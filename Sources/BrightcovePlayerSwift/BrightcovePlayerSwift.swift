//
// BrightcovePlayerSwift.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import Foundation

// The BrightcovePlayerSDK module should be imported by the consumer
// @_exported import BrightcovePlayerSDK

// MARK: - Version Information

/// Version information for the BrightcovePlayerSwift wrapper
public enum BrightcovePlayerSwift {
    public static let version = "1.0.0"
    public static let compatibleSDKVersion = "7.0.7"
}

// MARK: - Quick Start Helpers

/// Convenience methods for quickly setting up a Brightcove player
public enum BrightcovePlayerBuilder {
    
    /// Create a basic player with account credentials
    /// - Parameters:
    ///   - accountId: Your Brightcove account ID
    ///   - policyKey: Your Brightcove policy key
    /// - Returns: A configured BrightcovePlayer
    public static func player(
        accountId: String,
        policyKey: String
    ) -> BrightcovePlayer {
        let configuration = BrightcovePlayer.Configuration(
            accountId: accountId,
            policyKey: policyKey
        )
        return BrightcovePlayer(configuration: configuration)
    }
    
    /// Create a player for direct URL playback (no account required)
    /// - Returns: A BrightcovePlayer configured for URL-based playback
    public static func urlPlayer() -> BrightcovePlayer {
        BrightcovePlayer()
    }
    
    /// Create a player with full configuration options
    /// - Parameter configuration: Complete player configuration
    /// - Returns: A configured BrightcovePlayer
    public static func player(
        with configuration: BrightcovePlayer.Configuration
    ) -> BrightcovePlayer {
        BrightcovePlayer(configuration: configuration)
    }
}

// MARK: - Global Configuration

/// Global configuration options for the Brightcove Player SDK
public enum BrightcoveGlobalConfig {
    
    /// Set the China proxy domain for playback services
    /// - Parameter domain: The proxy domain to use
    public static func setChinaProxyDomain(_ domain: String) {
        BCOVGlobalConfiguration.sharedConfig.chinaProxyDomain = domain
    }
    
    /// Get the current session ID for analytics tracking
    public static var sessionID: String {
        BCOVPlayerSDKManager.sharedManager().sessionID
    }
}

// MARK: - Analytics Extensions

public extension BrightcovePlayer {
    
    /// Enable analytics tracking with custom parameters
    /// - Parameter parameters: Custom analytics parameters
    func enableAnalytics(with parameters: [String: Any] = [:]) {
        // Configure analytics if needed
        if var options = playbackController.options {
            for (key, value) in parameters {
                options[key] = value
            }
            playbackController.options = options
        }
    }
}

// MARK: - Debugging Helpers

#if DEBUG
public extension BrightcovePlayer {
    
    /// Enable verbose logging for debugging
    func enableVerboseLogging() {
        // Enable logging at the SDK level
        BCOVPlayerSDKManager.sharedManager().setLogLevel(.verbose)
    }
    
    /// Get current playback session information for debugging
    var debugInfo: [String: Any] {
        var info: [String: Any] = [:]
        
        info["playbackState"] = String(describing: playbackState)
        info["currentTime"] = currentTime
        info["duration"] = duration
        info["progress"] = progress
        info["volume"] = volume
        info["isMuted"] = isMuted
        info["isLoading"] = isLoading
        
        if let video = currentVideo {
            info["currentVideoId"] = video.id
            info["currentVideoName"] = video.name
            info["currentVideoSources"] = video.sources.count
        }
        
        return info
    }
}
#endif