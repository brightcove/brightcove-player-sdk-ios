//
// PlaybackService+Swift.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import Foundation
import BrightcovePlayerSDK
import Combine

/// Swift-friendly extensions for BCOVPlaybackService
public extension BCOVPlaybackService {
    
    /// Load a video asynchronously using async/await
    /// - Parameters:
    ///   - videoId: The video ID to load
    ///   - authToken: Optional auth token
    /// - Returns: A BrightcoveVideo
    func loadVideo(
        withId videoId: String,
        authToken: String? = nil
    ) async throws -> BrightcoveVideo {
        var configuration = [BCOVPlaybackService.ConfigurationKeyAssetID: videoId]
        
        if let authToken = authToken {
            configuration[BCOVPlaybackService.ConfigurationKeyAuthToken] = authToken
        }
        
        return try await withCheckedThrowingContinuation { continuation in
            findVideo(withConfiguration: configuration, queryParameters: nil) { video, _, error in
                if let error = error {
                    continuation.resume(throwing: BrightcovePlayerError.videoLoadFailed(error))
                    return
                }
                
                guard let video = video else {
                    continuation.resume(throwing: BrightcovePlayerError.videoNotFound)
                    return
                }
                
                let brightcoveVideo = BrightcoveVideo(bcovVideo: video)
                continuation.resume(returning: brightcoveVideo)
            }
        }
    }
    
    /// Load a video by reference ID asynchronously
    /// - Parameters:
    ///   - referenceId: The reference ID to load
    ///   - authToken: Optional auth token
    /// - Returns: A BrightcoveVideo
    func loadVideo(
        withReferenceId referenceId: String,
        authToken: String? = nil
    ) async throws -> BrightcoveVideo {
        var configuration = [BCOVPlaybackService.ConfigurationKeyReferenceID: referenceId]
        
        if let authToken = authToken {
            configuration[BCOVPlaybackService.ConfigurationKeyAuthToken] = authToken
        }
        
        return try await withCheckedThrowingContinuation { continuation in
            findVideo(withConfiguration: configuration, queryParameters: nil) { video, _, error in
                if let error = error {
                    continuation.resume(throwing: BrightcovePlayerError.videoLoadFailed(error))
                    return
                }
                
                guard let video = video else {
                    continuation.resume(throwing: BrightcovePlayerError.videoNotFound)
                    return
                }
                
                let brightcoveVideo = BrightcoveVideo(bcovVideo: video)
                continuation.resume(returning: brightcoveVideo)
            }
        }
    }
    
    /// Load a playlist asynchronously
    /// - Parameters:
    ///   - playlistId: The playlist ID to load
    ///   - authToken: Optional auth token
    /// - Returns: A BrightcovePlaylist
    func loadPlaylist(
        withId playlistId: String,
        authToken: String? = nil
    ) async throws -> BrightcovePlaylist {
        var configuration = [BCOVPlaybackService.ConfigurationKeyAssetID: playlistId]
        
        if let authToken = authToken {
            configuration[BCOVPlaybackService.ConfigurationKeyAuthToken] = authToken
        }
        
        return try await withCheckedThrowingContinuation { continuation in
            findPlaylist(withConfiguration: configuration, queryParameters: nil) { playlist, _, error in
                if let error = error {
                    continuation.resume(throwing: BrightcovePlayerError.videoLoadFailed(error))
                    return
                }
                
                guard let playlist = playlist else {
                    continuation.resume(throwing: BrightcovePlayerError.videoNotFound)
                    return
                }
                
                let brightcovePlaylist = BrightcovePlaylist(bcovPlaylist: playlist)
                continuation.resume(returning: brightcovePlaylist)
            }
        }
    }
}

// MARK: - Combine Publishers

@available(iOS 13.0, tvOS 13.0, *)
public extension BCOVPlaybackService {
    
