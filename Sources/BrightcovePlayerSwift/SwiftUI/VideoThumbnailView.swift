//
// VideoThumbnailView.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import SwiftUI

/// A SwiftUI view for displaying video thumbnails with metadata
public struct VideoThumbnailView: View {
    
    private let video: BrightcoveVideo
    private let size: ThumbnailSize
    private let showMetadata: Bool
    private let onTap: (() -> Void)?
    
    public init(
        video: BrightcoveVideo,
        size: ThumbnailSize = .medium,
        showMetadata: Bool = true,
        onTap: (() -> Void)? = nil
    ) {
        self.video = video
        self.size = size
        self.showMetadata = showMetadata
        self.onTap = onTap
    }
    
    public var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            // Thumbnail image
            thumbnailImage
                .aspectRatio(16/9, contentMode: .fill)
                .frame(width: size.width, height: size.height)
                .clipShape(RoundedRectangle(cornerRadius: 8))
                .overlay(
                    RoundedRectangle(cornerRadius: 8)
                        .stroke(Color.gray.opacity(0.3), lineWidth: 1)
                )
                .overlay(
                    // Duration badge
                    durationBadge,
                    alignment: .bottomTrailing
                )
                .onTapGesture {
                    onTap?()
                }
            
            // Metadata
            if showMetadata {
                VStack(alignment: .leading, spacing: 4) {
                    if let name = video.name {
                        Text(name)
                            .font(size.titleFont)
                            .fontWeight(.medium)
                            .lineLimit(2)
                    }
                    
                    if let description = video.description {
                        Text(description)
                            .font(size.descriptionFont)
                            .foregroundColor(.secondary)
                            .lineLimit(3)
                    }
                }
                .frame(width: size.width, alignment: .leading)
            }
        }
    }
    
    @ViewBuilder
    private var thumbnailImage: some View {
        AsyncImage(url: video.thumbnailURL ?? video.posterURL) { image in
            image
                .resizable()
        } placeholder: {
            Rectangle()
                .fill(Color.gray.opacity(0.3))
                .overlay(
                    Image(systemName: "play.rectangle.fill")
                        .font(.largeTitle)
                        .foregroundColor(.white.opacity(0.8))
                )
        }
    }
    
    @ViewBuilder
    private var durationBadge: some View {
        if video.duration > 0 {
            Text(formatDuration(video.duration))
                .font(.caption2)
                .fontWeight(.medium)
                .foregroundColor(.white)
                .padding(.horizontal, 6)
                .padding(.vertical, 2)
                .background(Color.black.opacity(0.8))
                .clipShape(RoundedRectangle(cornerRadius: 4))
                .padding(6)
        }
    }
    
    private func formatDuration(_ duration: TimeInterval) -> String {
        let hours = Int(duration) / 3600
        let minutes = (Int(duration) % 3600) / 60
        let seconds = Int(duration) % 60
        
        if hours > 0 {
            return String(format: "%d:%02d:%02d", hours, minutes, seconds)
        } else {
            return String(format: "%d:%02d", minutes, seconds)
        }
    }
}

// MARK: - ThumbnailSize

public enum ThumbnailSize {
    case small
    case medium
    case large
    case custom(width: CGFloat, height: CGFloat)
    
    var width: CGFloat {
        switch self {
        case .small: return 120
        case .medium: return 200
        case .large: return 320
        case .custom(let width, _): return width
        }
    }
    
    var height: CGFloat {
        switch self {
        case .small: return 68
        case .medium: return 112
        case .large: return 180
        case .custom(_, let height): return height
        }
    }
    
    var titleFont: Font {
        switch self {
        case .small: return .caption
        case .medium: return .subheadline
        case .large: return .headline
        case .custom: return .subheadline
        }
    }
    
    var descriptionFont: Font {
        switch self {
        case .small: return .caption2
        case .medium: return .caption
        case .large: return .subheadline
        case .custom: return .caption
        }
    }
}

// MARK: - Playlist View

/// A SwiftUI view for displaying a playlist of videos
public struct VideoPlaylistView: View {
    
    private let playlist: BrightcovePlaylist
    private let thumbnailSize: ThumbnailSize
    private let layout: PlaylistLayout
    private let onVideoTap: ((BrightcoveVideo) -> Void)?
    
    public init(
        playlist: BrightcovePlaylist,
        thumbnailSize: ThumbnailSize = .medium,
        layout: PlaylistLayout = .vertical,
        onVideoTap: ((BrightcoveVideo) -> Void)? = nil
    ) {
        self.playlist = playlist
        self.thumbnailSize = thumbnailSize
        self.layout = layout
        self.onVideoTap = onVideoTap
    }
    
