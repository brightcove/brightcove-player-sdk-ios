//
// MockSDK.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import Foundation
import UIKit
import AVFoundation

// MARK: - Mock implementations for when BrightcovePlayerSDK is not available

#if !canImport(BrightcovePlayerSDK)

// Mock the essential types and constants from the SDK for compilation

public typealias BCOVPlaybackController = MockPlaybackController
public typealias BCOVVideo = MockVideo  
public typealias BCOVSource = MockSource
public typealias BCOVPlaylist = MockPlaylist
public typealias BCOVPlaybackService = MockPlaybackService
public typealias BCOVPlayerSDKManager = MockPlayerSDKManager
public typealias BCOVPlaybackSession = MockPlaybackSession
public typealias BCOVPlaybackSessionLifecycleEvent = MockLifecycleEvent
public typealias BCOVPUIPlayerView = MockPlayerView
public typealias BCOVPUIBasicControlView = MockControlView
public typealias BCOVPUIPlayerViewOptions = MockPlayerViewOptions
public typealias BCOVCuePointCollection = MockCuePointCollection
public typealias BCOVGlobalConfiguration = MockGlobalConfiguration

// Mock constants
public let kBCOVVideoPropertyKeyId = "id"
public let kBCOVVideoPropertyKeyName = "name"
public let kBCOVVideoPropertyKeyDescription = "description"
public let kBCOVVideoPropertyKeyDuration = "duration"
public let kBCOVVideoPropertyKeyThumbnail = "thumbnail"
public let kBCOVVideoPropertyKeyPoster = "poster"
public let kBCOVPlaylistPropertiesKeyId = "id"
public let kBCOVPlaylistPropertiesKeyName = "name"
public let kBCOVPlaylistPropertiesKeyDescription = "description"
public let kBCOVSourceDeliveryHLS = "application/x-mpegURL"
public let kBCOVSourceDeliveryMP4 = "video/mp4"
public let kBCOVSourceDeliveryDASH = "application/dash+xml"
public let kBCOVPlaybackSessionLifecycleEventPlay = "play"
public let kBCOVPlaybackSessionLifecycleEventPause = "pause"
public let kBCOVPlaybackSessionLifecycleEventEnd = "end"
public let kBCOVPlaybackSessionLifecycleEventFail = "fail"

// Mock protocol definitions
public protocol BCOVPlaybackControllerDelegate: AnyObject {
    func playbackController(_ controller: BCOVPlaybackController, 
                          playbackSession session: BCOVPlaybackSession,
                          didProgressTo progress: TimeInterval)
    func playbackController(_ controller: BCOVPlaybackController,
                          playbackSession session: BCOVPlaybackSession,
                          didChangeDuration duration: TimeInterval)
    func playbackController(_ controller: BCOVPlaybackController,
                          playbackSession session: BCOVPlaybackSession,
                          didReceive lifecycleEvent: BCOVPlaybackSessionLifecycleEvent)
}

public protocol BCOVPUIPlayerViewDelegate: AnyObject {
    func playerView(_ playerView: BCOVPUIPlayerView, willTransitionTo screenMode: Int)
}

// Mock class implementations
public class MockPlaybackController {
    public weak var delegate: BCOVPlaybackControllerDelegate?
    public var view: UIView = UIView()
    public var isAutoAdvance = true
    public var isAutoPlay = true
    public var options: [String: Any] = [:]
    public var playbackSessions: [Any] = []
    
    public func play() {}
    public func pause() {}
    public func seek(to time: CMTime) {}
    public func setVideos(_ videos: [BCOVVideo]) {}
}

public class MockVideo {
    public let properties: [String: Any]
    public let sources: [BCOVSource]
    
    public init(source: BCOVSource?, cuePoints: BCOVCuePointCollection?, properties: [String: Any]) {
        self.properties = properties
        self.sources = source != nil ? [source!] : []
    }
    
    public static func video(withURL url: URL) -> MockVideo {
        let source = MockSource(url: url, deliveryMethod: "video/mp4", properties: [:])
        return MockVideo(source: source, cuePoints: nil, properties: [:])
    }
}

