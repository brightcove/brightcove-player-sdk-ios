# Brightcove Player SDK for iOS with Swift & SwiftUI

[![Swift](https://img.shields.io/badge/Swift-5.5+-orange)](https://swift.org)
[![iOS](https://img.shields.io/badge/iOS-13.0+-blue)](https://developer.apple.com/ios/)
[![SwiftUI](https://img.shields.io/badge/SwiftUI-2.0+-green)](https://developer.apple.com/xcode/swiftui/)
[![SPM](https://img.shields.io/badge/SPM-compatible-brightgreen)](https://swift.org/package-manager/)

## 🎉 Now with Native Swift & SwiftUI Support!

This repository has been enhanced with a comprehensive **Swift and SwiftUI layer** that provides modern, idiomatic APIs while maintaining full compatibility with the original Objective-C SDK.

### ⚡ Quick Start - SwiftUI

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
            
            Button("Play Sample Video") {
                Task {
                    try await player.loadVideo(withId: "6140448705001")
                }
            }
        }
    }
}
```

### 🚀 What's New

- **Native SwiftUI Components**: Drop-in video players, thumbnails, and playlists
- **Modern Swift APIs**: Async/await, Combine publishers, @Published properties
- **Type-Safe Models**: Swift structs and enums for all video data
- **Reactive Programming**: ObservableObject conformance for seamless SwiftUI integration
- **Custom Controls**: Build your own player UI with SwiftUI
- **Builder Patterns**: Easy setup with fluent APIs

📖 **[Complete Swift & SwiftUI Documentation →](README_SWIFT.md)**
