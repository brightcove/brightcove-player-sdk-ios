//
// VideoPlayerView.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import SwiftUI
import BrightcovePlayerSDK

/// A SwiftUI view that wraps the Brightcove Player
public struct VideoPlayerView: UIViewRepresentable {
    
    @ObservedObject private var player: BrightcovePlayer
    private let configuration: PlayerViewConfiguration
    
    public init(
        player: BrightcovePlayer,
        configuration: PlayerViewConfiguration = PlayerViewConfiguration()
    ) {
        self.player = player
        self.configuration = configuration
    }
    
    public func makeUIView(context: Context) -> BCOVPUIPlayerView {
        let options = BCOVPUIPlayerViewOptions()
        options.automaticControlTypeSelection = configuration.automaticControlTypeSelection
        options.jumpBackInterval = configuration.jumpBackInterval
        options.hideControlsInterval = configuration.hideControlsInterval
        options.hideControlsAnimationDuration = configuration.hideControlsAnimationDuration
        options.showControlsAnimationDuration = configuration.showControlsAnimationDuration
        options.showPictureInPictureButton = configuration.showPictureInPictureButton
        
        let controlView: BCOVPUIBasicControlView
        switch configuration.controlsLayout {
        case .vod:
            controlView = BCOVPUIBasicControlView.withVODLayout()
        case .live:
            controlView = BCOVPUIBasicControlView.withLiveLayout()
        case .liveDVR:
            controlView = BCOVPUIBasicControlView.withLiveDVRLayout()
        case .audioOnly:
            controlView = BCOVPUIBasicControlView.basicControlView(withAODLayout: ())
        case .liveAudio:
            controlView = BCOVPUIBasicControlView.basicControlView(withLiveAudioLayout: ())
        case .liveDVRAudio:
            controlView = BCOVPUIBasicControlView.basicControlView(withLiveDVRAudioLayout: ())
        case .none:
            controlView = BCOVPUIBasicControlView()
        }
        
        let playerView = BCOVPUIPlayerView(
            playbackController: player.playbackController,
            options: options,
            controlsView: controlView
        )
        
        playerView?.delegate = context.coordinator
        
        return playerView ?? BCOVPUIPlayerView()
    }
    
    public func updateUIView(_ uiView: BCOVPUIPlayerView, context: Context) {
        // Update any view properties if needed
    }
    
    public func makeCoordinator() -> Coordinator {
        Coordinator(self)
    }
    
    public class Coordinator: NSObject, BCOVPUIPlayerViewDelegate {
        private let parent: VideoPlayerView
        
        init(_ parent: VideoPlayerView) {
            self.parent = parent
        }
        
        // Implement delegate methods as needed
        public func playerView(_ playerView: BCOVPUIPlayerView,
                             willTransitionTo screenMode: BCOVPUIScreenMode) {
            // Handle screen mode transitions
        }
    }
}

// MARK: - Configuration

public struct PlayerViewConfiguration {
    public let automaticControlTypeSelection: Bool
    public let jumpBackInterval: TimeInterval
    public let hideControlsInterval: TimeInterval
    public let hideControlsAnimationDuration: TimeInterval
    public let showControlsAnimationDuration: TimeInterval
    public let showPictureInPictureButton: Bool
    public let controlsLayout: ControlsLayout
    
    public init(
        automaticControlTypeSelection: Bool = true,
        jumpBackInterval: TimeInterval = 10.0,
        hideControlsInterval: TimeInterval = 3.0,
        hideControlsAnimationDuration: TimeInterval = 0.25,
        showControlsAnimationDuration: TimeInterval = 0.25,
        showPictureInPictureButton: Bool = true,
        controlsLayout: ControlsLayout = .vod
    ) {
        self.automaticControlTypeSelection = automaticControlTypeSelection
        self.jumpBackInterval = jumpBackInterval
        self.hideControlsInterval = hideControlsInterval
        self.hideControlsAnimationDuration = hideControlsAnimationDuration
        self.showControlsAnimationDuration = showControlsAnimationDuration
        self.showPictureInPictureButton = showPictureInPictureButton
        self.controlsLayout = controlsLayout
    }
    
    public enum ControlsLayout {
        case vod
        case live
        case liveDVR
        case audioOnly
        case liveAudio
        case liveDVRAudio
        case none
    }
}

// MARK: - View Modifiers

public extension VideoPlayerView {
    
    /// Configure the player view with custom settings
    func playerConfiguration(_ configuration: PlayerViewConfiguration) -> VideoPlayerView {
        VideoPlayerView(player: player, configuration: configuration)
    }
    
    /// Enable or disable automatic control type selection
    func automaticControls(_ enabled: Bool = true) -> VideoPlayerView {
        var config = configuration
        config = PlayerViewConfiguration(
            automaticControlTypeSelection: enabled,
            jumpBackInterval: config.jumpBackInterval,
            hideControlsInterval: config.hideControlsInterval,
            hideControlsAnimationDuration: config.hideControlsAnimationDuration,
            showControlsAnimationDuration: config.showControlsAnimationDuration,
            showPictureInPictureButton: config.showPictureInPictureButton,
            controlsLayout: config.controlsLayout
        )
        return VideoPlayerView(player: player, configuration: config)
    }
    
    /// Set the jump back interval
    func jumpBackInterval(_ interval: TimeInterval) -> VideoPlayerView {
        var config = configuration
        config = PlayerViewConfiguration(
            automaticControlTypeSelection: config.automaticControlTypeSelection,
            jumpBackInterval: interval,
            hideControlsInterval: config.hideControlsInterval,
            hideControlsAnimationDuration: config.hideControlsAnimationDuration,
            showControlsAnimationDuration: config.showControlsAnimationDuration,
            showPictureInPictureButton: config.showPictureInPictureButton,
            controlsLayout: config.controlsLayout
        )
        return VideoPlayerView(player: player, configuration: config)
    }
    
    /// Enable or disable Picture in Picture
    func pictureInPicture(_ enabled: Bool = true) -> VideoPlayerView {
        var config = configuration
        config = PlayerViewConfiguration(
            automaticControlTypeSelection: config.automaticControlTypeSelection,
            jumpBackInterval: config.jumpBackInterval,
            hideControlsInterval: config.hideControlsInterval,
            hideControlsAnimationDuration: config.hideControlsAnimationDuration,
            showControlsAnimationDuration: config.showControlsAnimationDuration,
            showPictureInPictureButton: enabled,
            controlsLayout: config.controlsLayout
        )
        return VideoPlayerView(player: player, configuration: config)
    }
}