    /// Publisher for loading a video by ID
    func videoPublisher(
        withId videoId: String,
        authToken: String? = nil
    ) -> AnyPublisher<BrightcoveVideo, Error> {
        Future { [weak self] promise in
            guard let self = self else {
                promise(.failure(BrightcovePlayerError.playbackFailed("PlaybackService deallocated")))
                return
            }
            
            var configuration = [BCOVPlaybackService.ConfigurationKeyAssetID: videoId]
            
            if let authToken = authToken {
                configuration[BCOVPlaybackService.ConfigurationKeyAuthToken] = authToken
            }
            
            self.findVideo(withConfiguration: configuration, queryParameters: nil) { video, _, error in
                if let error = error {
                    promise(.failure(BrightcovePlayerError.videoLoadFailed(error)))
                    return
                }
                
                guard let video = video else {
                    promise(.failure(BrightcovePlayerError.videoNotFound))
                    return
                }
                
                let brightcoveVideo = BrightcoveVideo(bcovVideo: video)
                promise(.success(brightcoveVideo))
            }
        }
        .eraseToAnyPublisher()
    }
    
    /// Publisher for loading a playlist by ID
    func playlistPublisher(
        withId playlistId: String,
        authToken: String? = nil
    ) -> AnyPublisher<BrightcovePlaylist, Error> {
        Future { [weak self] promise in
            guard let self = self else {
                promise(.failure(BrightcovePlayerError.playbackFailed("PlaybackService deallocated")))
                return
            }
            
            var configuration = [BCOVPlaybackService.ConfigurationKeyAssetID: playlistId]
            
            if let authToken = authToken {
                configuration[BCOVPlaybackService.ConfigurationKeyAuthToken] = authToken
            }
            
            self.findPlaylist(withConfiguration: configuration, queryParameters: nil) { playlist, _, error in
                if let error = error {
                    promise(.failure(BrightcovePlayerError.videoLoadFailed(error)))
                    return
                }
                
                guard let playlist = playlist else {
                    promise(.failure(BrightcovePlayerError.videoNotFound))
                    return
                }
                
                let brightcovePlaylist = BrightcovePlaylist(bcovPlaylist: playlist)
                promise(.success(brightcovePlaylist))
            }
        }
        .eraseToAnyPublisher()
    }
}

// MARK: - BrightcovePlaylist

public struct BrightcovePlaylist: Identifiable {
    
    public let id: String
    public let name: String?
    public let description: String?
    public let videos: [BrightcoveVideo]
    public let properties: [String: Any]
    
    internal let bcovPlaylist: BCOVPlaylist
    
    internal init(bcovPlaylist: BCOVPlaylist) {
        self.bcovPlaylist = bcovPlaylist
        self.id = bcovPlaylist.properties[kBCOVPlaylistPropertiesKeyId] as? String ?? UUID().uuidString
        self.name = bcovPlaylist.properties[kBCOVPlaylistPropertiesKeyName] as? String
        self.description = bcovPlaylist.properties[kBCOVPlaylistPropertiesKeyDescription] as? String
        self.properties = bcovPlaylist.properties
        
        self.videos = bcovPlaylist.videos.compactMap { video in
            guard let bcovVideo = video as? BCOVVideo else { return nil }
            return BrightcoveVideo(bcovVideo: bcovVideo)
        }
    }
    
    public init(
        id: String = UUID().uuidString,
        name: String? = nil,
        description: String? = nil,
        videos: [BrightcoveVideo] = [],
        additionalProperties: [String: Any] = [:]
    ) {
        var properties = additionalProperties
        properties[kBCOVPlaylistPropertiesKeyId] = id
        properties[kBCOVPlaylistPropertiesKeyName] = name
        properties[kBCOVPlaylistPropertiesKeyDescription] = description
        
        let bcovVideos = videos.map { $0.bcovVideo }
        
        self.bcovPlaylist = BCOVPlaylist(videos: bcovVideos, properties: properties)
        
        self.id = id
        self.name = name
        self.description = description
        self.videos = videos
        self.properties = properties
    }
}