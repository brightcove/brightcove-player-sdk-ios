//
// BrightcoveVideo.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import Foundation
#if canImport(BrightcovePlayerSDK)
import BrightcovePlayerSDK
#endif

/// A Swift wrapper for BCOVVideo providing a more idiomatic interface
public struct BrightcoveVideo: Identifiable, Hashable {
    
    // MARK: - Properties
    
    public let id: String
    public let name: String?
    public let description: String?
    public let duration: TimeInterval
    public let thumbnailURL: URL?
    public let posterURL: URL?
    public let sources: [VideoSource]
    public let properties: [String: Any]
    
    internal let bcovVideo: BCOVVideo
    
    // MARK: - Initialization
    
    internal init(bcovVideo: BCOVVideo) {
        self.bcovVideo = bcovVideo
        self.id = bcovVideo.properties[kBCOVVideoPropertyKeyId] as? String ?? UUID().uuidString
        self.name = bcovVideo.properties[kBCOVVideoPropertyKeyName] as? String
        self.description = bcovVideo.properties[kBCOVVideoPropertyKeyDescription] as? String
        self.duration = (bcovVideo.properties[kBCOVVideoPropertyKeyDuration] as? NSNumber)?.doubleValue ?? 0
        self.properties = bcovVideo.properties
        
        // Extract URLs
        self.thumbnailURL = {
            if let thumbnailURLString = bcovVideo.properties[kBCOVVideoPropertyKeyThumbnail] as? String {
                return URL(string: thumbnailURLString)
            }
            return nil
        }()
        
        self.posterURL = {
            if let posterURLString = bcovVideo.properties[kBCOVVideoPropertyKeyPoster] as? String {
                return URL(string: posterURLString)
            }
            return nil
        }()
        
        // Convert sources
        self.sources = bcovVideo.sources.compactMap { source in
            guard let bcovSource = source as? BCOVSource else { return nil }
            return VideoSource(bcovSource: bcovSource)
        }
    }
    
    public init(
        id: String = UUID().uuidString,
        name: String? = nil,
        description: String? = nil,
        duration: TimeInterval = 0,
        thumbnailURL: URL? = nil,
        posterURL: URL? = nil,
        sources: [VideoSource] = [],
        additionalProperties: [String: Any] = [:]
    ) {
        var properties = additionalProperties
        properties[kBCOVVideoPropertyKeyId] = id
        properties[kBCOVVideoPropertyKeyName] = name
        properties[kBCOVVideoPropertyKeyDescription] = description
        properties[kBCOVVideoPropertyKeyDuration] = NSNumber(value: duration)
        
        if let thumbnailURL = thumbnailURL {
            properties[kBCOVVideoPropertyKeyThumbnail] = thumbnailURL.absoluteString
        }
        
        if let posterURL = posterURL {
            properties[kBCOVVideoPropertyKeyPoster] = posterURL.absoluteString
        }
        
        let bcovSources = sources.map { $0.bcovSource }
        
        self.bcovVideo = BCOVVideo(
            source: bcovSources.first,
            cuePoints: BCOVCuePointCollection(),
            properties: properties
        )
        
        self.id = id
        self.name = name
        self.description = description
        self.duration = duration
        self.thumbnailURL = thumbnailURL
        self.posterURL = posterURL
        self.sources = sources
        self.properties = properties
    }
    
    // MARK: - Hashable
    
    public func hash(into hasher: inout Hasher) {
        hasher.combine(id)
    }
    
    public static func == (lhs: BrightcoveVideo, rhs: BrightcoveVideo) -> Bool {
        lhs.id == rhs.id
    }
}

// MARK: - VideoSource

public struct VideoSource: Identifiable, Hashable {
    
    public let id = UUID()
    public let url: URL
    public let deliveryMethod: DeliveryMethod
    public let mediaType: String?
    public let size: Int?
    public let averageBitrate: Int?
    public let width: Int?
    public let height: Int?
    
    internal let bcovSource: BCOVSource
    
    internal init(bcovSource: BCOVSource) {
        self.bcovSource = bcovSource
        self.url = bcovSource.url
        
        // Convert delivery method
        if let deliveryMethodString = bcovSource.deliveryMethod {
            switch deliveryMethodString {
            case kBCOVSourceDeliveryHLS:
                self.deliveryMethod = .hls
            case kBCOVSourceDeliveryMP4:
                self.deliveryMethod = .mp4
            case kBCOVSourceDeliveryDASH:
                self.deliveryMethod = .dash
            default:
                self.deliveryMethod = .unknown
            }
        } else {
            self.deliveryMethod = .unknown
        }
        
        self.mediaType = bcovSource.properties["media_type"] as? String
        self.size = (bcovSource.properties["size"] as? NSNumber)?.intValue
        self.averageBitrate = (bcovSource.properties["avg_bitrate"] as? NSNumber)?.intValue
        self.width = (bcovSource.properties["width"] as? NSNumber)?.intValue
        self.height = (bcovSource.properties["height"] as? NSNumber)?.intValue
    }
    
    public init(
        url: URL,
        deliveryMethod: DeliveryMethod = .hls,
        mediaType: String? = nil,
        size: Int? = nil,
        averageBitrate: Int? = nil,
        width: Int? = nil,
        height: Int? = nil
    ) {
        self.url = url
        self.deliveryMethod = deliveryMethod
        self.mediaType = mediaType
        self.size = size
        self.averageBitrate = averageBitrate
        self.width = width
        self.height = height
        
        var properties: [String: Any] = [:]
        if let mediaType = mediaType { properties["media_type"] = mediaType }
        if let size = size { properties["size"] = NSNumber(value: size) }
        if let averageBitrate = averageBitrate { properties["avg_bitrate"] = NSNumber(value: averageBitrate) }
        if let width = width { properties["width"] = NSNumber(value: width) }
        if let height = height { properties["height"] = NSNumber(value: height) }
        
        self.bcovSource = BCOVSource(
            url: url,
            deliveryMethod: deliveryMethod.rawValue,
            properties: properties
        )
    }
    
    public enum DeliveryMethod: String, CaseIterable {
        case hls = "application/x-mpegURL"
        case mp4 = "video/mp4"
        case dash = "application/dash+xml"
        case unknown = "unknown"
    }
}

// MARK: - Convenience Extensions

public extension BrightcoveVideo {
    
    /// Create a video with a single URL source
    static func video(withURL url: URL, name: String? = nil) -> BrightcoveVideo {
        let source = VideoSource(url: url)
        return BrightcoveVideo(
            name: name,
            sources: [source]
        )
    }
    
    /// Get the best quality source based on resolution and bitrate
    var bestQualitySource: VideoSource? {
        sources.max { lhs, rhs in
            // Prefer HLS over MP4
            if lhs.deliveryMethod != rhs.deliveryMethod {
                if lhs.deliveryMethod == .hls { return false }
                if rhs.deliveryMethod == .hls { return true }
            }
            
            // Then by resolution
            let lhsResolution = (lhs.width ?? 0) * (lhs.height ?? 0)
            let rhsResolution = (rhs.width ?? 0) * (rhs.height ?? 0)
            
            if lhsResolution != rhsResolution {
                return lhsResolution < rhsResolution
            }
            
            // Finally by bitrate
            return (lhs.averageBitrate ?? 0) < (rhs.averageBitrate ?? 0)
        }
    }
    
    /// Get HLS sources only
    var hlsSources: [VideoSource] {
        sources.filter { $0.deliveryMethod == .hls }
    }
    
    /// Get MP4 sources only
    var mp4Sources: [VideoSource] {
        sources.filter { $0.deliveryMethod == .mp4 }
    }
}