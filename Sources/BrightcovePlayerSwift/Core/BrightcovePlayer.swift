//
// BrightcovePlayer.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import Foundation
#if canImport(BrightcovePlayerSDK)
import BrightcovePlayerSDK
#endif
import AVFoundation
import Combine

/// A modern Swift wrapper for the Brightcove Player SDK
@MainActor
public final class BrightcovePlayer: ObservableObject {
    
    // MARK: - Published Properties
    
    /// The current playback state
    @Published public private(set) var playbackState: PlaybackState = .idle
    
    /// The current video being played
    @Published public private(set) var currentVideo: BrightcoveVideo?
    
    /// Current playback progress (0.0 to 1.0)
    @Published public private(set) var progress: Double = 0.0
    
    /// Current time in seconds
    @Published public private(set) var currentTime: TimeInterval = 0.0
    
    /// Total duration in seconds
    @Published public private(set) var duration: TimeInterval = 0.0
    
    /// Whether the player is muted
    @Published public var isMuted: Bool = false {
        didSet {
            playbackController.view.layer.sublayers?.first?.setValue(isMuted, forKey: "muted")
        }
    }
    
    /// Current volume (0.0 to 1.0)
    @Published public var volume: Float = 1.0 {
        didSet {
            if let session = playbackController.playbackSessions.first as? BCOVPlaybackSession {
                session.player.volume = volume
            }
        }
    }
    
    /// Whether the player is loading content
    @Published public private(set) var isLoading: Bool = false
    
    /// Any error that occurred during playback
    @Published public private(set) var error: BrightcovePlayerError?
    
    // MARK: - Internal Properties
    
    internal let playbackController: BCOVPlaybackController
    private let playbackService: BCOVPlaybackService?
    private var cancellables = Set<AnyCancellable>()
    
    // MARK: - Configuration
    
    public struct Configuration {
        public let accountId: String?
        public let policyKey: String?
        public let authToken: String?
        public let playbackServiceConfiguration: [String: Any]
        
        public init(
            accountId: String? = nil,
            policyKey: String? = nil,
            authToken: String? = nil,
            playbackServiceConfiguration: [String: Any] = [:]
        ) {
            self.accountId = accountId
            self.policyKey = policyKey
            self.authToken = authToken
            self.playbackServiceConfiguration = playbackServiceConfiguration
        }
    }
    
    // MARK: - Initialization
    
    public init(configuration: Configuration = Configuration()) {
        let sdkManager = BCOVPlayerSDKManager.sharedManager()
        self.playbackController = sdkManager.createPlaybackController()
        
        if let accountId = configuration.accountId,
           let policyKey = configuration.policyKey {
            self.playbackService = BCOVPlaybackService(withAccountId: accountId, policyKey: policyKey)
        } else {
            self.playbackService = nil
        }
        
        setupPlaybackController()
    }
    
    // MARK: - Private Setup
    
    private func setupPlaybackController() {
        playbackController.delegate = PlaybackControllerDelegate(player: self)
        playbackController.isAutoAdvance = true
        playbackController.isAutoPlay = true
    }
}

// MARK: - Playback Control

public extension BrightcovePlayer {
    
    /// Play the current video
    func play() {
        playbackController.play()
        playbackState = .playing
    }
    
    /// Pause the current video
    func pause() {
        playbackController.pause()
        playbackState = .paused
    }
    
    /// Seek to a specific time
    /// - Parameter time: The time to seek to in seconds
    func seek(to time: TimeInterval) {
        playbackController.seek(to: CMTimeMakeWithSeconds(time, preferredTimescale: CMTimeScale(NSEC_PER_SEC)))
    }
    
    /// Seek to a specific progress percentage
    /// - Parameter progress: The progress to seek to (0.0 to 1.0)
    func seek(to progress: Double) {
        let targetTime = duration * progress
        seek(to: targetTime)
    }
    
    /// Stop playback and reset to beginning
    func stop() {
        playbackController.pause()
        seek(to: 0)
        playbackState = .stopped
    }
    
    /// Set videos to play
    /// - Parameter videos: Array of BrightcoveVideo objects
    func setVideos(_ videos: [BrightcoveVideo]) {
        let bcovVideos = videos.map { $0.bcovVideo }
        playbackController.setVideos(bcovVideos)
        isLoading = false
    }
}

