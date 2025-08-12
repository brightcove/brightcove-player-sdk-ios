//
// ViewModifiers.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import SwiftUI

// MARK: - Player View Modifiers

public extension View {
    
    /// Apply a loading state overlay to any view
    func loadingOverlay(_ isLoading: Bool, message: String = "Loading...") -> some View {
        self.overlay(
            Group {
                if isLoading {
                    ZStack {
                        Color.black.opacity(0.3)
                        
                        VStack(spacing: 16) {
                            ProgressView()
                                .progressViewStyle(CircularProgressViewStyle(tint: .white))
                                .scaleEffect(1.5)
                            
                            Text(message)
                                .foregroundColor(.white)
                                .font(.subheadline)
                        }
                        .padding(20)
                        .background(Color.black.opacity(0.7))
                        .clipShape(RoundedRectangle(cornerRadius: 12))
                    }
                    .transition(.opacity)
                    .animation(.easeInOut(duration: 0.2), value: isLoading)
                }
            }
        )
    }
    
    /// Apply an error alert to any view
    func errorAlert(_ error: Binding<BrightcovePlayerError?>) -> some View {
        self.alert("Playback Error", isPresented: .constant(error.wrappedValue != nil)) {
            Button("OK") {
                error.wrappedValue = nil
            }
        } message: {
            Text(error.wrappedValue?.localizedDescription ?? "Unknown error occurred")
        }
    }
    
    /// Apply a video player aspect ratio with safe bounds
    func videoAspectRatio(_ ratio: CGFloat = 16/9, contentMode: ContentMode = .fit) -> some View {
        self.aspectRatio(ratio, contentMode: contentMode)
            .clipped()
    }
}

// MARK: - Custom View Modifiers

/// A view modifier that adds a subtle glow effect
struct GlowEffect: ViewModifier {
    let color: Color
    let radius: CGFloat
    
    func body(content: Content) -> some View {
        content
            .shadow(color: color, radius: radius / 3)
            .shadow(color: color, radius: radius / 3)
            .shadow(color: color, radius: radius / 3)
    }
}

public extension View {
    func glow(color: Color = .blue, radius: CGFloat = 10) -> some View {
        self.modifier(GlowEffect(color: color, radius: radius))
    }
}

/// A view modifier for player control buttons
struct PlayerControlButton: ViewModifier {
    let isHighlighted: Bool
    
    func body(content: Content) -> some View {
        content
            .foregroundColor(.white)
            .padding(12)
            .background(
                Circle()
                    .fill(isHighlighted ? Color.blue.opacity(0.3) : Color.clear)
                    .overlay(
                        Circle()
                            .stroke(Color.white.opacity(0.3), lineWidth: 1)
                    )
            )
            .scaleEffect(isHighlighted ? 1.1 : 1.0)
            .animation(.easeInOut(duration: 0.1), value: isHighlighted)
    }
}

public extension View {
    func playerControlStyle(isHighlighted: Bool = false) -> some View {
        self.modifier(PlayerControlButton(isHighlighted: isHighlighted))
    }
}

// MARK: - Layout Extensions

public extension VideoPlayerView {
    
    /// Apply fullscreen presentation
    func fullscreenCover<Content: View>(
        isPresented: Binding<Bool>,
        @ViewBuilder content: @escaping () -> Content
    ) -> some View {
        self.fullScreenCover(isPresented: isPresented, content: content)
    }
}

// MARK: - Gesture Extensions

public extension CustomVideoPlayer {
    
    /// Add double-tap to fullscreen gesture
    func doubleTapFullscreen(_ action: @escaping () -> Void) -> some View {
        self.onTapGesture(count: 2) {
            action()
        }
    }
    
    /// Add pinch to zoom gesture for video content
    func pinchToZoom() -> some View {
        self.scaleEffect(1.0) // Placeholder for zoom implementation
            .gesture(
                MagnificationGesture()
                    .onChanged { value in
                        // Handle zoom changes
                    }
            )
    }
}