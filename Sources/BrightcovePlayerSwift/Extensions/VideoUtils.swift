//
// VideoUtils.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import Foundation
import AVFoundation
import SwiftUI

/// Utilities for working with video content and playback
public enum VideoUtils {
    
    // MARK: - Video Quality Detection
    
    /// Determine the quality level of a video source based on resolution
    /// - Parameter source: The video source to analyze
    /// - Returns: Quality level
    public static func qualityLevel(for source: VideoSource) -> VideoQuality {
        guard let width = source.width, let height = source.height else {
            return .unknown
        }
        
        let pixels = width * height
        
        switch pixels {
        case 0..<(640 * 360):
            return .low
        case (640 * 360)..<(1280 * 720):
            return .standard
        case (1280 * 720)..<(1920 * 1080):
            return .hd
        case (1920 * 1080)..<(3840 * 2160):
            return .fullHD
        default:
            return .ultraHD
        }
    }
    
    /// Get the best quality source from available sources
    /// - Parameter sources: Array of video sources
    /// - Returns: The highest quality source
    public static func bestQualitySource(from sources: [VideoSource]) -> VideoSource? {
        sources.max { lhs, rhs in
            let lhsQuality = qualityLevel(for: lhs)
            let rhsQuality = qualityLevel(for: rhs)
            return lhsQuality.rawValue < rhsQuality.rawValue
        }
    }
    
    // MARK: - Aspect Ratio Calculations
    
    /// Calculate the aspect ratio of a video source
    /// - Parameter source: The video source
    /// - Returns: Aspect ratio as width/height, or 16/9 if unknown
    public static func aspectRatio(for source: VideoSource) -> CGFloat {
        guard let width = source.width, let height = source.height, height > 0 else {
            return 16.0 / 9.0 // Default aspect ratio
        }
        return CGFloat(width) / CGFloat(height)
    }
    
    /// Determine if a video is in landscape or portrait orientation
    /// - Parameter source: The video source
    /// - Returns: Video orientation
    public static func orientation(for source: VideoSource) -> VideoOrientation {
        let ratio = aspectRatio(for: source)
        if ratio > 1.0 {
            return .landscape
        } else if ratio < 1.0 {
            return .portrait
        } else {
            return .square
        }
    }
    
    // MARK: - File Size Utilities
    
    /// Format a file size in bytes to human readable format
    /// - Parameter bytes: Size in bytes
    /// - Returns: Formatted size string (e.g., "1.2 MB")
    public static func formatFileSize(_ bytes: Int) -> String {
        let formatter = ByteCountFormatter()
        formatter.allowedUnits = [.useBytes, .useKB, .useMB, .useGB]
        formatter.countStyle = .file
        return formatter.string(fromByteCount: Int64(bytes))
    }
    
    /// Estimate bandwidth requirement for a video source
    /// - Parameter source: The video source
    /// - Returns: Estimated bandwidth in Mbps, or nil if unknown
    public static func estimatedBandwidth(for source: VideoSource) -> Double? {
        guard let bitrate = source.averageBitrate else { return nil }
        return Double(bitrate) / 1_000_000 // Convert to Mbps
    }
    
    // MARK: - Thumbnail Generation
    
    /// Generate a thumbnail URL for a given time in the video
    /// - Parameters:
    ///   - video: The video
    ///   - time: Time in seconds
    /// - Returns: Thumbnail URL if available
    public static func thumbnailURL(for video: BrightcoveVideo, at time: TimeInterval) -> URL? {
        // This is a placeholder - actual implementation would depend on 
        // the video service's thumbnail generation capabilities
        guard let baseURL = video.thumbnailURL?.absoluteString else { return nil }
        let timeParam = Int(time)
        return URL(string: "\(baseURL)?t=\(timeParam)")
    }
    
    // MARK: - Validation
    