// MARK: - Video Loading

public extension BrightcovePlayer {
    
    /// Load a video by ID using the Playback Service
    /// - Parameter videoId: The video ID to load
    func loadVideo(withId videoId: String) async throws {
        guard let playbackService = playbackService else {
            throw BrightcovePlayerError.noPlaybackService
        }
        
        await MainActor.run {
            isLoading = true
            error = nil
        }
        
        let configuration = [
            BCOVPlaybackService.ConfigurationKeyAssetID: videoId
        ]
        
        return try await withCheckedThrowingContinuation { continuation in
            playbackService.findVideo(withConfiguration: configuration, queryParameters: nil) { [weak self] video, _, error in
                Task { @MainActor in
                    self?.isLoading = false
                    
                    if let error = error {
                        let brightcoveError = BrightcovePlayerError.videoLoadFailed(error)
                        self?.error = brightcoveError
                        continuation.resume(throwing: brightcoveError)
                        return
                    }
                    
                    guard let video = video else {
                        let brightcoveError = BrightcovePlayerError.videoNotFound
                        self?.error = brightcoveError
                        continuation.resume(throwing: brightcoveError)
                        return
                    }
                    
                    let brightcoveVideo = BrightcoveVideo(bcovVideo: video)
                    self?.setVideos([brightcoveVideo])
                    self?.currentVideo = brightcoveVideo
                    
                    continuation.resume()
                }
            }
        }
    }
    
    /// Load a video with a direct URL
    /// - Parameter url: The video URL
    func loadVideo(withURL url: URL) {
        let video = BCOVVideo.video(withURL: url)
        let brightcoveVideo = BrightcoveVideo(bcovVideo: video)
        setVideos([brightcoveVideo])
        currentVideo = brightcoveVideo
    }
}

// MARK: - Playback State

public enum PlaybackState {
    case idle
    case loading
    case playing
    case paused
    case stopped
    case ended
    case error
}

// MARK: - Error Handling

public enum BrightcovePlayerError: Error, LocalizedError {
    case noPlaybackService
    case videoLoadFailed(Error)
    case videoNotFound
    case playbackFailed(String)
    
    public var errorDescription: String? {
        switch self {
        case .noPlaybackService:
            return "No playback service configured. Please provide account ID and policy key."
        case .videoLoadFailed(let error):
            return "Failed to load video: \(error.localizedDescription)"
        case .videoNotFound:
            return "Video not found"
        case .playbackFailed(let message):
            return "Playback failed: \(message)"
        }
    }
}

// MARK: - Playback Controller Delegate

private class PlaybackControllerDelegate: NSObject, BCOVPlaybackControllerDelegate {
    weak var player: BrightcovePlayer?
    
    init(player: BrightcovePlayer) {
        self.player = player
    }
    
    func playbackController(_ controller: BCOVPlaybackController,
                          playbackSession session: BCOVPlaybackSession,
                          didProgressTo progress: TimeInterval) {
        Task { @MainActor in
            player?.currentTime = progress
            if let duration = player?.duration, duration > 0 {
                player?.progress = progress / duration
            }
        }
    }
    
    func playbackController(_ controller: BCOVPlaybackController,
                          playbackSession session: BCOVPlaybackSession,
                          didChangeDuration duration: TimeInterval) {
        Task { @MainActor in
            player?.duration = duration
        }
    }
    
    func playbackController(_ controller: BCOVPlaybackController,
                          playbackSession session: BCOVPlaybackSession,
                          didReceive lifecycleEvent: BCOVPlaybackSessionLifecycleEvent) {
        Task { @MainActor in
            switch lifecycleEvent.eventType {
            case kBCOVPlaybackSessionLifecycleEventPlay:
                player?.playbackState = .playing
            case kBCOVPlaybackSessionLifecycleEventPause:
                player?.playbackState = .paused
            case kBCOVPlaybackSessionLifecycleEventEnd:
                player?.playbackState = .ended
            case kBCOVPlaybackSessionLifecycleEventFail:
                player?.playbackState = .error
                if let properties = lifecycleEvent.properties,
                   let errorMessage = properties["error"] as? String {
                    player?.error = BrightcovePlayerError.playbackFailed(errorMessage)
                }
            default:
                break
            }
        }
    }
}