//
// CustomVideoPlayer.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import SwiftUI
import Combine

/// A fully SwiftUI-native video player with custom controls
public struct CustomVideoPlayer: View {
    
    @ObservedObject private var player: BrightcovePlayer
    @State private var showControls = true
    @State private var isControlsHidden = false
    @State private var controlsTimer: AnyCancellable?
    
    private let showBuiltInControls: Bool
    private let autoHideControls: Bool
    private let autoHideDelay: TimeInterval
    
    public init(
        player: BrightcovePlayer,
        showBuiltInControls: Bool = false,
        autoHideControls: Bool = true,
        autoHideDelay: TimeInterval = 3.0
    ) {
        self.player = player
        self.showBuiltInControls = showBuiltInControls
        self.autoHideControls = autoHideControls
        self.autoHideDelay = autoHideDelay
    }
    
    public var body: some View {
        ZStack {
            // Video player view
            VideoPlayerView(
                player: player,
                configuration: PlayerViewConfiguration(
                    automaticControlTypeSelection: showBuiltInControls,
                    controlsLayout: showBuiltInControls ? .vod : .none
                )
            )
            .aspectRatio(16/9, contentMode: .fit)
            .background(Color.black)
            
            // Custom overlay controls
            if !showBuiltInControls {
                customControlsOverlay
            }
            
            // Loading indicator
            if player.isLoading {
                ProgressView()
                    .progressViewStyle(CircularProgressViewStyle(tint: .white))
                    .scaleEffect(1.5)
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
                    .background(Color.black.opacity(0.3))
            }
        }
        .onTapGesture {
            if autoHideControls && !showBuiltInControls {
                toggleControls()
            }
        }
        .onReceive(player.$playbackState) { state in
            if state == .playing && autoHideControls {
                startControlsHideTimer()
            } else {
                cancelControlsHideTimer()
            }
        }
    }
    
    @ViewBuilder
    private var customControlsOverlay: some View {
        VStack {
            Spacer()
            
            if showControls {
                CustomControlsView(player: player)
                    .transition(.opacity.combined(with: .move(edge: .bottom)))
                    .animation(.easeInOut(duration: 0.3), value: showControls)
            }
        }
        .opacity(isControlsHidden ? 0 : 1)
    }
    
    private func toggleControls() {
        withAnimation(.easeInOut(duration: 0.3)) {
            showControls.toggle()
        }
        
        if showControls {
            startControlsHideTimer()
        } else {
            cancelControlsHideTimer()
        }
    }
    
    private func startControlsHideTimer() {
        cancelControlsHideTimer()
        
        controlsTimer = Timer.publish(every: autoHideDelay, on: .main, in: .common)
            .autoconnect()
            .sink { _ in
                withAnimation(.easeInOut(duration: 0.3)) {
                    showControls = false
                }
                cancelControlsHideTimer()
            }
    }
    
    private func cancelControlsHideTimer() {
        controlsTimer?.cancel()
        controlsTimer = nil
    }
}

// MARK: - Custom Controls View

private struct CustomControlsView: View {
    @ObservedObject var player: BrightcovePlayer
    @State private var isDragging = false
    
    var body: some View {
        VStack(spacing: 16) {
            // Progress bar
            VStack(spacing: 8) {
                HStack {
                    Text(formatTime(player.currentTime))
                        .font(.caption)
                        .foregroundColor(.white)
                    
                    Spacer()
                    
                    Text(formatTime(player.duration))
                        .font(.caption)
                        .foregroundColor(.white)
                }
                
                GeometryReader { geometry in
                    ZStack(alignment: .leading) {
                        // Track
                        Rectangle()
                            .fill(Color.white.opacity(0.3))
                            .frame(height: 4)
                        
                        // Progress
                        Rectangle()
                            .fill(Color.red)
                            .frame(width: geometry.size.width * CGFloat(player.progress), height: 4)
                    }
                    .clipShape(RoundedRectangle(cornerRadius: 2))
                    .gesture(
                        DragGesture()
                            .onChanged { value in
                                isDragging = true
                                let progress = Double(value.location.x / geometry.size.width)
                                let clampedProgress = min(max(progress, 0), 1)
                                player.seek(to: clampedProgress)
                            }
                            .onEnded { _ in
                                isDragging = false
                            }
                    )
                }
                .frame(height: 4)
            }
            
            // Control buttons
            HStack(spacing: 32) {
                Button(action: {
                    let newTime = max(0, player.currentTime - 10)
                    player.seek(to: newTime)
                }) {
                    Image(systemName: "gobackward.10")
                        .font(.title2)
                        .foregroundColor(.white)
                }
                
                Button(action: {
                    if player.playbackState == .playing {
                        player.pause()
                    } else {
                        player.play()
                    }
                }) {
                    Image(systemName: player.playbackState == .playing ? "pause.fill" : "play.fill")
                        .font(.title)
                        .foregroundColor(.white)
                }
                
                Button(action: {
                    let newTime = min(player.duration, player.currentTime + 10)
                    player.seek(to: newTime)
                }) {
                    Image(systemName: "goforward.10")
                        .font(.title2)
                        .foregroundColor(.white)
                }
                
                Spacer()
                
                // Volume control
                HStack {
                    Image(systemName: player.isMuted ? "speaker.slash.fill" : "speaker.wave.2.fill")
                        .font(.caption)
                        .foregroundColor(.white)
                        .onTapGesture {
                            player.isMuted.toggle()
                        }
                    
                    Slider(value: Binding(
                        get: { Double(player.volume) },
                        set: { player.volume = Float($0) }
                    ), in: 0...1)
                    .frame(width: 60)
                    .accentColor(.white)
                }
            }
        }
        .padding(.horizontal, 20)
        .padding(.vertical, 16)
        .background(
            LinearGradient(
                gradient: Gradient(colors: [Color.clear, Color.black.opacity(0.7)]),
                startPoint: .top,
                endPoint: .bottom
            )
        )
    }
    
    private func formatTime(_ timeInterval: TimeInterval) -> String {
        let minutes = Int(timeInterval) / 60
        let seconds = Int(timeInterval) % 60
        return String(format: "%02d:%02d", minutes, seconds)
    }
}

// MARK: - View Modifiers

public extension CustomVideoPlayer {
    
    /// Configure whether to show built-in controls
    func showBuiltInControls(_ show: Bool = true) -> CustomVideoPlayer {
        CustomVideoPlayer(
            player: player,
            showBuiltInControls: show,
            autoHideControls: autoHideControls,
            autoHideDelay: autoHideDelay
        )
    }
    
    /// Configure auto-hide behavior for custom controls
    func autoHideControls(_ autoHide: Bool = true, delay: TimeInterval = 3.0) -> CustomVideoPlayer {
        CustomVideoPlayer(
            player: player,
            showBuiltInControls: showBuiltInControls,
            autoHideControls: autoHide,
            autoHideDelay: delay
        )
    }
}