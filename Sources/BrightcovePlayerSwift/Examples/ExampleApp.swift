//
// ExampleApp.swift
// BrightcovePlayerSwift Example
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import SwiftUI
import BrightcovePlayerSwift

@main
struct ExampleApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}

struct ContentView: View {
    @StateObject private var player = BrightcovePlayerBuilder.player(
        accountId: "YOUR_ACCOUNT_ID",
        policyKey: "YOUR_POLICY_KEY"
    )
    
    @State private var selectedTab = 0
    @State private var showingVideoDetail = false
    @State private var selectedVideo: BrightcoveVideo?
    
    var body: some View {
        TabView(selection: $selectedTab) {
            // Basic Player Tab
            PlayerTab(player: player)
                .tabItem {
                    Image(systemName: "play.rectangle.fill")
                    Text("Player")
                }
                .tag(0)
            
            // Custom Player Tab
            CustomPlayerTab(player: player)
                .tabItem {
                    Image(systemName: "tv")
                    Text("Custom")
                }
                .tag(1)
            
            // Playlist Tab
            PlaylistTab(player: player)
                .tabItem {
                    Image(systemName: "list.bullet")
                    Text("Playlist")
                }
                .tag(2)
        }
    }
}

// MARK: - Basic Player Tab

struct PlayerTab: View {
    @ObservedObject var player: BrightcovePlayer
    @State private var videoId = "6140448705001" // Sample video ID
    @State private var isLoading = false
    
    var body: some View {
        NavigationView {
            VStack(spacing: 20) {
                // Video Input
                VStack(alignment: .leading) {
                    Text("Video ID")
                        .font(.headline)
                    
                    TextField("Enter video ID", text: $videoId)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                }
                
                // Load Button
                Button("Load Video") {
                    loadVideo()
                }
                .buttonStyle(.borderedProminent)
                .disabled(videoId.isEmpty || isLoading)
                
                // Player
                if player.currentVideo != nil {
                    VideoPlayerView(player: player)
                        .aspectRatio(16/9, contentMode: .fit)
                        .background(Color.black)
                        .clipShape(RoundedRectangle(cornerRadius: 12))
                } else {
                    Rectangle()
                        .fill(Color.gray.opacity(0.3))
                        .aspectRatio(16/9, contentMode: .fit)
                        .overlay(
                            VStack {
                                Image(systemName: "play.rectangle")
                                    .font(.largeTitle)
                                    .foregroundColor(.gray)
                                Text("No video loaded")
                                    .foregroundColor(.gray)
                            }
                        )
                        .clipShape(RoundedRectangle(cornerRadius: 12))
                }
                
                // Player Controls
                PlayerControlsView(player: player)
                
                Spacer()
            }
            .padding()
            .navigationTitle("Basic Player")
            .alert("Error", isPresented: .constant(player.error != nil)) {
                Button("OK") {
                    // Handle error dismissal
                }
            } message: {
                Text(player.error?.localizedDescription ?? "Unknown error")
            }
        }
    }
    
    private func loadVideo() {
        isLoading = true
        Task {
            do {
                try await player.loadVideo(withId: videoId)
            } catch {
                print("Failed to load video: \(error)")
            }
            isLoading = false
        }
    }
}

// MARK: - Custom Player Tab

struct CustomPlayerTab: View {
    @ObservedObject var player: BrightcovePlayer
    @State private var videoUrl = "https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4"
    
    var body: some View {
        NavigationView {
            VStack(spacing: 20) {
                // URL Input
                VStack(alignment: .leading) {
                    Text("Video URL")
                        .font(.headline)
                    
                    TextField("Enter video URL", text: $videoUrl)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                }
                
                // Load Button
                Button("Load URL") {
                    if let url = URL(string: videoUrl) {
                        player.loadVideo(withURL: url)
                    }
                }
                .buttonStyle(.borderedProminent)
                .disabled(videoUrl.isEmpty)
                
                // Custom Player
                CustomVideoPlayer(player: player)
                    .clipShape(RoundedRectangle(cornerRadius: 12))
                
                Spacer()
            }
            .padding()
            .navigationTitle("Custom Player")
        }
    }
}

// MARK: - Playlist Tab

struct PlaylistTab: View {
    @ObservedObject var player: BrightcovePlayer
    @State private var sampleVideos: [BrightcoveVideo] = []
    
    var body: some View {
        NavigationView {
            ScrollView {
                LazyVStack(spacing: 16) {
                    ForEach(sampleVideos) { video in
                        VideoCardView(
                            video: video,
                            onPlay: {
                                player.setVideos([video])
                                player.play()
                            }
                        )
                    }
                }
                .padding()
            }
            .navigationTitle("Playlist")
            .onAppear {
                loadSampleVideos()
            }
        }
    }
    
    private func loadSampleVideos() {
        // Create sample videos
        sampleVideos = [
            BrightcoveVideo(
                name: "Big Buck Bunny",
                description: "A short computer-animated comedy film by the Blender Institute",
                duration: 596,
                sources: [
                    VideoSource(url: URL(string: "https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4")!)
                ]
            ),
            BrightcoveVideo(
                name: "Elephant Dream",
                description: "An open source computer animated short film",
                duration: 654,
                sources: [
                    VideoSource(url: URL(string: "https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ElephantsDream.mp4")!)
                ]
            )
        ]
    }
}

// MARK: - Player Controls View

struct PlayerControlsView: View {
    @ObservedObject var player: BrightcovePlayer
    
    var body: some View {
        VStack(spacing: 12) {
            // Progress
            VStack(spacing: 4) {
                HStack {
                    Text(formatTime(player.currentTime))
                        .font(.caption)
                        .monospacedDigit()
                    
                    Spacer()
                    
                    Text(formatTime(player.duration))
                        .font(.caption)
                        .monospacedDigit()
                }
                
                ProgressView(value: player.progress)
                    .progressViewStyle(LinearProgressViewStyle(tint: .blue))
            }
            
            // Control buttons
            HStack(spacing: 32) {
                Button(action: { player.seek(to: max(0, player.currentTime - 10)) }) {
                    Image(systemName: "gobackward.10")
                        .font(.title2)
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
                }
                
                Button(action: { player.seek(to: min(player.duration, player.currentTime + 10)) }) {
                    Image(systemName: "goforward.10")
                        .font(.title2)
                }
            }
            
            // Volume control
            HStack {
                Image(systemName: player.isMuted ? "speaker.slash.fill" : "speaker.wave.2.fill")
                    .onTapGesture {
                        player.isMuted.toggle()
                    }
                
                Slider(value: Binding(
                    get: { Double(player.volume) },
                    set: { player.volume = Float($0) }
                ), in: 0...1)
            }
        }
        .padding()
        .background(Color(.systemGray6))
        .clipShape(RoundedRectangle(cornerRadius: 12))
    }
    
    private func formatTime(_ timeInterval: TimeInterval) -> String {
        let minutes = Int(timeInterval) / 60
        let seconds = Int(timeInterval) % 60
        return String(format: "%02d:%02d", minutes, seconds)
    }
}