    public var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            // Playlist header
            if let name = playlist.name {
                Text(name)
                    .font(.title2)
                    .fontWeight(.bold)
            }
            
            if let description = playlist.description {
                Text(description)
                    .font(.subheadline)
                    .foregroundColor(.secondary)
            }
            
            // Videos
            switch layout {
            case .vertical:
                LazyVStack(spacing: 16) {
                    ForEach(playlist.videos) { video in
                        VideoThumbnailView(
                            video: video,
                            size: thumbnailSize,
                            onTap: { onVideoTap?(video) }
                        )
                    }
                }
                
            case .horizontal:
                ScrollView(.horizontal, showsIndicators: false) {
                    LazyHStack(spacing: 16) {
                        ForEach(playlist.videos) { video in
                            VideoThumbnailView(
                                video: video,
                                size: thumbnailSize,
                                onTap: { onVideoTap?(video) }
                            )
                        }
                    }
                    .padding(.horizontal)
                }
                
            case .grid(let columns):
                LazyVGrid(columns: Array(repeating: GridItem(.flexible()), count: columns), spacing: 16) {
                    ForEach(playlist.videos) { video in
                        VideoThumbnailView(
                            video: video,
                            size: thumbnailSize,
                            onTap: { onVideoTap?(video) }
                        )
                    }
                }
            }
        }
    }
    
    public enum PlaylistLayout {
        case vertical
        case horizontal
        case grid(columns: Int)
    }
}

// MARK: - Video Card View

/// A card-style view for displaying video information
public struct VideoCardView: View {
    
    private let video: BrightcoveVideo
    private let onPlay: (() -> Void)?
    private let onAddToQueue: (() -> Void)?
    
    public init(
        video: BrightcoveVideo,
        onPlay: (() -> Void)? = nil,
        onAddToQueue: (() -> Void)? = nil
    ) {
        self.video = video
        self.onPlay = onPlay
        self.onAddToQueue = onAddToQueue
    }
    
    public var body: some View {
        VStack(alignment: .leading, spacing: 0) {
            // Thumbnail
            AsyncImage(url: video.thumbnailURL ?? video.posterURL) { image in
                image
                    .resizable()
                    .aspectRatio(16/9, contentMode: .fill)
            } placeholder: {
                Rectangle()
                    .fill(Color.gray.opacity(0.3))
                    .aspectRatio(16/9, contentMode: .fill)
                    .overlay(
                        ProgressView()
                    )
            }
            .clipped()
            
            // Content
            VStack(alignment: .leading, spacing: 12) {
                VStack(alignment: .leading, spacing: 4) {
                    if let name = video.name {
                        Text(name)
                            .font(.headline)
                            .fontWeight(.semibold)
                            .lineLimit(2)
                    }
                    
                    if let description = video.description {
                        Text(description)
                            .font(.subheadline)
                            .foregroundColor(.secondary)
                            .lineLimit(3)
                    }
                }
                
                // Action buttons
                HStack {
                    Button(action: { onPlay?() }) {
                        HStack {
                            Image(systemName: "play.fill")
                            Text("Play")
                        }
                        .font(.subheadline)
                        .fontWeight(.medium)
                        .foregroundColor(.white)
                        .padding(.horizontal, 16)
                        .padding(.vertical, 8)
                        .background(Color.blue)
                        .clipShape(RoundedRectangle(cornerRadius: 8))
                    }
                    
                    if onAddToQueue != nil {
                        Button(action: { onAddToQueue?() }) {
                            Image(systemName: "plus")
                                .font(.subheadline)
                                .fontWeight(.medium)
                                .foregroundColor(.blue)
                                .padding(8)
                                .background(Color.blue.opacity(0.1))
                                .clipShape(Circle())
                        }
                    }
                    
                    Spacer()
                    
                    if video.duration > 0 {
                        Text(formatDuration(video.duration))
                            .font(.caption)
                            .foregroundColor(.secondary)
                    }
                }
            }
            .padding(16)
        }
        .background(Color(.systemBackground))
        .clipShape(RoundedRectangle(cornerRadius: 12))
        .shadow(color: .black.opacity(0.1), radius: 8, x: 0, y: 2)
    }
    
    private func formatDuration(_ duration: TimeInterval) -> String {
        let hours = Int(duration) / 3600
        let minutes = (Int(duration) % 3600) / 60
        let seconds = Int(duration) % 60
        
        if hours > 0 {
            return String(format: "%d:%02d:%02d", hours, minutes, seconds)
        } else {
            return String(format: "%d:%02d", minutes, seconds)
        }
    }
}