public class MockSource {
    public let url: URL
    public let deliveryMethod: String?
    public let properties: [String: Any]
    
    public init(url: URL, deliveryMethod: String?, properties: [String: Any]) {
        self.url = url
        self.deliveryMethod = deliveryMethod
        self.properties = properties
    }
}

public class MockPlaylist {
    public let videos: [BCOVVideo]
    public let properties: [String: Any]
    
    public init(videos: [BCOVVideo], properties: [String: Any]) {
        self.videos = videos
        self.properties = properties
    }
}

public class MockPlaybackService {
    public init(withAccountId accountId: String, policyKey: String) {}
    
    public func findVideo(withConfiguration configuration: [String: Any], 
                         queryParameters: [String: Any]?,
                         completion: @escaping (BCOVVideo?, Any?, Error?) -> Void) {
        // Mock implementation
        completion(nil, nil, NSError(domain: "MockSDK", code: 0, userInfo: [NSLocalizedDescriptionKey: "Mock implementation - BrightcovePlayerSDK not available"]))
    }
    
    public func findPlaylist(withConfiguration configuration: [String: Any],
                           queryParameters: [String: Any]?,
                           completion: @escaping (BCOVPlaylist?, Any?, Error?) -> Void) {
        // Mock implementation  
        completion(nil, nil, NSError(domain: "MockSDK", code: 0, userInfo: [NSLocalizedDescriptionKey: "Mock implementation - BrightcovePlayerSDK not available"]))
    }
}

public class MockPlayerSDKManager {
    public static func sharedManager() -> MockPlayerSDKManager {
        return MockPlayerSDKManager()
    }
    
    public func createPlaybackController() -> BCOVPlaybackController {
        return MockPlaybackController()
    }
    
    public var sessionID: String {
        return "mock-session-id"
    }
    
    public func setLogLevel(_ level: Int) {}
}

public class MockPlaybackSession {
    public var player: AVPlayer = AVPlayer()
}

public class MockLifecycleEvent {
    public let eventType: String
    public let properties: [String: Any]?
    
    public init(eventType: String, properties: [String: Any]?) {
        self.eventType = eventType
        self.properties = properties
    }
}

public class MockPlayerView: UIView {
    public weak var delegate: BCOVPUIPlayerViewDelegate?
    
    public init(playbackController: BCOVPlaybackController?, options: BCOVPUIPlayerViewOptions?, controlsView: BCOVPUIBasicControlView?) {
        super.init(frame: .zero)
        backgroundColor = .black
    }
    
    public init(playbackController: BCOVPlaybackController?, options: BCOVPUIPlayerViewOptions?) {
        super.init(frame: .zero)
        backgroundColor = .black
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
}

public class MockControlView: UIView {
    public static func withVODLayout() -> MockControlView {
        return MockControlView()
    }
    
    public static func withLiveLayout() -> MockControlView {
        return MockControlView()
    }
    
    public static func withLiveDVRLayout() -> MockControlView {
        return MockControlView()
    }
    
    public static func basicControlView(withAODLayout: Void) -> MockControlView {
        return MockControlView()
    }
    
    public static func basicControlView(withLiveAudioLayout: Void) -> MockControlView {
        return MockControlView()
    }
    
    public static func basicControlView(withLiveDVRAudioLayout: Void) -> MockControlView {
        return MockControlView()
    }
}

public class MockPlayerViewOptions {
    public var automaticControlTypeSelection = true
    public var jumpBackInterval: TimeInterval = 10.0
    public var hideControlsInterval: TimeInterval = 3.0
    public var hideControlsAnimationDuration: TimeInterval = 0.25
    public var showControlsAnimationDuration: TimeInterval = 0.25
    public var showPictureInPictureButton = false
}

public class MockCuePointCollection {}

public class MockGlobalConfiguration {
    public static let sharedConfig = MockGlobalConfiguration()
    public var chinaProxyDomain: String?
}

// Mock service extensions
public extension MockPlaybackService {
    static let ConfigurationKeyAssetID = "videoId"
    static let ConfigurationKeyReferenceID = "referenceId" 
    static let ConfigurationKeyAuthToken = "authToken"
}

#endif