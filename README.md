# Brightcove Player SDK for iOS, version 6.12.0.2391


## Table of Contents

1. [Requirements](#requirements)
1. [Supported Platforms](#supported-platforms)
1. [Noteworthy](#noteworthy)
1. [FairPlay](#fairplay)
1. [Sidecar Subtitles](#sidecar-subtitles)
1. [Offline Playback](#offline-playback)
1. [Installation](#installation)
1. [CocoaPods](#cocoapods)
1. [Manual Installaion](#manual-installation)
1. [Swift Package Manager](#swift-package-manager)
1. [Imports](#imports)
1. [Quick Start](#quick-start)
1. [Built-In PlayerUI Controls for iOS](#built-in-playerui-controls)
1. [Built-In TV Player Controls for tvOS](#built-in-tv-player-controls-for-tvos)
1. [AirPlay](#airplay)
1. [Video 360](#video-360)
1. [Architectural Overview](#architectural-lverview)
1. [Play, Pause, and Seek](#play-pause-and-seek)
1. [Playback Rate](#playback-rate)
1. [Preloading Videos](#preloading-videos)
1. [Source Selection (HLS, MP4, HTTP/HTTPS)](#source-selection-hls-mp4-httphttps)
1. [Setting a Preferred Bitrate](#setting-a-preferred-bitrate)
1. [Obtaining Content and Ad Playback Information](#obtaining-content-and-ad-playback-information)
1. [Handling Network Interruptions and Slowdowns](#handling-network-interruptions-and-slowdowns)
1. [Subclassing](#subclassing)
1. [Values](#values)
1. [Retrieving Brightcove Assets Using the Playback Service](#retrieving-brightcove-assets-using-the-playback-service)
1. [View Strategy](#view-strategy)
1. [Playing Video In The Background](#playing-video-in-the-background)
1. [Picture In Picture](#picture-in-picture)
1. [Thumbnail Seeking](#thumbnail-seeking)
1. [Video Insertion](#video-insertion)
1. [Generic Stream Concurrency](#generic-stream-concurrency)
1. [Tracking Errors](#tracking-errors)
1. [Combining Plugins](#combining-plugins)
1. [Buffer Optimization](#buffer-optimization)
1. [Using an AVPlayerViewController with a BCOVPlaybackController](#using-an-avplayerviewcontroller-with-a-bcovplaybackcontroller)
1. [Playback Authorization Service](#playback-authorization-service)
1. [VoiceOver Support](#voiceover-support)
1. [Custom Localization](#custom-localization)
1. [China Delivery](#china-delivery)
1. [AVAudioSession Configuration](#avaudiosession-configuration)
1. [Audio-Only Support](#audio-only-support)
1. [Bumper Support](#bumper-support)
1. [Frequently Asked Questions](#frequently-asked-questions)
1. [Support](#support)

## Requirements

- Xcode 13.0+
- ARC

## Supported Platforms

Brightcove provides active support for the latest iOS SDK on the latest public release of the following iOS versions:

 * iOS 13, 14 and 15
 * tvOS 13, 14 and 15
 * Mac Catalyst 13.0 and above (since 6.10.3).

Brightcove provides passive support for the following iOS versions:

 * iOS 11.4.1, 12.5.4
 * tvOS 11.4.1, 12.4.1

The Core SDK is localized for Arabic (ar), English (en), French (fr), German (de), Japanese (ja), Korean (ko), Spanish (es), Simplified Chinese (zh-Hans) and Traditional Chinese (zh-Hant). To gain the benefit of a localization, your app must also be localized for the same language and locale. See the [Custom Localization](#CustomLocalization) section for additional information.

## Noteworthy

All SDK components - the core and plugin frameworks - are released with the same version number. When upgrading any single component, upgrade all components to the same version.

### Running on Apple Silicon M1 Simulators with Universal Frameworks

For projects using Xcode 12 on Apple Silicon M1 and Universal Frameworks (.framework) a build error is returned when building the project for the arm64 simulator.

```
*ld: building for iOS Simulator, but linking in dylib built for iOS, file for architecture arm64*
```
To build for an arm64 simulator, ensure that `arm64` has been added to your "Excluded Architectures" build setting for `Any iOS Simulator SDK` in the "Build Settings" tab of your application target.

### CocoaPods Podspec XCFramework Subspecs (since release 6.10.0)

Release 6.10.0 of the Brightcove Player SDK adds subspecs for core and each plugin to support XCFrameworks. The default value for each subspec is `/Framework`.

The BrightcoveGoogleCast plugin supports the `no-bluetooth` variant. As shown below, the first subspec indicates the GoogleCast version to be used (bluetooth or no-bluetooth) and the second subspec indicates the distribution package of the plugin (Framework or XCFramework). Bluetooth and Framework are the default subspecs for BrightcoveGoogleCast.

```bash
  pod 'Brightcove-Player-GoogleCast'                          # Bluetooth and Framework
  pod 'Brightcove-Player-GoogleCast/Bluetooth'                # Bluetooth and Framework
  pod 'Brightcove-Player-GoogleCast/Bluetooth/Framework'      # Bluetooth and Framework
  pod 'Brightcove-Player-GoogleCast/Bluetooth/XCFramework'    # Bluetooth and XCFramework
  pod 'Brightcove-Player-GoogleCast/No-Bluetooth'             # No-Bluetooth and Framework
  pod 'Brightcove-Player-GoogleCast/No-Bluetooth/Framework'   # No-Bluetooth and Framework
  pod 'Brightcove-Player-GoogleCast/No-Bluetooth/XCFramework' # No-Bluetooth and XCFramework
```
<br/>

| Podspec Name | Subspec Names |
|---|---|
| Brightcove-Player-Core | Brightcove-Player-Core/Framework<br>Brightcove-Player-Core/XCFramework |
| Brightcove-Player-Core-static | Brightcove-Player-Core-static/Framework<br>Brightcove-Player-Core-static/XCFramework |
| Brightcove-Player-FreeWheel | Brightcove-Player-FreeWheel/Framework<br>Brightcove-Player-FreeWheel/XCFramework |
| Brightcove-Player-GoogleCast | Brightcove-Player-GoogleCast/Bluetooth/Framework<br>Brightcove-Player-GoogleCast/No-Bluetooth/Framework<br>Brightcove-Player-GoogleCast/Bluetooth/XCFramework<br>Brightcove-Player-GoogleCast/No-Bluetooth/XCFramework |
| Brightcove-Player-GoogleCast-static | Brightcove-Player-GoogleCast-static/Bluetooth/Framework<br>Brightcove-Player-GoogleCast-static/No-Bluetooth/Framework<br>Brightcove-Player-GoogleCast-static/Bluetooth/XCFramework<br>Brightcove-Player-GoogleCast-static/No-Bluetooth/XCFramework |
| Brightcove-Player-IMA | Brightcove-Player-IMA/Framework<br>Brightcove-Player-IMA/XCFramework |
| Brightcove-Player-Omniture | Brightcove-Player-Omniture/Framework<br>Brightcove-Player-Omniture/XCFramework |
| Brightcove-Player-Omniture-static | Brightcove-Player-Omniture-static/Framework<br>Brightcove-Player-Omniture-static/XCFramework |
| Brightcove-Player-Pulse | Brightcove-Player-Pulse/Framework<br>Brightcove-Player-Pulse/XCFramework |
| Brightcove-Player-SSAI | Brightcove-Player-SSAI/Framework<br>Brightcove-Player-SSAI/XCFramework |
| Brightcove-Player-OpenMeasurement | - |

#### CocoaPods Podspec names (since release 6.12.0)

Release 6.12.0 of the Brightcove Player SDK updates the `Brightcove-Player-FreeWheel` and `Brightcove-Player-Omniture` podspecs to install the dynamic version of `BrightcovePlayerSDK`. A `-static` podspec is available some plugins which will install the static version of `BrightcovePlayerSDK` along with the static version of the plugin framework itself.

Podspec Name  |  Framework Type  |  Dependency
------------- | ------------- | -------------
Brightcove-Player-Core | dynamic | -
Brightcove-Player-Core-static | static  | -
Brightcove-Player-FreeWheel | dynamic | Brightcove-Player-Core for iOS,<br/>Brightcove-Player-Core for tvOS
Brightcove-Player-GoogleCast | static | Brightcove-Player-Core
Brightcove-Player-GoogleCast-static | static | Brightcove-Player-Core-static
Brightcove-Player-IMA | dynamic | Brightcove-Player-Core
Brightcove-Player-Omniture | static | Brightcove-Player-Core
Brightcove-Player-Omniture-static | static | Brightcove-Player-Core-static
Brightcove-Player-Pulse | dynamic | Brightcove-Player-Core
Brightcove-Player-SSAI | dynamic | Brightcove-Player-Core,<br/>Brightcove-Player-OpenMeasurement (only for Open Measurement)
Brightcove-Player-OpenMeasurement (available since 6.10.0) | dynamic | -


## FairPlay

Support for FairPlay-protected videos is integrated into the core _BrightcovePlayerSDK_ framework. Refer to the [FairPlay guide](FairPlay.md) for full details about using FairPlay with the Brightcove Native Player SDK.

## Sidecar Subtitles

Support for Sidecar Subtitles is integrated into the core _BrightcovePlayerSDK_ framework. For full details about using Sidecar Subtitles with the Brightcove Native Player SDK, refer to the [Sidecar Subtitles guide](SidecarSubtitles.md).

## Video Downloads and Offline Playback

Since release 6.0.0, the Brightcove Native Player SDK allows you to download HLS videos, including those protected with FairPlay encryption, for playback later, whether online or offline. Refer to the app developer's guide for full details:

[iOS App Developer's Guide to Video Downloading and Offline Playback with FairPlay](OfflinePlayback.md)

## Installation

The Brightcove Player SDK provides installation packages for iOS and tvOS as static and a dynamic libraries packaged as Frameworks and XCFrameworks. Deployment is supported on iOS 11.4 and above.

### CocoaPods

You can use [CocoaPods][cocoapods] to add the Brightcove Player SDK to your project. You can find the latest `Brightcove-Player-Core` podspec [here][podspecs]. The podspec supports both iOS and tvOS.

When using Brightcove CocoaPods in your project, add `source 'https://github.com/brightcove/BrightcoveSpecs.git'` to the start of your Podfile.

Specifying the default pod `Brightcove-Player-Core` will install the dynamic library Framework. To install the static framework, append `-static` like this: `pod 'Brightcove-Player-Core-static'`. To install XCFrameworks, append the `/XCFramework` subspec to the pod name.

#### Dynamic Framework example:

```bash
source 'https://github.com/CocoaPods/Specs'
source 'https://github.com/brightcove/BrightcoveSpecs.git'

platform :ios, '11.4'
use_frameworks!

target 'MyVideoPlayer' do
  pod 'Brightcove-Player-Core'
end
```

#### Static Framework example:

```bash
source 'https://github.com/CocoaPods/Specs'
source 'https://github.com/brightcove/BrightcoveSpecs.git'

platform :ios, '11.4'
use_frameworks!

target 'MyVideoPlayer' do
  pod 'Brightcove-Player-Core-static'
end
```

#### XCFramework example:

The XCFramework can be installed by appending the `/XCFramework` subspec to the pod.

```bash
source 'https://github.com/CocoaPods/Specs'
source 'https://github.com/brightcove/BrightcoveSpecs.git'

platform :ios, '11.4'
use_frameworks!

target 'MyVideoPlayer' do
  pod 'Brightcove-Player-Core/XCFramework'
  pod 'Brightcove-Player-Core-static/XCFramework'
end
```

When updating your installation, it's a good idea to refresh the local copy of your BrightcoveSpecs repository so that you have the latest podspecs locally, just as you would update your CococaPods master repository. Typically if you run `pod update` in Terminal this will happen automatically, or alternatively you can update explicitly with `pod repo update`.

### Manual Installation

To add the Brightcove Player SDK to your project manually:

1. Download the latest zipped release from our [release page][release].
1. Add `BrightcovePlayerSDK.framework` or `BrightcovePlayerSDK.xcframework` to your project. Be sure to use the version corresponding to your target, iOS or tvOS.
1. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the path to the framework. This should have been done automatically unless the framework is stored under a different root directory than your project.
1. On the "General" tab of your application target, add the following to the "Frameworks, Libraries, Embedded Content" section:
    * `BrightcovePlayerSDK.framework`  / `BrightcovePlayerSDK.xcframework`
1. (**Dynamic Framework** only) On the "General" tab of your application target, add 'BrightcovePlayerSDK.framework' to the "Embedded Binaries" section.
1. (**Dynamic Framework** only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcovePlayerSDK.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission. This step is no longer necessary when using XCFramework.
1. (**Static Framework** only) On the "Build Settings" tab of your application target, add `-ObjC` to the "Other Linker Flags" build setting.
1. (**Static Framework** only) Locate the file `BCOVPUIResources.bundle` within the `BrightcovePlayerSDK.framework` and drag it directly into your project listing so that the bundle file becomes a part of your app. After dragging the file, be sure to add it to your app's build target when prompted to do so. Once your app is built, the bundle file should reside in the app at the same level as the app's Info.plist file. The bundle file includes the font file that supplies some of the `BrightcovePlayerUI` interface elements, but it does not need to be listed in the plist itself. When using XCFramework, the `BrightcovePlayerSDK` can be found in the ios-arm64 folder.
1. (**Universal Framework** only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcovePlayerSDK.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission.
1. (**Apple Silicon with Universal Framework** only) On the "Build Settings" tab of your application target:
    * Ensure that `arm64` has been added to your "Excluded Architectures" build setting for `Any iOS Simulator SDK`.

For reference, here are all the SDK components and corresponding URLs to help you locate and download the latest releases:

Component  | URL
--------------------------- | ----------------------------------------------
Brightcove-Player-Core | <https://github.com/brightcove/brightcove-player-sdk-ios/releases>
Brightcove-Player-FreeWheel | <https://github.com/brightcove/brightcove-player-sdk-ios-fw/releases>
Brightcove-Player-IMA | <https://github.com/brightcove/brightcove-player-sdk-ios-ima/releases>
Brightcove-Player-Omniture | <https://github.com/brightcove/brightcove-player-sdk-ios-omniture/releases>
Brightcove-Player-Pulse | <https://github.com/brightcove/brightcove-player-sdk-ios-pulse/releases>
Brightcove-Player-SSAI | <https://github.com/brightcove/brightcove-player-sdk-ios-ssai/releases>

### Swift Package Manager

To add the Brightcove Player SDK to your project with Swift Package Manager: 

1. Select the "Package Dependencies" tab for your Project.
1. Click the "+" button.
1. In the "Search or Enter Package URL" field enter `https://github.com/brightcove/brightcove-player-sdk-ios.git`
1. When the UI updates click the "Add Package" button.
1. After Xcode processess the repo you'll be prompted to "Choose Package Products" ensure that your app target is selected and click the "Add Package" button.

*Note: Only the dynamic XCFramework is supported for Swift Package Manager.*

### Imports

The Brightcove Player SDK for iOS can be imported into code a few different ways:

```
@import BrightcovePlayerSDK;

// or...
#import <BrightcovePlayerSDK/BrightcovePlayerSDK.h>

// or...
#import <BrightcovePlayerSDK/[specific-class].h>
```
    
[cocoapods]: https://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-Core
[release]: https://github.com/brightcove/brightcove-player-sdk-ios/releases

## Quick Start

Playing video with the Brightcove Player SDK for iOS:

    // ** Customize these values with your own account information **
    static NSString * const kViewControllerPlaybackServicePolicyKey = @"...";
    static NSString * const kViewControllerAccountID = @"...";
    static NSString * const kViewControllerVideoID = @"...";
    
    BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    id<BCOVPlaybackController> controller = [manager createPlaybackController];
    self.controller = controller; // store this to a strong property
    [self.view addSubview:controller.view];  
     
    BCOVPlaybackService *service = [[BCOVPlaybackService alloc] initWithAccountId:kAccountId
                                                                        policyKey:kPlaybackServicePolicyKey];
    [service findVideoWithVideoID:kViewControllerVideoID
                       parameters:nil
                       completion:^(BCOVVideo    *video,
                                    NSDictionary *jsonResponse,
                                    NSError      *error) {
                                    
                                        [controller setVideos:@[ video ]];
                                        [controller play];
                                    
                                    }];

You need to keep the controller from being automatically released at the end of the method. A common way to do this is to store a reference to the controller in a strong instance variable.

## Built-in PlayerUI Controls

Since version 5.1.0, the Brightcove PlayerUI is fully integrated into the Core SDK framework. PlayerUI provides a fully-featured set of controls for playback and advertising, right out of the box.

The PlayerUI is quick to set up, displays ad controls for SSAI, Pulse and FreeWheel, and can be customized by creating your own layouts.

## Setting Up PlayerUI Controls

Follow the guidelines below for setting up the PlayerUI controls.

Create a property in your UIViewController to keep track of the BCOVPUIPlayerView. The BCOVPUIPlayerView will contain both the Playback Controller's view, and the controls view.

    // PlayerUI's Player View
    @property (nonatomic) BCOVPUIPlayerView *playerView;

Create the BCOVPUIBasicControlView, and then the BCOVPUIPlayerView. This is where we associate the Playback Controller (and thus all the videos it plays) with the controls.

    // Create and configure Control View.
    BCOVPUIBasicControlView *controlView = [BCOVPUIBasicControlView basicControlViewWithVODLayout];
    self.playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:self.playbackController options:nil controlsView:controlView];
    // Add BCOVPUIPlayerView to your video view.
    [self.videoView addSubview:self.playerView];

You'll need to set up the layout for the player view, you can do this with Auto Layout or the older Springs & Struts approach. 

### Springs & Struts

Set the player view to match the video container from your layout (`videoView`) when it resizes.

    self.playerView.frame = self.videoView.bounds;
    self.playerView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;  

### Auto Layout

Set the `translatesAutoresizingMaskIntoConstraints` on BCOVPUIPlayerView to `NO`.

    self.playerView.translatesAutoresizingMaskIntoConstraints = NO;

Then add the constraints for the layout; setting the top, right, left and bottom anchors of your BCOVPUIPlayerView to equal that of `videoView` 

    [NSLayoutConstraint activateConstraints:@[
                                              [self.playerView.topAnchor constraintEqualToAnchor:self.videoView.topAnchor],
                                              [self.playerView.rightAnchor constraintEqualToAnchor:self.videoView.rightAnchor],
                                              [self.playerView.leftAnchor constraintEqualToAnchor:self.videoView.leftAnchor],
                                              [self.playerView.bottomAnchor constraintEqualToAnchor:self.videoView.bottomAnchor],
                                              ]];

**Reminder:** The PlayerUI uses a small font file for various graphics. If you are installing the static framework, and not using CocoaPods, be sure to add the file `bcovpuiiconfont.ttf` from the `BrightcovePlayerSDK.framework` bundle directly to your project listing so that the font file is copied into the app bundle

## BCOVPUIPlayerViewOptions

The `BCOVPUIPlayerViewOptions` class allows you to customize some BCOVPlayerUI behavior at initialization. You can customize the following:

* `jumpBackInterval` The time in seconds the player will seek back when the jump back button is pressed.
* `hideControlsInterval` The time in seconds after the last touch event, before the controls are hidden.
* `hideControlsAnimationDuration` The time in seconds it takes for the controls to animate to hidden.
* `showControlsAnimationDuration` The time in seconds it takes for the controls to animate to visible.
* `learnMoreButtonBrowserStyle` Setting that determines if tapping the "Learn More" button on an ad will display the clickthrough link in an external browser (default setting) or an internal browser.
* `presentingViewController` The UIViewController subclass to use for presenting other view controllers (like the closed caption selection view controller).
* `automaticControlTypeSelection` Whether or not you want the `BCOVPUIPlayerView` to pick a `BCOVPUIBasicControlView` type automatically based on the media type. When this value is set to `YES` the `BCOVPUIBasicControlView` property passed into the `BCOVPUIPlayerView` initializer will be ignored. 
    * **Video + Audio Streams**
        * VOD streams will use `basicControlViewWithVODLayout`
        * Live streams will use `basicControlViewWithLiveLayout`
        * Live DVR streams will use `basicControlViewWithLiveDVRLayout`
    * **Audio-Only Streams**
        * VOD streams will use `basicControlViewWithAODLayout`
        * Live streams will use `basicControlViewWithLiveAudioLayout`
        * Live DVR streams will use `basicControlViewWithLiveDVRAudioLayout`

Options can be set using the following method:

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackController];

        BCOVPUIPlayerViewOptions *options = [[BCOVPUIPlayerViewOptions alloc] init];
        options.jumpBackInterval = 5;

        BCOVPUIPlayerView *playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:playbackController options:options];

## Supplied Layouts

Three layouts are provided to support different types of video:

- `BCOVPUIControlLayout basicVODControlLayout` is a basic layout for general on-demand video streams.

- `BCOVPUIControlLayout basicLiveControlLayout` is a layout for live video.

- `BCOVPUIControlLayout basicLiveDVRControlLayout` is a layout for live video streams with DVR controls.

You typically set a new layout immediatley after your `BCOVPUIPlayerView` is created, but you can also set a new layout at any time. For example, you can set a new VOD layout like this:

	playerView.controlsView.layout = [BCOVPUIControlLayout basicVODControlLayout]

## Custom Layouts

In addition to the default layouts, you can create your own highly customized layouts by instantiating a new `BCOVPUIControlLayout` with your own design.

1. First, create the controls that will go in your layout using `BCOVPUIBasicControlView layoutViewWithControlFromTag:width:elasticity:`. Each control is packaged in a `BCOVPUILayoutView` that determines the control spacing.

2. You can set the `width` of each layout view to the default width (which is based on the type of control), or you can specify your own width.

3. Use the `elasticity` argument to determine how much the layout view containing the control reizes its width to fill the control bar.
	- An elasticity of zero means the size of the layout view will be fixed.
	- An elasticity value greater than zero determines how much the layout view will grow to fill available space relative to all other elastic views in that control bar. A layout view with an elasticity value of 2.0 will grow twice as fast as a layout view with an elasticity value of 1.0. Typically a row of layout views will have at least one control with an elasticity greater than zero.

Here are examples of creating a variety of basic controls.

	// Create various standard layout views
	// Standard play/pause button
    BCOVPUILayoutView *playbackLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonPlayback width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

	// Standard jump back button
    BCOVPUILayoutView *jumpBackButtonLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonJumpBack width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

	// Current time indicator
    BCOVPUILayoutView *currentTimeLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagLabelCurrentTime width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

	// Time separator - typically the '/' character
    BCOVPUILayoutView *timeSeparatorLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagLabelTimeSeparator width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

	// Video duration label
    BCOVPUILayoutView *durationLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagLabelDuration width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

	// Slider bar used for seeking through the video
	// The elasticity is set to 1 so that it can resize to fill available space
    BCOVPUILayoutView *progressLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagSliderProgress width:kBCOVPUILayoutUseDefaultValue elasticity:1.0];

	// Closed caption button
    // This button is initially hidden ('removed'), and will be shown
    // if closed captions or audio tracks are available.
    BCOVPUILayoutView *closedCaptionLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonClosedCaption width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];
    closedCaptionLayoutView.removed = YES;

    // The full-screen button
    BCOVPUILayoutView *screenModeLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagButtonScreenMode width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];

	// AirPlay button
    // This button is initially hidden ('removed'), and will be shown
    // if AirPlay devices are available.
    BCOVPUILayoutView *externalRouteLayoutView = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewExternalRoute width:kBCOVPUILayoutUseDefaultValue elasticity:0.0];
    externalRouteLayoutView.removed = YES;

	// Empty view - used as a spacer
    BCOVPUILayoutView     *spacerLayoutView1 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:1.0 elasticity:1.0];

	// Empty view - used as a spacer
    BCOVPUILayoutView *spacerLayoutView2 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:1.0 elasticity:1.0];

	// Empty view - will have a custom UIImageView added as a subview
    BCOVPUILayoutView *logoLayoutView1 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:80.0 elasticity:1.0];

	// Empty view - will have a custom UIImageView added as a subview
    BCOVPUILayoutView *logoLayoutView2 = [BCOVPUIBasicControlView layoutViewWithControlFromTag:BCOVPUIViewTagViewEmpty width:36.0 elasticity:0.0];


Note that you can also create an empty layout view, into which you can place your own view (logo, control, nothing, etc.). This code shows how to place a `UIImage` logo inside the logoLayoutView1 we created above.

    // Create logo image inside an image view for display in control bar.
    UIImage *logoImage1 = [UIImage imageNamed:@"myLogo"];
    UIImageView *logoImageView1 = [[UIImageView alloc] initWithImage:logoImage1];

    logoImageView1.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    logoImageView1.contentMode = UIViewContentModeScaleAspectFit;
    logoImageView1.frame = logoLayoutView1.frame;

    // Add image view to our empty layout view.
    [logoLayoutView1 addSubview:logoImageView1];

Now that there are various controls packaged in layout views, they are ordered into arrays, each of wihch represents a single line of controls, i.e. a control bar. Note that you can have different layouts for portrait and landscape orientations, so you will typically set up two different arrays of control bars.

In the standard layout for landscape orientation, controls are arranged in a single array, and then that array is stored in another array representing the entire set of controls.

            NSArray *standardLayoutLine1 = @[ playbackLayoutView, jumpBackButtonLayoutView, currentTimeLayoutView, timeSeparatorLayoutView, durationLayoutView, progressLayoutView, spacerLayoutView1, logoLayoutView1, spacerLayoutView2, closedCaptionLayoutView, screenModeLayoutView, externalRouteLayoutView ];
            NSArray *standardLayoutLines = @[ standardLayoutLine1 ];

In the compact layout for portrait orientation, two arrays of controls are created, one for each line. These arrays are packaged into another array representing the compact layout.

Note that the exact same objects are used for most of the controls in each layout. When this is done, and you switch between portrait and landscape orientations, the object will be moved to its new position using smooth animation.


            NSArray *compactLayoutLine1 = @[ currentTimeLayoutView, progressLayoutView, durationLayoutView ];
            NSArray *compactLayoutLine2 = @[ playbackLayoutView, jumpBackButtonLayoutView, spacerLayoutView1, closedCaptionLayoutView, screenModeLayoutView, externalRouteLayoutView, logoLayoutView2 ];
            NSArray *compactLayoutLines = @[ compactLayoutLine1, compactLayoutLine2 ];

Finally, now that there are two layout configurations (one for full width, and one for compact width), you can create a new `BCOVPUIControlLayout` object, and set it in the player's control view.

            BCOVPUIControlLayout *customLayout = [[BCOVPUIControlLayout alloc] initWithStandardControls:standardLayoutLines compactControls:compactLayoutLines];
			playerView.controlsView.layout = customLayout;

If you have controls that you need to show or hide frequently, you can set the `removed` property on that control's layout view. When you have changed your controls, call `setNeedsLayout` on the playerView's controlView:

		logoLayoutView1.removed = YES;
	    [playerView.controlsView setNeedsLayout];

You can also customize several general `BCOVPUIControlLayout` properties:

- `controlBarHeight` sets the size of each row of controls.
- `horizontalItemSpacing` sets the spacing between each `BCOVPUILayoutView` in each control bar.
- `compactLayoutMaximumWidth` determines which set of controls is used. If the control view is smaller than `compactLayoutMaximumWidth`, the compact control set will be used, otherwise the standard controls will be used.

To change the set of controls that are displayed, you must create and install a new `BCOVPUIControlLayout`. New controls can be installed at any time.


## More Customization Examples

For more examples of PlayerUI customization, you can look at the sample code in the PlayerUI folder of the BrightcoveOS GitHub repository:

[https://github.com/BrightcoveOS/ios-player-samples][github]

[github]: https://github.com/BrightcoveOS/ios-player-samples

## Built-in TV Player Controls for tvOS

The Brightcove Native Player SDK includes built-in controls for playback in tvOS on Apple TV. For full details about using the built-in TV Player UI with the Brightcove Native Player SDK, see our [TV Player guide](TVPlayer.md).

## AirPlay

Enable AirPlay functionality by setting the `setAllowsExternalPlayback` property on your `BCOVPlaybackController` to `true`. The AirPlay button will be displayed in the playback controls if AirPlay devices are found on your network.

Currently, IMA is the only ad plugin that supports AirPlay and only when using pre-roll and/or post-roll ads. Using AirPlay with the Pulse, SSAI or FreeWheel ad plugins may result in unexpected behavior.

If you also want to support AirPlay 2 and allow for multiple devices to be selected for audio output you will have to do a few additional things. First, you'll need to configure AVAudioSession so that you can set the `routeSharingPolicy`. For example:

```
[AVAudioSession.sharedInstance setCategory:AVAudioSessionCategoryPlayback mode:AVAudioSessionModeMoviePlayback routeSharingPolicy:AVAudioSessionRouteSharingPolicyLongForm options:0 error:nil];
```
You will also need to configure at least one playback command via `MPRemoteCommandCenter`. At the very least you'll want to configure both the `pauseCommand` and `playCommand`. For Example:

```
MPRemoteCommandCenter *center = MPRemoteCommandCenter.sharedCommandCenter;

[center.pauseCommand addTargetWithHandler:^MPRemoteCommandHandlerStatus(MPRemoteCommandEvent * _Nonnull event) {
[self.playbackController pause];
return MPRemoteCommandHandlerStatusSuccess;
}];

[center.playCommand addTargetWithHandler:^MPRemoteCommandHandlerStatus(MPRemoteCommandEvent * _Nonnull event) {
[self.playbackController play];
return MPRemoteCommandHandlerStatusSuccess;
}];
```
Devices that are running iOS 11 or later will take advantage of `AVRoutePickerView` which has two delegate methods. These delegate methods are passed through to `BCOVPUIPlayerViewDelegate`. The methods are:

```
- (void)routePickerViewWillBeginPresentingRoutes:(AVRoutePickerView *)routePickerView;
- (void)routePickerViewDidEndPresentingRoutes:(AVRoutePickerView *)routePickerView;
```

The `AVRouteDetector` used to discover AirPlay routes is available on the `BCOVPUIBasicControlView` object so you can enable or disable its `routeDetectionEnabled` property as needed. 

Per Apple's documentation: "*Route detection significantly increases power consumption and must be turned off when it's no longer needed.*"

```
// Objective-C
self.playerView.controlsView.routeDetector.routeDetectionEnabled = NO;

// Swift
playerView?.controlsView.routeDetector.isRouteDetectionEnabled = false
```

For more information on incorporating AirPlay 2 into your app please see the [Getting Airplay 2 into Your App](https://developer.apple.com/documentation/avfoundation/media_playback_and_selection/getting_airplay_2_into_your_app?language=objc) documentation.

## Video 360

The Native Player SDK includes support for interactively displaying 360 degree spherical videos. 360 videos should be tagged with a "projection" field property containing the value "equirectangular". These videos will be loaded and played in the same way as other videos, but they will be displayed in a CAMetalLayer instead of an AVPlayerLayer.

Note: "equirectangular" is the only projection format supported for 360 source videos at this time.

The PlayerUI also has built-in support for Video 360, providing default panning gestures, gyroscopic motion detection for the view, and a new Video 360 button that appears when a Video 360 asset is playing. This button appears only on iPhones, and lets you toggle betwen the normal view and a "VR Goggles" view, where the screen is split in two, with the same scene rendered for each eye so that the device can be used in a head-mounted configuration. On iPads no Video 360 button is needed because there is only a single mode of operation: motion detection with panning gesture support.

Supporting Video 360 is as simple as playing a video. When the "projection" field property is detected, the Native Player SDK will automatically handle setting up and displaying the video in Metal, and installing the Video 360 button when appropriate.

If you are playing 360 videos outside of Video Cloud, be sure to add a "projection" property to the `BCOVVideo` object with the value "equirectangular".

To provide the best user experience with the VR Goggles mode, you should use a `BCOVPUIPlayerViewDelegate` method to detect when this mode is enabled. This allows you to force the device into landscape orientation (since that is the only orientation that makes sense for a VR Goggles view).

The following code shows how you could handle a forced orientation change when switching back and forth between a normal 360 view, and VR Goggles mode.

```
	// Set this to YES when displaying a VR goggles video
	@property (nonatomic) BOOL landscapeOnly;

	// UIViewController override:
   // Lets us control the orientation of the device
	- (UIInterfaceOrientationMask)supportedInterfaceOrientations
	{
	    if (self.landscapeOnly)
	    {
	        return UIInterfaceOrientationMaskLandscape;
	    }
	
	    return UIInterfaceOrientationMaskAll;
	}

    // BCOVPUIPlayerViewDelegate method
	- (void)didSetVideo360NavigationMethod:(BCOVPUIVideo360NavigationMethod)navigationMethod
	                       projectionStyle:(BCOVVideo360ProjectionStyle)projectionStyle
	{
	    switch (projectionStyle)
	    {
	        case BCOVVideo360ProjectionStyleNormal:
	            NSLog(@"BCOVVideo360ProjectionStyleNormal");
	            self.landscapeOnly = NO;
	            break;
	
	        case BCOVVideo360ProjectionStyleVRGoggles:
	            NSLog(@"BCOVPUIVideo360NavigationDeviceMotionTracking");
	            
	            self.landscapeOnly = YES;
	            
	            {
	                UIDeviceOrientation currentDeviceOrientation = [UIDevice currentDevice].orientation;
	                switch (currentDeviceOrientation)
	                {
	                    case UIDeviceOrientationLandscapeLeft:
	                    case UIDeviceOrientationLandscapeRight:
	                        // all good
	                        break;
	                    default:
	                    {
	                        // switch orientation
	                        NSNumber *value = [NSNumber numberWithInt:UIInterfaceOrientationLandscapeLeft];
	                        [[UIDevice currentDevice] setValue:value forKey:@"orientation"];
	                        break;
	                    }
	                }
	            }
	            break;
	    }
	    
	    [UIViewController attemptRotationToDeviceOrientation];
	}
```
The PlayerUI will install gestures to handle navigation around the 360 video, but if you are using your own controls you can set the view parameters of the virtual camera yourself. The `BCOVPlaybackController` protocol's `viewProjection` property lets you set these parameters. The property is a `BCOVVideo360ViewProjection` class with basic virtual camera settings like `pan`, `tilt`, and `zoom`. To change settings, make a copy of the current instance, change the settings on the new instance, and then assign it back to the `viewProjection` property.

## Architectural Overview

![Architectural Overview 1](architecture01.png)

The entry point to the Brightcove Player SDK for iOS is the [`BCOVPlayerSDKManager`][manager] singleton object. This Manager handles registration of plugin components and some other housekeeping tasks, but it primarily serves as an object factory. Your app's view controller obtains a reference to the Manager, and uses it to create a [`BCOVPlaybackController`][controller]. The playback controller's `view` property exposes a UIView containing the AVPlayerLayer object that ultimately presents your video content on the screen. The playback controller also accepts a [`BCOVPlaybackControllerDelegate`][delegate], which you can implement to respond to various video playback events.

The playback controller offers methods and properties to affect playback of the current video. However, internally, the playback controller delegates to a [`BCOVPlaybackSession`][session] object. Playback sessions do the actual work of preparing and playing video content, and contain the video's metadata and `AVPlayer`. The playback controller has mechanisms to advance from the current playback session to the next playback session, either automatically at the end of a video, or manually with a method call. Once the playback controller has advanced to a new session, the previous session is discarded and cannot be used again.

There are two other elements of the playback controller: a [`BCOVPlaybackSessionProvider`][provider], and a list of [`BCOVPlaybackSessionConsumer`][consumer]s. As the name would suggest, the playback session provider is responsible for creating playback sessions and delivering them to the playback controller. The playback controller then delivers the session to each of the playback session consumers in the list. Both the session provider and session consumer APIs are designed for use by plugin developers, and are not detailed in this document.

In addition to the playback functionality provided by the classes described above, there are a handful of value classes. These are used to hold data specific to the Player SDK for iOS. Each of these is described in more detail in its own section below.

[manager]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlayerSDKManager.h
[controller]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackController.h
[session]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackSession.h
[provider]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackSessionProvider.h
[service]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackService.h

## Play, Pause, and Seek

The Brightcove Player SDK for iOS provides play, pause, and seek methods on the `BCOVPlaybackController`. **It is important to use these methods instead of using the AVPlayer equivalent.** In their default implementations, these objects forward the calls directly to the corresponding method on the AVPlayer. However, if you are using plugins, they may override the default behavior to add functionality. For example, if using an advertising plugin, calling `[BCOVPlaybackController play]` the first time might cause pre-roll to play before starting the content. To find out more about how a plugin may override the default behavior, please refer to each plugin README.md or by checking for a category extension on `BCOVSessionProviderExtension` that the plugin may add.

*Calling play, pause, or seek on the AVPlayer directly may cause undefined behavior.*

## Playback Rate

To set a custom playback rate for AVPlayer you can use the `playbackRate` property on `BCOVPlaybackController`. **It is important that you set the playback rate using this property instead of setting it directly on AVPlayer.** 

Attempting to set `playbackRate` to a value of 0 or below will result in the value being set to 1.0. If AVPlayer's `currentItem` does not support `canPlaySlowForward` (for values less than 1) or `canPlayFastForward` (for values greater than 1) then the default playback rate of 1.0 will be used. Ad playback will not be affected.

If a custom value has been set for `playbackRate` the `audioTimePitchAlgorithm` for each `AVPlayerItem` will be set to `AVAudioTimePitchAlgorithmTimeDomain`. Alternatively you can set your own value for `audioTimePitchAlgorithm` like this:

```
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didReceiveLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)lifecycleEvent
{
    if ([lifecycleEvent.eventType isEqualToString:kBCOVPlaybackSessionLifecycleEventReady])
    {
        session.player.currentItem.audioTimePitchAlgorithm = AVAudioTimePitchAlgorithmVarispeed;
    }
}
```

You can read more about `audioTimePitchAlgorithm` [here](https://developer.apple.com/documentation/avfoundation/avaudiotimepitchalgorithm).

## Preloading Videos

If desired you may choose to preload upcoming videos in a playlist. One possible approach is to double-buffer a list of videos using two playback controllers, for example:

1. Initialize two playback controllers
1. Set up your player view and assign one of the two playback controllers to the playerView's playbackController property (now your active playback controller)
1. Once your playlist is ready assign the playlist (or just the videos array property) to a property as we'll need to access each video separately
1. Get the first video in the videos array and give it to the active playback controller (`[self.playbackController1 setVideos:@[self.videos.firstObject]]`)
1. Utilizing the `playbackController:didProgressTo:` delegate method of the playback controller determine if the current video has progressed far enough to where you want to begin preloading the next video
1. Once you determine it's time to preload get the next video in the videos array and set it on the alternate playback controller
1. Once the current video has completed set the playbackController on the playerView to the alternate playback controller
1. Rinse and repeat steps 5-7

For a working example you may download our [VideoPreloading](https://github.com/BrightcoveOS/ios-player-samples/tree/master/Player/VideoPreloading) sample app from our [Player Samples](https://github.com/BrightcoveOS/ios-player-samples) repository.

**Note: You might want to take into account the amount of memory available on the client's device and speed of their connection. If they are not on Wifi, preloading a video may affect the current video's network resources.**

## Source Selection (HLS, MP4, HTTP/HTTPS)

The Brightcove Player SDK for iOS provides clients the ability to attach multiple url and delivery types (`BCOVSource`) to a single video (`BCOVVideo`). For example, if your videos are being retrieved by the Playback Service, there may be a mix of HLS or MP4 renditions for a single video, along with HTTP and HTTPS versions.  Which one of these sources that get selected is determined by a source selection policy block. The default source selection policy will select the first HLS `BCOVSource` on each `BCOVVideo`, with HTTPS sources preferred over HTTP. 

Source selection can be overridden by creating a `BCOVBasicSessionProviderOptions` and using it to create a `BCOVBasicSessionProvider`. For example:

    BCOVPlayerSDKManager *sdkManager = [BCOVPlayerSDKManager sharedManager];
    
    BCOVBasicSessionProviderOptions *options = [[BCOVBasicSessionProviderOptions alloc] init];    
    options.sourceSelectionPolicy = <policy>
    
    id<BCOVPlaybackSessionProvider> provider = [sdkManager createBasicSessionProviderWithOptions:options];
    id<BCOVPlaybackController> playbackController = [sdkManager createPlaybackControllerWithSessionProvider:provider viewStrategy:nil];


If this default selection policy does not work for you, there are a few alternatives to selecting a source:

* If retrieving videos from Video Cloud via the Playback Service, before calling `-[BCOVPlaybackController setVideos:]`, use the update method on the `BCOVVideo` to only contain the source you want (see the "Values" section for more info).

* You can use the helper method `[BCOVBasicSourceSelectionPolicy sourceSelectionHLSWithScheme:scheme]` to create a policy that prefers a specific scheme. This is the method used to create the default source selection policy that prefers HTTPS.

* Similar to updating the video object, you may also implement your own source selection block.
        
        options.sourceSelectionPolicy = ^ BCOVSource *(BCOVVideo *video) {
        
           <Check video.sources for source>
           <Return source>

        };

Please be aware there are App Store limitations regarding the use of MP4 videos. Check the latest Apple Developer information for details.

## Setting a Preferred Bitrate

The Brightcove Player SDK for iOS provides a way to set the preferred bitrate for a video. You can create a BCOVPreferredBitrateConfig object that contains your desired bitrate options, along with some configuration for the view controller which is created to display the options. 

The title for the menu is optional. The bitrate options are an array of NSDictionary's with each dictionary having one key:value pair. The key will be used as the option name, and the value is an NSNumber with the bitrate for that option in bps (bits per second). The bitrates you enter are values that can be mapped to bitrates of the renditions of your video assets. You can learn more about renditions in [Ingest Profiles Best Practices]. 

Here is an example:

    BCOVPUIPlayerViewOptions *options = [[BCOVPUIPlayerViewOptions alloc] init];
    options.preferredBitrateConfig = [BCOVPreferredBitrateConfig configWithMenuTitle:@"Select an Option" andBitrateOptions:@[@{@"Auto":@(0)}, @{@"Setting 1":@(aBitrateValue)}, @{@"Setting 2":@(aBitrateValue)}]];

When the end-user selects one of the options, the [preferredPeakBitRate] property of the current AVPlayerItem will be set to the option's value. If the video is in a playlist, the next video played will also have the preferredPeakBitRate value set. 

After setting a non-zero value for [preferredPeakBitRate] you may not notice a difference in quality until AVPlayer has reached the end of its current buffered cache.

You may additionally use the `configWithMenuTitle:bitrateOptions:andIndexofInitialSelection:` initializer that provides the ability to set the index of your preferred initial value. The index should correlate to the index of the desired option in the `bitrateOptions` array. 

You may additionally use the `setPreferredPeakBitRate:` method on your `BCOVPlaybackController` object to programatically set the preferred bitrate for the current and future sessions. 

NOTE: End-users must be given a way to return to the default value (0) of [preferredPeakBitRate]. You can do this by providing an option with a bitrate value of 0. If you do not provide a bitrate option of 0 an "Automatic" option will be appended to your list of options for the end-user.

Please see Apple's documentation on [preferredPeakBitRate] for more information.

[preferredPeakBitRate]:https://developer.apple.com/documentation/avfoundation/avplayeritem/1388541-preferredpeakbitrate
[Ingest Profiles Best Practices]:https://studio.support.brightcove.com/admin/ingest-profiles-best-practices.html

## Obtaining Content and Ad Playback Information

The Brightcove Player SDK for iOS provides two mechanisms for obtaining playback information. The playback controller provides a delegate property that implements [`BCOVPlaybackControllerDelegate`][delegate]. A delegate can implement these optional methods to get notified of playback metadata like progress, duration changes, and other events. If an ad plugin is installed, it may also use this delegate to provide information about [ad playback][adplayback]. The [lifecycle event][lifecycle] delegate method provides events to signal changes in playback state. For example, when a player goes from the paused state to the playing state, the lifecycle event delegate method will be called with the `kBCOVPlaybackSessionLifecycleEventPlay` event. The default Lifecycle events are declared in [`BCOVPlaybackSession`][lifecycleevents]. Plugins provided by Brightcove add additional lifecycle events which are defined in each plugin.

[adplayback]:https://github.com/brightcove/brightcove-player-sdk-ios/blob/fd5e766693e533854f202f270d3d62e32ceaae04/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVAdvertising.h#L120-L192
[lifecycle]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/fd5e766693e533854f202f270d3d62e32ceaae04/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackController.h#L630-L641
[lifecycleevents]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackSession.h

The playback controller allows for a single delegate. In many cases, this will be enough to retrieve information; the delegate implementations can disseminate values and events to different parts of the app as necessary. In cases where multiple delegates would be required, as is the case when developing a plugin, the [`BCOVPlaybackSessionConsumer`][consumer] delegates provide equivalent functionality to the [`BCOVPlaybackControllerDelegate`][delegate] methods, including [ad data][adconsumer].

[consumer]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/fd5e766693e533854f202f270d3d62e32ceaae04/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackController.h#L538-L655
[adconsumer]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/fd5e766693e533854f202f270d3d62e32ceaae04/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVAdvertising.h#L195-L259
[delegate]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/fd5e766693e533854f202f270d3d62e32ceaae04/ios/dynamic/BrightcovePlayerSDK.framework/Headers/BCOVPlaybackController.h#L667-L793

Here is an example of how one might use `BCOVPlaybackSessionConsumer` to create an analytics plugin:

    @interface XYZAnalytics : NSObject <BCOVPlaybackSessionConsumer>
    @end

    @implementation XYZAnalytics

    - (void)playbackSession:(id<BCOVPlaybackSession>)session didProgressTo:(NSTimeInterval)progress
    {
        //react to progress event
    }

    @end

To use the plugin:

    BCOVPlayerSDKManager *sdkManager = [BCOVPlayerSDKManager sharedManager];
    id<BCOVPlaybackController> controller = [sdkManager createPlaybackController];
    XYZAnalytics *analytics = [[XYZAnalytics alloc] init];
    [controller addSessionConsumer:analytics];
    
## Handling Network Interruptions and Slowdowns

When the application experiences network interruptions, the `AVPlayer` used by the `BCOVPlaybackController` may stop attempting to recover if the interruption lasts too long. If this occurs, the lifecycle delegate method will be called with a `kBCOVPlaybackSessionLifecycleEventFailedToPlayToEndTime` event. When this event occurs, playback **will not** recover automatically. In order to recover from this event, you will need to detect when the network recovers in your client code.  

Once you have determined that the network has recovered, you can use `- [BCOVPlaybackController resumeVideoAtTime:withAutoPlay:]` to re-initialize the player. You will need to keep track of where you want to resume to. The player will make its best effort to suppress lifecycle events and progress events, in order to prevent ads from replaying or from analytics being interfered with.

Upon calling `- [BCOVPlaybackController resumeVideoAtTime:withAutoPlay:]`, the player will send a lifecycle event of type `kBCOVPlaybackSessionLifecycleEventResumeBegin`. `kBCOVPlaybackSessionLifecycleEventResumeComplete` will be sent if this action succeeds, otherwise `kBCOVPlaybackSessionLifecycleEventResumeFail` will be sent.

You must wait before calling `- [BCOVPlaybackController resumeVideoAtTime:withAutoPlay:]` a second time until you have received either `kBCOVPlaybackSessionLifecycleEventResumeComplete` or `kBCOVPlaybackSessionLifecycleEventResumeFail` from the previous call. You may wish to impose a retry limit, before giving the user a message that their network is too unstable.

When the `AVPlayer` is still able to access the network, but the video stalls because the network is too slow, the lifecycle delegate method will be called with a `kBCOVPlaybackSessionLifecycleEventPlaybackStalled` event. When playback is able to resume, the lifecycle delegate method will be called with a `kBCOVPlaybackSessionLifecycleEventPlaybackRecovered` event. These events only cover the case where normal playback stopped and does not cover buffering that occurs during a seek or initial load of the video.

When the video is initially loading, when a seek occurs, or when playback stalls due to a slow network, the lifecycle delegate method will be called with a `kBCOVPlaybackSessionLifecycleEventPlaybackBufferEmpty` event.  When playback is able to resume,  the lifecycle delegate method will be called with a `kBCOVPlaybackSessionLifecycleEventPlaybackLikelyToKeepUp` event.

## Subclassing

Except where explicitly documented otherwise, none of the classes in the Player SDK for iOS are designed to be subclassed. Creating a subclass of any SDK class that is not explicitly designed to be subclassed, especially any of the value classes, could result in unpredictable behavior.

## Values

Also known as "model objects", these classes (`BCOVPlaylist`, `BCOVVideo`, `BCOVSource`, `BCOVCuePoint`, `BCOVCuePointCollection`) are used to represent data in the Player SDK for iOS. It is crucial to understand that these data types are treated as *values*, rather than *identities*. By this, we mean that if you have two instances of a value class which have the exact same data, they represent the same idea or value, even though they are technically two different objects at separate memory addresses. In other words, neither SDK code nor your client code should ever use identity comparisons ("pointer equality") with value objects. Instead, each value class implements `-isEqual:` and provides a class-specific equality method overload, either of which should be used instead.

This is bad:

    if (myVideo == session.video) // Could lead to bugs!
    
These are good (and functionally equivalent):

    if ([myVideo isEqualToVideo:session.video])
    if ([myVideo isEqual:session.video])

The internals of the Player SDK for iOS may do such things as memoize values or make defensive copies, so relying on the pointer address to check for equality will end up causing you pain.

Another quality of value classes in the Player SDK for iOS is that they are *immutable*. Once you have an instance of a value, you should not try to subvert this immutability in any way, as it may lead to unpredictable behavior. If in your code you wish to "modify" a value in some fashion, your only recourse is to create a new value. As a convenience to help clients obtain "modified" values, each of the value classes offers an `-update:` method which takes a block that allows you to operate on a mutable copy of the original value.

Here is an example of using this method to create a "modified" version of an existing video object, but with different properties:

    BCOVVideo *video1; // (properties include a key "foo" whose value is "bar")
    BCOVVideo *video2 = [video1 update:^(id<BCOVMutableVideo> mutable) {
        
        mutable.properties = @{ @"foo": @"bar" };
        
    }];
    
	NSLog(@"foo is %@", video1.properties[@"foo"]); // prints "foo is bar"
    NSLog(@"foo is %@", video2.properties[@"foo"]); // prints "foo is quux"
    
    // Both video1 and video2 are still immutable objects:
    video1.properties = otherDictionary; // causes compiler error
    video2.properties = otherDictionary; // causes compiler error


As you can see in the example, `video1` has not been changed by the `-update` method call. Instead, this method returns a copy of `video1`, except with the modifications made in the body of the block. You should never allow the mutable copy to escape the block (such as by assigning it to a `__block` variable), instead use the immutable object returned by the `-update` method after you have made your modifications.

## Retrieving Brightcove Assets Using the Playback Service

The playback service class, `BCOVPlaybackService`, provides functionality for retrieving your Brightcove video assets and playlists via the [Brightcove Playback API][PlaybackAPI] , including rich metadata such as text tracks, previews, and thumbnails. The following example shows how to retrieve a video with a video ID. Methods for retrieving a video or playlist with that video's reference ID are also available.

    [1] NSString *policyKey = <your-policy-key>;
        NSString *accountId = <your-account-id>;
        NSString *videoID = <your-video-id>;

        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
        id<BCOVPlaybackController> controller = [manager createPlaybackControllerWithViewStrategy:nil];
        [self.view addSubview:controller.view];  
     
        BCOVPlaybackService *playbackService = [[BCOVPlaybackService alloc] initWithAccountId:accoundId
                                                                                    policyKey:policyKey];
        [playbackService findVideoWithVideoID:videoID
                                   parameters:nil
                                   completion:^(BCOVVideo *video,
                                                NSDictionary *jsonResponse,
                                                NSError      *error) {

                                       [controller setVideos:@[ video ]];
                                       [controller play];

                                   }];

1. The playback service requests **policy key** for authentication. To learn more about policy key and how to obtain one, please refer to the [policy key documentation][PolicyKey].

**NOTE: If you are using the Playback Authorization Service please review the [section](#PlaybackAuthorizationService) of this README related to that feature.

### Playlist Paging

For ``BCOVPlaybackService` methods that return a playlist, you can request a partial playlist, or "pages" from the playlist by specifying a limit and offset parameter in the parameters dictionary. The limit specifies the maximum number of videos that will be returned, and the offset specifies the index into the playlist at which videos will be returned.

For example, if you have a playlist with 100 videos, you can request only 6 videos starting at video number 10 as follows:

```
    NSDictionary *parameters =
    @{
        @"limit": @6,
        @"offset": @10
    };

    [playbackService findPlaylistWithPlaylistID:playlistID
                                     parameters: parameters
                                     completion:^(BCOVPlaylist *playlist,
                                                  NSDictionary *jsonResponse,
                                                  NSError      *error) {

        [controller setVideos: playlist];
        [controller play];

    }];
```


[PlaybackAPI]: https://apis.support.brightcove.com/playback/getting-started/overview-playback-api.html
[PolicyKey]: https://apis.support.brightcove.com/policy/getting-started/policy-keys.html

## View Strategy

The `BCOVPlaybackController` object is constructed with a view strategy, which allows you, as the client of the SDK, to define the exact UIView object that is returned from the playback controller's view property. This is important when using plugins that affect the playback controller's view, such as an advertising plugin that overlays the video view with an ad view. 
Many apps will have no need to create a view strategy, and can simply pass `nil` when creating a new playback controller. This will create a standard video view in the playback controller.

The `BCOVPlaybackControllerViewStrategy` typedef aliases (and documents) this more complex block signature:

```objc
UIView *(^)(UIView *videoView, id<BCOVPlaybackController> playbackController);
```

This signature describes an Objective-C block that returns a UIView and takes two parameters: a UIView and a playback controller. The return value is the UIView object that the playback controller's view property will point to.
The first parameter is an UIView that contains the video layer, the UIView will show the video. The second parameter is the playback controller object to which the view strategy has been given, the playback controller can be used to add necessary session consumers such as video controls or ad controls.

Example of a view strategy implementation:

```objc
BCOVPlaybackControllerViewStrategy viewStrategy = ^(UIView *videoView, id<BCOVPlaybackController> playbackController) {

    // Create some custom controls for the video view,
    // and compose both into a container view.
    [1] UIView<BCOVPlaybackSessionConsumer> *myControlsView = [[MyControlsView alloc] init];
    [2] UIView *controlsAndVideoView = [[UIView alloc] init];
    [3] [controlsAndVideoView addSubview:videoView];
        [controlsAndVideoView addSubview:myControlsView];
    // Compose the container with an advertising view
    // into another container view.
    [4] UIView<BCOVPlaybackSessionConsumer> *adView = [[SomeAdPluginView alloc] init];
    [5] UIView *adAndVideoView = [[UIView alloc] init];
    [6] [adAndVideoView addSubview:controlsAndVideoView];
        [adAndVideoView addSubview:adView];
    [7] [playbackController addSessionConsumer:myControlsView];
        [playbackController addSessionConsumer:adView];
    // This container view will become `playbackController.view`.
    return adAndVideoView;
};
```
Breaking the code down into steps:
[1] Create a custom controls view that conforms to the `BCOVPlaybackSessionConsumer` protocol. `BCOVPlaybackSessionConsumer`protocol allows to receive basic playback information for each video in addition to advertising.
[2] Create a container view for the video view and custom controls.
[3] Add as a subview the video container and the custom controls. The hierarchy is composed in the same order that views are added.
[4] Create an ad controls view that conforms to the `BCOVPlaybackSessionConsumer` protocol.
[5] Create a container view for the video view and controls, and the advertising view.
[6] Add as a subview the video container and the ad controls view.
[7] Register the custom controls view and the ad controls view as session consumers using the playback controller object returned by the block.

There is one caveat to using a view strategy: you must not access the playback controller's `view` property from within the view strategy block. Since the block is being called *because* the playback controller's `view` property was accessed for the first time, accessing the `view` property again *within* the view strategy block will cause your program to crash.

## Playing Video In The Background

By default, when an iOS application is sent to the background, or the device is locked, iOS will pause any video that is playing. To change this behavior, set the `allowsBackgroundAudioPlayback` property of the `BCOVPlaybackController` object to `YES`. (The default value is `NO`, indicating playback will pause in the background.)

You should also follow the guidelines set by Apple in [Technical Q&A QA1668][tqa1668] to set the proper background modes and audio session category for your app.

It's important that the `AVPlayerLayer` be detached from the `AVPlayer` before the app is switched to the background (and reattached when the app returns to the foreground). The Brightcove Player SDK will handle this for you when `allowsBackgroundAudioPlayback` is set to `YES`.

Finally, when playing background videos (and particularly when using playlists), you should use the iOS `MPRemoteCommandCenter` API to give the user playback control on the lock screen and in the control center.

[tqa1668]: https://developer.apple.com/library/ios/qa/qa1668

## Picture in Picture

To enable Picture-in-Picture in your application, set the `showPictureInPictureButton` property of the `BCOVPUIPlayerViewOptions` object to `YES` when instantiating your `BCOVPUIPlayerView` object. The Picture-in-Picture button will then be displayed in the controls bar on any device that support it. 

For Picture-in-Picture to work properly you will need to ensure that the `Audio, AirPlay, and Picture in Picture` mode is turned in the `Background Modes` section of the target Capabilities tab of your project. You should also follow the guidelines set by Apple in [Technical Q&A QA1668][tqa1668] to set the proper background modes and audio session category for your app.

The `AVPictureInPictureControllerDelegate` methods are passed along via `BCOVPUIPlayerViewDelegate`. These methods are:

```
- (void)pictureInPictureControllerDidStartPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;
- (void)pictureInPictureControllerDidStopPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;
- (void)pictureInPictureControllerWillStartPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;
- (void)pictureInPictureControllerWillStopPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController failedToStartPictureInPictureWithError:(NSError *)error
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:(void (^)(BOOL))completionHandler;
```

See Apple's [AVPictureInPictureControllerDelegate](https://developer.apple.com/documentation/avkit/avpictureinpicturecontrollerdelegate) documentation for more information.

To implement your own Picture-in-Picture behavior, leave the `allowsBackgroundAudioPlayback` property of `BCOVPlaybackController` set to `false`, and keep the `pictureInPictureActive` property of `BCOVPlaybackController` updated with the Picture-in-Picture status. If you are using the `AVPictureInPictureController`, you can use the `pictureInPictureControllerDidStartPictureInPicture:` and `pictureInPictureControllerDidStopPictureInPicture:` delegate methods to update this property.

You can read more about implemeneting Picture-in-Picture in Apple's [Adopting Picture in Picture in a Custom Player](https://developer.apple.com/documentation/avkit/adopting_picture_in_picture_in_a_custom_player) documentation.

Using a playlist of videos with mixed formats with picture-in-picture will result in the picture-in-picture window closing between each video.

iOS and iPadOS 14 introduced automatic Picture-in-Picture behavior which can be toggled on/off in `Settings > General > Picture in Picture`. In order for this feature to work as expected the player view must be equal to the width of the screen and the height must have a ratio of at least 0.57 to the width (16:9 or larger). If the width or height of your player view are smaller than these values Picture-in-Picture may not automatically be triggered when the application enters the background.

**Important: The IMA, FreeWheel, Pulse and SSAI plugins each handles Picture-in-Picture functionality differently. Review the Picture-in-Picture section in each plugin README for additional information.**

## Thumbnail Seeking

Thumbnail seeking allows users to drag the playhead along the timeline and view thumbnails as a preview of the associated content. This gives users the ability to quickly navigate a video file and find the content that they are interested in.

This feature is also referred to by Apple as Trick Play, and is referenced in their [HLS Authoring Specification](https://developer.apple.com/documentation/http_live_streaming/hls_authoring_specification_for_apple_devices?language=objc).

This feature is enabled by default. If you wish to disable thumbnail seeking you can do so by setting the `thumbnailSeekingEnabled` property on your `BCOVPlaybackController` to `NO`. 

```
self.playbackController.thumbnailSeekingEnabled = NO;
```

You can customize the layout of the thumbnail preview by making use of a delegate method with your `BCOVPUIPlayerView` or `BCOVTVPlayerView`. 

On iOS you can adjust the height, width and vertical offset:

```
- (void)setupPlayerView
{
    BCOVPUIPlayerView *playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:nil];
    playerView.delegate = self;
    ...
}

#pragma mark - BCOVPUIPlayerViewDelegate

- (CGRect)playerViewShouldDisplayThumbnailPreviewWithRect:(BCOVPUIPlayerView *)playerView
{
    CGFloat width = 100;
    CGFloat height = 56;
    CGFloat verticalOffset = -60;
    CGFloat modifier = 1;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        modifier = 2;
    }
    return CGRectMake(0, verticalOffset * modifier, width * modifier, height * modifier);
}
```

On tvOS you can adjust the height and width:

```
- (void)setupPlayerView
{
    self.playerView = [[BCOVTVPlayerView alloc] initWithOptions:nil];    
    self.playerView.delegate = self;
    ...
}

#pragma mark - BCOVTVPlayerViewDelegate

- (CGSize)playerViewShouldDisplayThumbnailPreviewWithSize:(BCOVTVPlayerView *)playerView
{
    CGSize size = self.view.frame.size;
    size.width = size.width / 6;
    size.height = size.height / 6;
    return size;
}
```
If manually constructing a `BCOVVideo` object you can set the URL to be used for the Thumbnail WebVTT source:

```
BCOVVideo *video = [BCOVVideo videoWithURL:[NSURL URLWithString:@"https://mydomain.com/master.m3u8"]];
video = [video update:^(id<BCOVMutableVideo> mutableVideo) {
    mutableVideo.thumbnailVTTURL = [NSURL URLWithString:@"https://mydomain.com/thumbnail.webvtt"];
}];
```

Thumbnail seeking is only available for online videos; downloaded/offline videos do not support this feature. 

## Video Insertion

You can insert an additional BCOVVideo, after another BCOVVideo already in the queue, into your `BCOVPlaybackController` by calling `insertVideo:afterVideoAtIndex:`.

For example:

```
// This will insert the new video after the first video in the queue
[self.playbackController insertVideo:videoToInsert afterVideoAtIndex:0];
```

There are two delegate methods you can utilize to be alerted of the success or failure of the request.

* `- (void)playbackController:(id<BCOVPlaybackController>)controller didInsertVideo:(BCOVVideo *)video atIndex:(NSUInteger)index`
* `- (void)playbackController:(id<BCOVPlaybackController>)controller failedToInsertVideo:(BCOVVideo *)video`

## Generic Stream Concurrency

Generic Stream Concurrency (GSC) is a service which determines whether playback is permitted based on the active playback sessions for the viewer and a preset concurrency limit. The service is requested through the Edge Playback Authorization (EPA) service. The same JWT used to retrieve the video is used here, and should include a `uid` claim, a `climit` claim and optionally, a `sid` claim. This feature must be enabled in your acccount.

Generic Stream Concurrency is not enabled in the SDK by default. If you wish to enable it, set the `streamConcurrencyEnabled` property of your `BCOVPlaybackController` to `YES`.

```
self.playbackController.streamConcurrencyEnabled = YES;
```

The `sid` value can be included in the JWT or sent as a `BCOVPlaybackController` option, both of which are optional. The `sid` value in the JWT has precedence over the `BCOVPlaybackController` option.

```
self.playbackController.options[kBCOVAuthHeartbeatPropertyKeySessionId] = @"sessionId";
```

A new delegate method has been added to `BCOVPlaybackControllerDelegate` to retrieve the active sessions when the concurrency limit has been reached.

```
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didReachMaxConcurrency:(NSDictionary *)sessions
{
    NSLog(@"%@", sessions);
}
```

## Tracking Errors

Playback errors are typically handled and reported through video playback events from the playback controller. If you need to dig deeper and track problems with particular videos or app sessions, you can take advantage of the Brightcove Player SDK's *session ID*. The session ID is a property of the `BCOVPlayerSDKManager` that you can retrieve like this:

```
NSString *sdkSessionID = BCOVPlayerSDKManager.sharedManager.sessionID;
```

The session ID is a unique string that does not change during the app life cycle. This string is reported with various other analytics data to the Brightcove metrics servers. If you are having problems with a particular app instance, or video, you can record the session ID and send it back to your own company servers. Then you can send the session ID, video ID, and any other pertinent data to Brightcove service engineers to help diagnose any issues.


## Combining Plugins

If you need to combine Player SDK plugins, for example to add subtitles to a DRM-protected video which plays ads managed by Google IMA, `BCOVSessionProviders` from each plugin are created and chained together and the chain is used to construct the `BCOVPlaybackController`.

```
BCOVPlayerSDKManager *sdkManager = [BCOVPlayerSDKManager sharedManager];
        
IMASettings *imaSettings = [[IMASettings alloc] init];
imaSettings.ppid = kViewControllerIMAPublisherID;
imaSettings.language = kViewControllerIMALanguage;
        
IMAAdsRenderingSettings *renderSettings = [[IMAAdsRenderingSettings alloc] init];
renderSettings.webOpenerPresentingController = self;
        
BCOVIMAAdsRequestPolicy *adsRequestPolicy =
    [BCOVIMAAdsRequestPolicy videoPropertiesVMAPAdTagUrlAdsRequestPolicy];

// create the sidecar subtitles session provider. it has no upstream session provider.
id<BCOVPlaybackSessionProvider> sidecarSessionProvider =
    [sdkManager createSidecarSubtitlesSessionProviderWithUpstreamSessionProvider:nil];

// create a fairplay session provider with the sidecar session provider as its upstream session
id<BCOVFPSAuthorizationProxy> authProxy =
    [[BCOVFPSBrightcoveAuthProxy alloc] initWithPublisherId:nil applicationId:nil];
id<BCOVPlaybackSessionProvider> fairPlaySessionProvider =
    [sdkManager createFairPlaySessionProviderWithAuthorizationProxy:authProxy upstreamSessionProvider:sidecarSessionProvider];
    
// create the IMA session provider with an upstream sidecar subtitles session provider.
id<BCOVPlaybackSessionProvider> imaSessionProvider =
    [sdkManager createIMASessionProviderWithSettings:imaSettings
                                adsRenderingSettings:renderSettings
                                    adsRequestPolicy:adsRequestPolicy
                                         adContainer:self.playerView.contentOverlayView
                                      viewController:self
                                      companionSlots:nil
                             upstreamSessionProvider:fairPlaySessionProvider];

// create the playback controller using the session provider chain.
id<BCOVPlaybackController> playbackController =
    [sdkManager createPlaybackControllerWithSessionProvider:imaSessionProvider
                                               viewStrategy:nil];
```

## Buffer Optimization

### Overview

Developers have control over the size of the forward playback buffer used by the `AVPlayer`. This is done by setting the `preferredForwardBufferDuration` property in the `AVPlayerItem` class.

By default, the Brightcove Native Player SDK sets the `preferredForwardBufferDuration` property in a way that optimizes overall bandwidth without sacrificing playback quality. This behavior can be overridden with your own values.

### Default Behavior

Everyone pays for bandwidth, so it's important to reduce bandwidth consumption without affecting playback quality. New with version 5.2.0, the Brightcove Native Player SDK manages the buffer size for you dynamically as the video plays.

Prior to iOS 10, the `AVPlayer` buffered as much video data as it practicably could, up to around 50 Megabytes. This is fine for the video viewing model where a user selects a video and then watches it until the end, but many modern apps now "tease" videos with autoplay, hoping to secure engagement after a few seconds. A lot of users simply move on to different videos. With aggressive buffering you can end up with several minutes of buffered video that are thrown away with each video impression.

The Brightcove Native Player SDK addresses this problem by starting the video with a small baseline buffer, and then increasing it as the user watches more of the video. After a certain point, the buffer size is capped since it is not practical or helpful to make it too large.

### Modifying The Default Behavior

If you want to keep the default behavior of the Brightcove Native Player SDK, but modify the minimum and maximum values used for the buffer sizes, you can do the following when setting up the `BCOVPlaybackController`:

    // Create mutable dictionary to hold new values
    NSMutableDictionary *options = self.playbackController.options.mutableCopy;

    // Set new values in dictionary
    options[kBCOVBufferOptimizerMethodKey] = @(BCOVBufferOptimizerMethodDefault);
    options[kBCOVBufferOptimizerMinimumDurationKey] = @(min);
    options[kBCOVBufferOptimizerMaximumDurationKey] = @(max);

    // Set new dictionary in your playback controller
    self.playbackController.options = options;

These options should be set before calling `-BCOVPlaybackController setVideos:`.

`min` and `max` values:

- These are floating point values that you can set as the new minimum and maximum buffer durations. 
- If the values are set too small, playback may stall under erratic network conditions. 
- If the values are set too large, the `AVPlayer` may buffer data that is never viewed. 
- Testing based on your expected use cases is important. 
- Values are specified in seconds of time, and must be greater than or equal to 1.0. (Zero is a special value in the `AVPlayerItem` that tells the `AVPlayer` to determine its own buffer size.


### Turning Off Buffer Optimization

If you do not want any buffer optimization active in your current playback session, you can use the same technique, but set the optimziation method to "None" as follows:

    // Create mutable dictionary to hold new values
    NSMutableDictionary *options = self.playbackController.options.mutableCopy;
    
    // Set new values in dictionary
    options[kBCOVBufferOptimizerMethodKey] = @(BCOVBufferOptimizerMethodNone);

    // Set new dictionary in your playback controller
    self.playbackController.options = options;

With the method set to “None”, iOS will maintain full control of the forward buffer size.

### Implementing Your Own Buffer Optimization Method

If you want to set your own buffer size for playback, first turn off buffer optimization as described in the previous section. Then, you can implement the following `BCOVPlaybackController` delegate method:

	- (void)playbackController:(id<BCOVPlaybackController>)controller didAdvanceToPlaybackSession:(id<BCOVPlaybackSession>)session
	{
	  // Make sure the property exists on the current AVPlayerItem.
      if ([session.player.currentItem respondsToSelector:NSSelectorFromString(@"preferredForwardBufferDuration")])
      {
        // Set your preferredForwardBufferDuration value here.
		 session.player.currentItem.preferredForwardBufferDuration = newPreferredForwardBufferDurationValue;
      }
	}

If you want to change the buffer size dynamically over time, you can set `session.player.currentItem.preferredForwardBufferDuration` in the `BCOVPlaybackController`'s progress delegate method in a similar fashion:

	- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didProgressTo:(NSTimeInterval)progress
	{
	  // Make sure the property exists on the current AVPlayerItem.
      if ([session.player.currentItem respondsToSelector:NSSelectorFromString(@"preferredForwardBufferDuration")])
      {
        // Set preferredForwardBufferDuration based on your own logic here
		 session.player.currentItem.preferredForwardBufferDuration = newPreferredForwardBufferDurationValue;
      }
	}

Note: Apple specifically put "preferred" in `preferredForwardBufferDuration` because you can set any value you want, but generally speaking the `AVPlayer` player will use it only as a guideline. Also keep in mind that setting it to zero returns full control of the buffer size to the `AVPlayer`.

## Using an AVPlayerViewController with a BCOVPlaybackController

### Overview

You can use the AVPlayerViewController instead of the AVPlayerLayer used by the BCOVPlaybackSession class. Using the AVPlayerViewController allows the player to use the native iOS and tvOS player controls, but there are limitations to this approach (see below).

To use the AVPlayerViewController, you can set a BCOVPlaybackController dictionary property called `kBCOVAVPlayerViewControllerCompatibilityKey`:

    BCOVPlayerSDKManager *sdkManager = [BCOVPlayerSDKManager sharedManager];

    id<BCOVPlaybackController> playbackController;

    NSMutableDictionary *mutableOptions = self.playbackController.options.mutableCopy;
    // To use the AVPlayerViewController
    mutableOptions[kBCOVAVPlayerViewControllerCompatibilityKey] = @YES;

    // To use the BCOVPlaybackSession's AVPlayerLayer
    // mutableOptions[kBCOVAVPlayerViewControllerCompatibilityKey] = @NO;

    self.playbackController.options = mutableOptions;

The default value of kBCOVAVPlayerViewControllerCompatibilityKey is `@NO`, which means that a BCOVPlaybackController created without this dictionary property explicitly set will use the BCOVPlaybackSession's AVPlayerLayer by default.

### Advertising

The Brightcove IMA, FreeWheel, Pulse and SSAI ad plugins are compatible when using AVPlayerViewController. You can use the AVPlayerViewController's `contentOverlayView` for the view in which to display ads (not applicable to SSAI). 

You may wish to hide/show the AVPlayerViewController's playback controls before and after ads play:

```
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didEnterAdSequence:(BCOVAdSequence *)adSequence
{
    self.avpvc.showsPlaybackControls = NO;
}

- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didExitAdSequence:(BCOVAdSequence *)adSequence
{
    self.avpvc.showsPlaybackControls = YES;
}
```

When using an AVPlayerViewController with the Brightcove IMA plugin and ads with a "Learn More" button you'll need to create an additional UIView to use as the ad container view. This is because AVPlayerViewController's `contentOverlayView` is not interactive so attempting to tap the "Learn More" button will have no effect. You can use the `playbackController:playbackSession:didEnterAdSequence:` and `playbackController:playbackSession:didExitAdSequence:` delegate methods to show and hide your ad container view.

### tvOS

If using the IMA, FreeWheel, Pulse or SSAI plugins on tvOS an array of `AVInterstitialTimeRange` will be created for each ad cue point and set on the `interstitialTimeRanges` of the associated `AVPlayerItem`. For the IMA, FreeWheel and Pulse plugins you will want to create a play/pause gesture so that when an ad is active you can correctly pause and resume the ad and not affect playback of the video itself. Here is an example:

```
- (void)setUpAdPlayPauseGesture
{
    self.playPauseGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(playPauseAd:)];
    self.playPauseGesture.allowedPressTypes = @[@(UIPressTypePlayPause)];
    [self.avpvc.view addGestureRecognizer:self.playPauseGesture];
}

- (void)playPauseAd:(UITapGestureRecognizer *)gesture
{
    if (self.insideAdSequence)
    {
        if (self.adPlaying)
        {
            [self.playbackController resumeAd];
            self.adPlaying = NO;
        }
        else
        {
            [self.playbackController pauseAd];
            self.adPlaying = YES;
        }
    }
    else
    {
        if (self.avpvc.player.rate == 0)
        {
            [self.playbackController play];
        }
        else
        {
            [self.playbackController pause];
        }
    }
}

- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didEnterAdSequence:(BCOVAdSequence *)adSequence
{
    self.insideAdSequence = YES;
}

- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didExitAdSequence:(BCOVAdSequence *)adSequence
{
    self.insideAdSequence = NO;
}
```

For displaying an ad overlay, like a countdown, please see the **AVPlayerViewController Support** section of the ad plugin README you are using for some guidance.

Note that SSAI's `AVPlayerViewController` compatibility is specific to tvOS due to the availability of `AVInterstitialTimeRange`. You will still be able to have playback on iOS however the duration of the video will include the duration of all the ads. 


### Sample Projects

We have sample projects demonstrating the use of AVPlayerViewController with the Brightcove iOS SDK.  You can find the [iOS sample project here](https://github.com/BrightcoveOS/ios-player-samples/tree/master/Player/NativeControls) and the [tvOS sample project here](https://github.com/BrightcoveOS/ios-player-samples/tree/master/IMA/NativeControlsIMAPlayer_tvOS).

### Limitations to Using the AVPlayerViewController

#### Analytics

When using the AVPlayerViewController, the video_engagement events sent to the Brightcove Analytics server will report 0 for player_width and player_height.

## Playback Authorization Service

If you are using the Playback Authorization Service you will need to use the playback service methods that allow you to pass in an authorization token. 

```
- (void)findPlaylistWithPlaylistID:(NSString *)playlistID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findPlaylistWithReferenceID:(NSString *)referenceID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findVideoWithVideoID:(NSString *)videoID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findVideoWithReferenceID:(NSString *)referenceID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;

```

**Note: In the case of playlists, all videos in the playlist must use the same token.  In a subsequent release, assigning a different token to each video in a playlist will be possible.  You will be responsible for maintaining the mapping between video id and token.**

## VoiceOver Support

VoiceOver is supported out-of-the-box for the playback controls. By default, if VoiceOver is enabled, the BCOVPlayerUI control view will not auto-hide. Using the double-tap VoiceOver activation gesture on the playback controller's view will toggle the visibility of the control view. There is an associated `accessibilityHint` that is set on the playback controller's view. The `accessibilityLabel` of each BCOVPlayerUI control can be customized within your application. 

To change the `accessibilityLabel` values of any of the buttons in the control view you must set an object to be a `BCOVPUIButtonAccessibilityDelegate` like this:

    [self.playerView.controlsView setButtonsAccessibilityDelegate:self];

You must then have that object conform to the `BCOVPUIButtonAccessibilityDelegate` protocol by implmenting the `- (NSString *)accessibilityLabelForButton:(BCOVPUIButton *)button isPrimaryState:(BOOL)isPrimaryState` method similar to this:

    - (NSString *)accessibilityLabelForButton:(BCOVPUIButton *)button isPrimaryState:(BOOL)isPrimaryState
    {
        switch (button.tag)
        {
            case BCOVPUIViewTagButtonPlayback:
                return isPrimaryState ? NSLocalizedString(@"Start Playback", nil) : NSLocalizedString(@"Stop PLayback", nil);
            case BCOVPUIViewTagButtonScreenMode:
                return isPrimaryState ? NSLocalizedString(@"Enter Fullscreen", nil) : NSLocalizedString(@"Exit Fullscreen", nil);
            case BCOVPUIViewTagButtonJumpBack:
                return nil;
            case BCOVPUIViewTagButtonClosedCaption:
                return nil;
            case BCOVPUIViewTagButtonVideo360:
                return nil;
            case BCOVPUIViewTagButtonPreferredBitrate:
                return nil;
            default:
                return nil;
        }
    }

If a `nil` value is returned the default value will be used.

Setting the `accessibilityHint` on the playback controller can be done like this:

    self.playbackController.view.accessibilityHint = @"Double tap to show or hide controls";

Similarly you can set the `accessibilityLabel` on the current time and duration labels, along with the progress slider, like this:

    self.playerView.controlsView.durationLabel.accessibilityLabelPrefix = @"Total Time";
    self.playerView.controlsView.currentTimeLabel.accessibilityLabelPrefix = @"Current Time";
    self.playerView.controlsView.progressSlider.accessibilityLabel = @"Timeline";

## Custom Localization

You can provide additional language localizations that the Brightcove iOS SDK does not support out-of-the-box. 

1. Add the language you need to your project if you have not already done so. You can add localizations by navigating to Project > Localizations (under the Info tab) and clicking the `+` button beneath the "Localizations" section.
1. In Xcode, with your project open, navigate to File > New > File
1. In the *Filter* search bar enter "Strings" and then select the "Strings File" and click "Next"
1. Name the file "BrightcoveSDK.strings" and click "Create"
1. Select the BrightcoveSDK.strings file in the Navigator pane and in the Inspector pane click the "Localize..." button
1. From the dropdown select the desired language
1. The Inspector pane will now show all the available localization options, you can select additional languages now if needed
1. You can now add your own localizations to the BrightcoveSDK.strings file. If you have selected multiple languages you will see a BrightcoveSDK.strings file in the Navigator pane for each language.
1. The keys for each string the SDK uses can be found [here](https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/BrightcoveSDK.strings)

## China Delivery

To define a proxy domain for playback services, metrics and analytics servers in China, set the `chinaProxyDomain` property of the `BCOVGlobalConfiguration` singleton to a fully qualified domain name. For example:

```
BCOVGlobalConfiguration.sharedConfig.chinaProxyDomain = @"host.mydomain.com";
```

Be sure to set the proxy domain name before using any other services of the Native Player SDK. Refer to the [_BCOVGlobalConfiguration Class Reference_](https://docs.brightcove.com/ios-sdk/Classes/BCOVGlobalConfiguration.html#//api/name/chinaProxyDomain) for details.

## AVAudioSession Configuration

Depending on how you need your application to perform when it comes to audio playback you can configure AVAudioSession to suit your specific needs. For example if you want to support AirPlay 2 and multiple audio routes see the [AirPlay](#AirPlay) section of this README. 

A basic AVAudioSession can be configured like this:

```
//  Obj-C
NSError *categoryError = nil;
// see https://developer.apple.com/documentation/avfoundation/avaudiosessioncategoryplayback
BOOL success = [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback error:&categoryError];

if (!success)
{
    // Handle error
}
```

```
// Swift
var categoryError :NSError?
var success: Bool
do {
    // see https://developer.apple.com/documentation/avfoundation/avaudiosessioncategoryplayback
    try AVAudioSession.sharedInstance().setCategory(.playback)
    success = true
} catch let error as NSError {
    categoryError = error
    success = false
}

if !success {
    // Handle error
}
```

This configuration can typically be done in your AppDelegate's `application:didFinishLaunchingWithOptions:` method. There may be situations where you need a more sophisticated AVAudioSession configuration, for example if you want to allow audio from other apps to be heard when the audio in your app is muted. In this situation you can configure the AVAudioSession in the view controller that has access to your current AVPlayer. For example:

```
// Swift
func setUpAudioSession() {
    var categoryError :NSError?
    var success: Bool

    do {
        if let currentPlayer = currentPlayer {
            // If the player is muted, then allow mixing.
            // Ensure other apps can have their background audio
            // active when this app is in foreground
            if currentPlayer.isMuted {
                try AVAudioSession.sharedInstance().setCategory(.playback, options: .mixWithOthers)
            } else {
                try AVAudioSession.sharedInstance().setCategory(.playback, options: AVAudioSession.CategoryOptions(rawValue: 0))
            }
        } else {
            try AVAudioSession.sharedInstance().setCategory(.playback, options: AVAudioSession.CategoryOptions(rawValue: 0))
        }
        
        success = true
    } catch let error as NSError {
        categoryError = error
        success = false
    }

    if !success {
        print("AppDelegate Debug - Error setting AVAudioSession category.  Because of this, there may be no sound. \(categoryError!)")
    }
}
```
```
// Objc-C
- (void)setUpAudioSession
{
    NSError *categoryError = nil;
    BOOL success;
    
    // If the player is muted, then allow mixing.
    // Ensure other apps can have their background audio
    // active when this app is in foreground
    if (self.currentPlayer.isMuted)
    {
        success = [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback withOptions:AVAudioSessionCategoryOptionMixWithOthers error:&categoryError];
    }
    else
    {
        success = [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback withOptions:0 error:&categoryError];
    }
    
    if (!success)
    {
        NSLog(@"AppDelegate Debug - Error setting AVAudioSession category.  Because of this, there may be no sound. `%@`", categoryError);
    }
}
```
Sample code can be found in our [VideoCloudBasicPlayer](https://github.com/BrightcoveOS/ios-player-samples/tree/master/Player/VideoCloudBasicPlayer) sample project.

You can read more about AVAudioSession [here](https://developer.apple.com/documentation/avfoundation/avaudiosession). 

## Audio-Only Support

The Brightcove Player SDK supports audio-only streams and includes a few audio-only features. If you have configured a poster image for your video that image will be displayed in the `contentOverlayView` of your `BCOVPUIPlayerView`. You can adjust the `UIViewContentMode` of the poster image view by using the `contentModeForPosterImage` property on `BCOVPUIPlayerViewOptions`, the default value is `UIViewContentModeScaleAspectFit`. 

You may also wish to keep the player controls visible at all times, in that case you can enable `keepControlsVisible` on `BCOVPUIPlayerViewOptions`.

If you do not want to display the poster image or simply want a more compact playback view you can set the height of your `BCOVPUIPlayerView` parent view to a height of 88 pt for a compact (&lt; 450 pt) layout or a height of 44 pt for a standard layout. 

There are three pre-configured audio-only `BCOVPUIBasicControlView` layouts you can use if you aren't using `automaticControlTypeSelection`:
- `basicControlViewWithAODLayout`
- `basicControlViewWithLiveAudioLayout`
- `basicControlViewWithLiveDVRAudioLayout`

You can also be notified if a stream is audio-only or video+audio with the `playbackController:playbackSession:determinedMediaType` delegate method:

```
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session determinedMediaType:(BCOVSourceMediaType)mediaType
{
    switch (mediaType)
    {
        case BCOVSourceMediaTypeAudio:
            NSLog(@"Source is Audio Only");
            break;
        case BCOVSourceMediaTypeAudioVideo:
            NSLog(@"Source is Audio and Video");
            break;
    }
}
```

Our [VideoCloudBasicPlayer](https://github.com/BrightcoveOS/ios-player-samples/tree/master/Player/VideoCloudBasicPlayer) has support for displaying the media information on the Lock Screen, Control Center and over AirPlay. See the `NowPlayingHandler` class for implementation details.

## Bumper Support

A Video Bumper is a short asset, usually 10 seconds or less, that plays before all other media and typically shows the brand or company that your video represents.  A player will request a bumper from the Playback API like any other video, and insert it before ads and content.

Bumpers are a player-level feature, meaning a given player may only be associated with a single bumper. The playlists share the same bumper video. There will be two ways to configure a player to play a bumper video:

#### 1. Playback Service (BCOVPlaybackService) signatures.

- `bumperID`. The ID of the video to find.

```
- (void)findPlaylistWithPlaylistID:(NSString *)playlistID bumperID:(NSString *)bumperID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findPlaylistWithPlaylistID:(NSString *)playlistID bumperID:(NSString *)bumperID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findVideoWithVideoID:(NSString *)videoID bumperID:(NSString *)bumperID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findVideoWithVideoID:(NSString *)videoID bumperID:(NSString *)bumperID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;
```

- `BumperRefID`. The reference ID of the video to find.

```
- (void)findPlaylistWithReferenceID:(NSString *)referenceID bumperReferenceID:(NSString *)bumperReferenceID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findPlaylistWithReferenceID:(NSString *)referenceID bumperReferenceID:(NSString *)bumperReferenceID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findVideoWithReferenceID:(NSString *)referenceID bumperReferenceID:(NSString *)bumperReferenceID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;

- (void)findVideoWithReferenceID:(NSString *)referenceID bumperReferenceID:(NSString *)bumperReferenceID authToken:(NSString *)authToken parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;
```

#### 2. Custom Fields.

The `bumper_id` field can be defined in Custom Fields in VideoCloud/Studio. The `bumper_id` can be used without the signatures previously defined. The `bumper_id` must be a valid video ID.

**Note: BumperID passed via the Custom Fields (`bumper_id` field) take precedence over any ID in the playback service.**

Playback controls can be hidden while the bumper is playing.

```
BCOVPUIPlayerViewOptions *options = [BCOVPUIPlayerViewOptions new];
options.automaticControlTypeSelection = YES;
options.showBumperControls = NO;
BCOVPUIPlayerView *playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:nil options:options controlsView:nil];
```

If the `automaticControlTypeSelection` option is set to `YES`, the layout for the bumper will adapt to the content (video or audio only). `basicControlViewWithVODLayout` and `basicControlViewWithAODLayout` layouts are designed for bumpers, `Live` or `LiveDRV` layouts are not available. Playback controls have a unique appearance when a bumper active:

- The Progress Bar is purple
- Buffering is not reflected in the progress bar
- Seeking is not allowed
- The JumpBack button is not present
- AirPlay and PiP depend on the playerView configuration
  - the AirPlay icon depends on the content (video/audio-only)
  - PiP is not allowed for audio-only content

## Frequently Asked Questions

### My content won't load. Is there an easy way to test whether the URL points to a valid video?

If the content is packaged as MP4, you can paste the URL directly into most web browsers, and the video should play (or download to your filesystem, where you can play it locally). If the content is packaged as HLS, you can use QuickTime Player to test it: select `File -> Open Location…` and paste in the `.m3u8` playlist URL, and the video should play.

### I can hear the audio track playing, but the video freezes for a few seconds sporadically. What's happening?

This is a common symptom of having called a main thread-only UIKit or AVFoundation method from a non-main thread. The delegate methods on `BCOVPlaybackControllerDelegate` are always called on the main thread.

### Why do I see a message in the log indicating that no source has been found?

This message indicates that the default source selection policy can't figure which source to pick. The default policy selects the first source whose `deliveryMethod` is `kBCOVSourceDeliveryHLS` ("HLS"). If no HLS source is found, its fallback behavior will select the first source whose `deliveryMethod` is `kBCOVSourceDeliveryMP4` ("MP4"). If no source with a `deliveryMethod` of "HLS" or "MP4" exists on the video, the policy will select the video's first source (regardless of `deliveryMethod`). If you aren't happy with its selection, you can use `-[BCOVPlayerSDKManager createBasicSessionProviderWithOptions:]` and pass in an instance of `BCOVBasicSessionProviderOptions` with a custom `sourceSelectionPolicy` property set. When creating videos and sources manually, ensure that the sources are created with the appropriate `deliveryMethod`.

### [Apple recommends][audioguidelines] that apps which play video should still play audio even when the device is muted. Why doesn't the Brightcove Player SDK for iOS respect these guidelines?

The API which controls whether an app emits audio in iOS apps is the [AVAudioSession API][avaudiosessionapi]. An audio session is global to an app, which means that its configuration affects both the sounds that are emitted by the AVPlayers created by the Player SDK, as well as other sounds that an app may produce. Since the Player SDK cannot know how the app wants the audio session configured for those other sounds, it doesn't affect the audio session at all. This means that unless you explicitly configure your app's audio session otherwise, you inherit the default behavior of suppressing any and all audio when the device is muted, including audio emitted by AVPlayers. To conform to Apple's recommendations regarding audio playback, you (the app developer) must configure the audio session according to your app's specific needs.

See our [AVAudioSession Configuration](#AVAudioSessionConfig) section in this README for additional information.

[audioguidelines]: https://developer.apple.com/Library/ios/documentation/Audio/Conceptual/AudioSessionProgrammingGuide/AudioGuidelinesByAppType/AudioGuidelinesByAppType.html
[avaudiosessionapi]: https://developer.apple.com/Library/ios/documentation/Audio/Conceptual/AudioSessionProgrammingGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40007875-CH1-SW1

## Support

If you have questions, need help or want to provide feedback, please use the [Support Portal](https://supportportal.brightcove.com/s/login/) or contact your Account Manager.  To receive notification of new SDK software releases, subscribe to the Brightcove Native Player SDKs [Google Group](https://groups.google.com/g/brightcove-native-player-sdks).
