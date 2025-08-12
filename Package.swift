// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "BrightcovePlayerSwift",
    platforms: [
        .iOS(.v13), .tvOS(.v13) // Minimum iOS 13 for SwiftUI and Combine
    ],
    products: [
        .library(
            name: "BrightcovePlayerSDK",
            targets: ["BrightcovePlayerSDK"]
        ),
        .library(
            name: "BrightcovePlayerSwift",
            targets: ["BrightcovePlayerSwift"]
        )
    ],
    targets: [
        .binaryTarget(
            name: "BrightcovePlayerSDK",
            path: "xcframework/BrightcovePlayerSDK.xcframework"
        ),
        .target(
            name: "BrightcovePlayerSwift",
            dependencies: ["BrightcovePlayerSDK"],
            path: "Sources/BrightcovePlayerSwift",
            exclude: ["Examples/"]
        )
    ]
)