    /// Validate if a video URL is potentially playable
    /// - Parameter url: The video URL to validate
    /// - Returns: true if the URL looks valid for video playback
    public static func isValidVideoURL(_ url: URL) -> Bool {
        let scheme = url.scheme?.lowercased()
        guard scheme == "http" || scheme == "https" else { return false }
        
        let pathExtension = url.pathExtension.lowercased()
        let validExtensions = ["mp4", "mov", "m4v", "m3u8", "mpd"]
        
        return validExtensions.contains(pathExtension) || pathExtension.isEmpty
    }
    
    /// Check if a video requires authentication
    /// - Parameter video: The video to check
    /// - Returns: true if authentication might be required
    public static func requiresAuthentication(_ video: BrightcoveVideo) -> Bool {
        // Check if any sources have authentication-related properties
        return video.sources.contains { source in
            source.bcovSource.properties.keys.contains { key in
                key.lowercased().contains("auth") || 
                key.lowercased().contains("token") ||
                key.lowercased().contains("drm")
            }
        }
    }
}

// MARK: - Supporting Types

public enum VideoQuality: Int, CaseIterable, Comparable {
    case unknown = 0
    case low = 1      // < 640x360
    case standard = 2 // 640x360 to 1280x720
    case hd = 3       // 720p
    case fullHD = 4   // 1080p
    case ultraHD = 5  // 4K+
    
    public var displayName: String {
        switch self {
        case .unknown: return "Unknown"
        case .low: return "Low (360p)"
        case .standard: return "Standard (480p)"
        case .hd: return "HD (720p)"
        case .fullHD: return "Full HD (1080p)"
        case .ultraHD: return "Ultra HD (4K)"
        }
    }
    
    public static func < (lhs: VideoQuality, rhs: VideoQuality) -> Bool {
        lhs.rawValue < rhs.rawValue
    }
}

public enum VideoOrientation {
    case landscape
    case portrait
    case square
    
    public var aspectRatio: CGFloat {
        switch self {
        case .landscape: return 16.0 / 9.0
        case .portrait: return 9.0 / 16.0
        case .square: return 1.0
        }
    }
}

// MARK: - SwiftUI Integration

public extension BrightcoveVideo {
    
    /// Get the video quality for display purposes
    var qualityLevel: VideoQuality {
        guard let bestSource = bestQualitySource else { return .unknown }
        return VideoUtils.qualityLevel(for: bestSource)
    }
    
    /// Get the primary aspect ratio of the video
    var aspectRatio: CGFloat {
        guard let bestSource = bestQualitySource else { return 16.0 / 9.0 }
        return VideoUtils.aspectRatio(for: bestSource)
    }
    
    /// Get the video orientation
    var orientation: VideoOrientation {
        guard let bestSource = bestQualitySource else { return .landscape }
        return VideoUtils.orientation(for: bestSource)
    }
    
    /// Get estimated bandwidth requirement
    var estimatedBandwidth: Double? {
        guard let bestSource = bestQualitySource else { return nil }
        return VideoUtils.estimatedBandwidth(for: bestSource)
    }
    
    /// Check if video requires authentication
    var requiresAuthentication: Bool {
        VideoUtils.requiresAuthentication(self)
    }
}

// MARK: - Preview Extensions for SwiftUI

#if DEBUG
public extension BrightcoveVideo {
    
    /// Create a sample video for SwiftUI previews
    static var sampleVideo: BrightcoveVideo {
        BrightcoveVideo(
            name: "Sample Video",
            description: "A sample video for testing and previews",
            duration: 120,
            thumbnailURL: URL(string: "https://via.placeholder.com/320x180"),
            sources: [
                VideoSource(
                    url: URL(string: "https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4")!,
                    deliveryMethod: .mp4,
                    width: 1920,
                    height: 1080,
                    averageBitrate: 2000000
                )
            ]
        )
    }
    
    /// Create a sample playlist for SwiftUI previews
    static var samplePlaylist: BrightcovePlaylist {
        BrightcovePlaylist(
            name: "Sample Playlist",
            description: "A sample playlist for testing",
            videos: [sampleVideo, sampleVideo, sampleVideo]
        )
    }
}
#endif