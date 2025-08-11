# Brightcove Player SDK for iOS - Swift & SwiftUI

A modern Swift and SwiftUI wrapper for the Brightcove Player SDK, providing idiomatic Swift APIs and native SwiftUI components.

## 🆕 What's New

This repository has been enhanced with a comprehensive Swift and SwiftUI layer on top of the existing Objective-C Brightcove Player SDK. The new implementation provides:

- **Modern Swift API**: Async/await support, Combine publishers, and Swift-friendly interfaces
- **SwiftUI Components**: Native SwiftUI video player views with customizable controls
- **Reactive Programming**: ObservableObject conformance with @Published properties
- **Type Safety**: Strong typing with Swift enums and structs
- **Simplified Usage**: Builder patterns and convenience initializers

## Table of Contents

1. [Swift Quick Start](#swift-quick-start)
2. [SwiftUI Integration](#swiftui-integration)
3. [Modern Swift Features](#modern-swift-features)
4. [Custom SwiftUI Components](#custom-swiftui-components)
5. [Migration Guide](#migration-guide)
6. [Examples](#examples)
7. [Legacy Documentation](#legacy-documentation)

## Swift Quick Start

### Basic Player Setup

```swift
import SwiftUI
import BrightcovePlayerSwift

struct ContentView: View {
    @StateObject private var player = BrightcovePlayerBuilder.player(
        accountId: "YOUR_ACCOUNT_ID",
        policyKey: "YOUR_POLICY_KEY"
    )
    
    var body: some View {
        VStack {
            VideoPlayerView(player: player)
                .aspectRatio(16/9, contentMode: .fit)
            
            Button("Load Video") {
                Task {
                    try await player.loadVideo(withId: "YOUR_VIDEO_ID")
                }
            }
        }
    }
}
```

### URL-based Playback

```swift
let player = BrightcovePlayerBuilder.urlPlayer()
let videoURL = URL(string: "https://example.com/video.mp4")!
player.loadVideo(withURL: videoURL)
```

## SwiftUI Integration

### Built-in Player Controls

```swift
VideoPlayerView(player: player)
    .automaticControls(true)
    .jumpBackInterval(10)
    .pictureInPicture(true)
```

### Custom SwiftUI Player

```swift
CustomVideoPlayer(player: player)
    .showBuiltInControls(false)
    .autoHideControls(true, delay: 3.0)
```

### Video Thumbnails and Cards

```swift
// Thumbnail view
VideoThumbnailView(
    video: brightcoveVideo,
    size: .medium,
    onTap: { playVideo() }
)

// Card view with actions
VideoCardView(
    video: brightcoveVideo,
    onPlay: { playVideo() },
    onAddToQueue: { addToQueue() }
)
```

### Playlist Views

```swift
VideoPlaylistView(
    playlist: playlist,
    layout: .grid(columns: 2),
    onVideoTap: { video in
        player.setVideos([video])
        player.play()
    }
)
```

## Modern Swift Features

### Async/Await Support

```swift
// Load video with async/await
do {
    try await player.loadVideo(withId: "video123")
    print("Video loaded successfully")
} catch {
    print("Failed to load video: \(error)")
}

// Load playlist
let playlist = try await playbackService.loadPlaylist(withId: "playlist123")
```

### Combine Publishers

```swift
import Combine

// Observe playback state changes
player.$playbackState
    .sink { state in
        switch state {
        case .playing:
            print("Video is playing")
        case .paused:
            print("Video is paused")
        case .ended:
            print("Video ended")
        default:
            break
        }
    }
    .store(in: &cancellables)

// Use Combine for loading videos
playbackService
    .videoPublisher(withId: "video123")
    .sink(
        receiveCompletion: { completion in
            if case .failure(let error) = completion {
                print("Error: \(error)")
            }
        },
        receiveValue: { video in
            player.setVideos([video])
        }
    )
    .store(in: &cancellables)
```

### Reactive Player Properties

```swift
// All player properties are @Published for SwiftUI
@ObservedObject var player: BrightcovePlayer

// Automatically updates UI when these change:
player.playbackState  // .idle, .loading, .playing, .paused, .stopped, .ended
player.currentTime    // Current playback time
player.duration       // Total video duration  
player.progress       // Progress from 0.0 to 1.0
player.volume         // Volume from 0.0 to 1.0
player.isMuted        // Mute state
player.isLoading      // Loading indicator
player.currentVideo   // Currently playing video
player.error          // Any playback errors
```

## Custom SwiftUI Components

### Custom Controls Example

```swift
struct MyCustomPlayer: View {
    @ObservedObject var player: BrightcovePlayer
    
    var body: some View {
        ZStack {
            VideoPlayerView(player: player)
                .playerConfiguration(
                    PlayerViewConfiguration(controlsLayout: .none)
                )
            
            VStack {
                Spacer()
                
                // Custom control bar
                HStack {
                    Button(action: { player.play() }) {
                        Image(systemName: "play.fill")
                    }
                    
                    Slider(value: Binding(
                        get: { player.progress },
                        set: { player.seek(to: $0) }
                    ))
                    
                    Text("\(formatTime(player.currentTime))")
                }
                .padding()
                .background(Color.black.opacity(0.7))
            }
        }
    }
}
```

### Custom Video Loading

```swift
struct VideoLoader: View {
    @StateObject private var player = BrightcovePlayerBuilder.urlPlayer()
    
    var body: some View {
        VStack {
            if player.isLoading {
                ProgressView("Loading video...")
            } else if let error = player.error {
                Text("Error: \(error.localizedDescription)")
                    .foregroundColor(.red)
            } else {
                CustomVideoPlayer(player: player)
            }
        }
        .task {
            // Load video on appear
            await loadVideo()
        }
    }
    
    private func loadVideo() async {
        do {
            try await player.loadVideo(withId: "sample_video_id")
        } catch {
            print("Failed to load: \(error)")
        }
    }
}
```

## Advanced Features

### Configuration Options

```swift
// Player configuration
let configuration = BrightcovePlayer.Configuration(
    accountId: "account123",
    policyKey: "policy456", 
    authToken: "auth789"
)

let player = BrightcovePlayer(configuration: configuration)

// PlayerView configuration
let viewConfig = PlayerViewConfiguration(
    automaticControlTypeSelection: true,
    jumpBackInterval: 15.0,
    hideControlsInterval: 4.0,
    showPictureInPictureButton: true,
    controlsLayout: .vod
)
```

### Error Handling

```swift
// Comprehensive error handling
do {
    try await player.loadVideo(withId: videoId)
} catch BrightcovePlayerError.noPlaybackService {
    print("Please configure account ID and policy key")
} catch BrightcovePlayerError.videoNotFound {
    print("Video not found")
} catch BrightcovePlayerError.videoLoadFailed(let error) {
    print("Load failed: \(error)")
} catch {
    print("Unexpected error: \(error)")
}
```

### Analytics and Debugging

```swift
// Enable analytics
player.enableAnalytics(with: [
    "custom_param": "value"
])

#if DEBUG
// Debug helpers
player.enableVerboseLogging()
print("Debug info: \(player.debugInfo)")
#endif
```

## Migration Guide

### From Objective-C to Swift

**Before (Objective-C):**
```objective-c
BCOVPlayerSDKManager *sdkManager = [BCOVPlayerSDKManager sharedManager];
BCOVPlaybackController *playbackController = [sdkManager createPlaybackController];

[playbackService findVideoWithConfiguration:@{kBCOVPlaybackServiceConfigurationKeyAssetID: videoId}
                            queryParameters:nil
                                 completion:^(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error) {
    if (video) {
        [self.playbackController setVideos:@[video]];
        [self.playbackController play];
    }
}];
```

**After (Swift with async/await):**
```swift
let player = BrightcovePlayerBuilder.player(
    accountId: accountId,
    policyKey: policyKey
)

try await player.loadVideo(withId: videoId)
player.play()
```

### From UIKit to SwiftUI

**Before (UIKit):**
```swift
let options = BCOVPUIPlayerViewOptions()
let controlView = BCOVPUIBasicControlView.withVODLayout()
let playerView = BCOVPUIPlayerView(playbackController: playbackController, 
                                  options: options, 
                                  controlsView: controlView)
view.addSubview(playerView)
```

**After (SwiftUI):**
```swift
VideoPlayerView(player: player)
    .automaticControls(true)
```

## Installation

### Swift Package Manager

Add this repository URL to your Xcode project:
```
https://github.com/Mannydefreitas7/brightcove-player-swift
```

Then import both modules:
```swift
import BrightcovePlayerSDK      // Original SDK
import BrightcovePlayerSwift    // Swift wrapper
```

### Requirements

- iOS 13.0+ / tvOS 13.0+ (for SwiftUI and Combine)
- Xcode 13.0+
- Swift 5.5+

## Examples

See the `Sources/BrightcovePlayerSwift/Examples/` folder for complete example apps demonstrating:

- Basic video playback
- Custom SwiftUI controls
- Playlist management
- Error handling
- Advanced configurations

## Legacy Documentation

For the original Objective-C documentation, see the sections below or refer to the [original README](README_ORIGINAL.md).

---

# Legacy Brightcove Player SDK Documentation

The following sections contain the original documentation for the Objective-C SDK, which remains fully functional and supported.
