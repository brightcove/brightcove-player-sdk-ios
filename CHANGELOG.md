## Release 6.8.4 ##

### Brightcove Player SDK for iOS (Core)

#### Breaking Changes

* Nullability annotations have been added to BCOVVideo.h to resolve compile time warnings. You may need to use `guard let` or `if let` in your Swift code to handle optionals.

#### Additions and Improvements

* Deprecates `thumbnailScrubbingEnabled`. Use `thumbnailSeekingEnabled` instead.

### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds the `kBCOVFWLifecycleEventAdError` eventType to pass through errors encountered by the FreeWheel SDK. Refer to the _Tracking FreeWheel Errors_ section of the Freewheel _README_ for details.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an issue where the `playerUrl` property of the `BCOVReceiverAppConfig` was ignored.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Updates the IMA _README_ to reflect deprecations, e.g. `registerVideoControlsOverlay`, in Google IMA SDK v3.12.1 for iOS.

* Adds Open Measurement example code to the BasicIMAPlayer [sample project](https://github.com/BrightcoveOS/ios-player-samples).

### Pulse Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an issue where `kBCOVPlaybackSessionLifecycleEventEnd` was posted before a postroll ad.

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds an abbreviated ad time remaining label (e.g. "30s") to the built-in PlayerUI ad controls. This label is used only when the available width is at a minimum as is the case for some small iOS devices and syllable-verbose languages.

* Adds the `vmapResponseData` property to the SSAI session object. Refer to the _Access to VMAP Response Data_ section of the SSAI plugin _README_ for details.

## Release 6.8.3 ##

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* An `NSError` returned with a `kBCOVPlaybackSessionLifecycleEventError` event may now contain the `kBCOVFPSAuthProxyResponseData` key in its `userInfo`.

* Adds the `iFramePlaylistURL` property to `BCOVVideo` to allow an iFrame (TrickPlay) playlist URL to be defined at runtime. Refer to the _Thumbnail Scrubbing_ section of the Core SDK _README_ for details.

* Fixes Automatic Picture in Picture compatibility with iOS 14.

* Fixes an issue where an app in Picture in Picture mode closed the PiP view when advancing to the next video in a video playlist.

* Fixes an issue where auto-advancing to an MP4 video in a playlist would not auto-play.

* Fixes the `BCOVPlaybackController` method `resumeVideoAtTime:withAutoPlay:`.

* Improves resuming Live video streams after very long pauses.

* Fixes an issue where the Video360 screen-mode button was not disabled when entering VR Goggles mode.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Release 6.8.2 added support for setting a splash screen image URL. For example:
```
BCOVReceiverAppConfig *appConfig = [BCOVReceiverAppConfig new];
appConfig.splashScreen = @"https://host.company.com/images/cast-splash.jpg";
self.googleCastManager = [[BCOVGoogleCastManager alloc] initForBrightcoveReceiverApp:appConfig];
```

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds the `kBCOVIMAOptionBlockAdTargetingAPIsKey` option to prevent the Brightcove IMA plugin from making calls to Apple's AdSupport and AppTrackingTransparency APIs. This can be helpful when submitting certain apps to the App Store. Refer to the _Device Ad Targeting_ section of the IMA _README_ for details. Refer also to the header comments of the `createIMAPlaybackControllerWithSettings:` methods in `BCOVIMAComponent.h`.

* Fixes an issue where `kBCOVPlaybackSessionLifecycleEventEnd` was not sent when a video played with no ads.

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* When a VMAP document cannot be found it will be reported by a `kBCOVPlaybackSessionLifecycleEventError` event with an `NSError` having a `code` property set to `kBCOVSSAIErrorCodeVMAPMissingError`.

* Fixes an issue where VMAP documents could be requested twice.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an issue where `kBCOVPlaybackSessionLifecycleEventEnd` would not be triggered when using an `IMASessionProvider` with no ads configured.

## Release 6.8.2 ##

#### Additions and Improvements

* Exposes ad skip properties for all SDK ad plugins. Refer to `kBCOVAdPropertyKeySkippable` and `kBCOVAdPropertyKeySkipTime` in `BCOVAdvertising.h`.

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds convenience methods for accessing Multilingual Metadata in a Playback API response. Refer to `localizedNameForLocale`, `localizedShortDescriptionForLocale` and `localizedLongDescriptionForLocale` in `BCOVVideo` and note that these are C-style functions in keeping with the pattern of `NSLocalizedString`. Also adds the `BCOVPlaybackControllerBasicDelegate` callback method `playbackController:determinedMetadata:forVideo:`.

* Adds the `BCOVPlaybackControllerBasicDelegate` method `-playbackController:determinedCodecs:forVideo:` to report the codecs in use during playback.

* Fixes an issue with custom progress bar thumb images on iOS 14.

* Fixes issues with background audio on some devices running iOS 14.

* Fixes an issue where a video manifest would be requested even if `thumbnailScrubbingEnabled` was set to false.

* Fixes an issue where subtitles were no longer visible after an app returned to the foreground.

* Fixes an issue where a paused video resumed playing after swiping down to expose the tab bar menu on tvOS.

* Fixes playback for some complex custom view strategies.

* Reduces SDK startup time after videos have been downloaded to the device.

### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports version 6.38.0 of the FreeWheel AdManager framework for iOS and tvOS.

* Fixes an issue where an incorrect ad duration value could be passed to a `BCOVFWSessionProviderAdContextPolicy` block.
 
### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for setting a splash screen image URL. For example:
```
BCOVReceiverAppConfig *appConfig = [BCOVReceiverAppConfig new];
appConfig.splashScreen = @"https://host.company.com/images/cast-splash.jpg";
self.googleCastManager = [[BCOVGoogleCastManager alloc] initForBrightcoveReceiverApp:appConfig];
```

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

 * Adds support for VAST 4.1 AdVerification through integration of the [IAB Open Measurement SDK (OM SDK)](https://iabtechlab.com/standards/open-measurement-sdk/) v1.3. Refer to `createSSAISessionProviderWithUpstreamSessionProvider:omidPartner:` in the `BCOVSSAIAdditions` category of `BCOVPlayerSDKManager` in `BCOVSSAIComponent.h`. Addition of the OM SDK has increased the file size of the SSAI dynamic framework by ~13 MB, and the static framework by ~18MB.
 
 * Fixes an issue where the browser view displayed in response to tapping a companion ad was transparent on iPad devices.

## Release 6.8.1 ##

#### Breaking Changes

* Some Brightcove Player SDK Podspecs have been updated which might affect your project Podfile. Refer to the *Noteworthy* section of the SDK Core README.

#### Additions and Improvements

* Fixes an issue where _Rebuild from Bitcode_ failed during Distribution, Validation and App Store submission for apps built with dynamic Brightcove frameworks.

* Fixes some Podspecs to allow the IMA and Omniture plugins to be used together.

### Brightcove Player SDK for iOS (Core)

#### Breaking Changes

* The property `externalRouteView` on `BCOVPUIBasicControlView` has been renamed to `externalRouteViewButton` and is now a `BCOVPUIButton`. 

#### Additions and Improvements

* Fixes the AirPlay button accessibility label.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes a memory leak which could cause a video to continue playing after its view controller had been dismissed.

## Release 6.8.0 ##

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds the `BCOVTVPlayerViewDelegate` methods `playerDidBeginFastForward`, `playerDidEndFastForward`, `playerDidBeginFastRewind` and `playerDidEndFastRewind` to indicate the start and end of fast-forwarding and fast-rewinding. 

* Improves reporting of FairPlay errors which are now passed as `kBCOVPlaybackSessionLifecycleEventError` lifecycle events.

* Fixes an issue where the use of Sidecar Subtitles caused the video to fail to play for some Dynamic Delivery accounts.

* Fixes an issue where the status of a terminated download was incorrectly reported as complete. Downloads are terminated when the app is terminated, for example by swiping up.

* Fixes an issue where `BCOVVideo -playableoffline` always returned `NO` on iOS 14.

* Fixes the appearance of the player progress bar on iOS 14.

* Fixes an issue where `kBCOVPlaybackSessionLifecycleEventFail` was not posted for bad video source URL's on iOS 11.

* Fixes an issue where rental licenses (dual expiry licenses) prevented playback on iOS 11.4.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for the Brightcove CAF Receiver. See the [Brightcove CAF Receiver](https://github.com/brightcove/brightcove-player-sdk-ios-googlecast#brightcove-caf-receiver) section of the Google Cast Plugin README for more information.

* Supports version 4.5.0 of the Google Cast SDK for iOS. See the [iOS Permissions Changes](https://developers.google.com/cast/docs/ios_sender/ios_permissions_changes) page for information about permission changes for iOS 14 and how they play into the Google Cast SDK.

* Fixes an issue where AirPlay failed to play EPA enabled content on 3rd and 4th generation Apple TV devices.

### IMA Plugin for Brightcove Player SDK for iOS

#### Breaking Changes

* As a result of new support for Google Ads IMA SDK 3.12.1 for iOS and 4.3.2 for tvOS, all `BCOVPlayerSDKManager(BCOVIMAAdditions)` category methods now require the `UIViewController` of the IMA ad container view to be passed as an additional parameter. Refer to the [BCOVPlayerSDKManager(BCOVIMAAdditions) Category Reference](https://docs.brightcove.com/ios-plugins/ima/Categories/BCOVPlayerSDKManager+BCOVIMAAdditions.html) page. Refer also to Section 3.12.0 of the [Google IMA iOS SDK release history](https://developers.google.com/interactive-media-ads/docs/sdks/ios/client-side/history).

#### Additions and Improvements

* Adds support for App Tracking Transparency for Google Interactive Media Ads SDK 3.12.1 for iOS and 4.3.2 for tvOS.  See [Request App Tracking Transparency authorization](https://developers.google.com/interactive-media-ads/docs/sdks/ios/client-side/ios14) for more information.

* Corrects the value of `is_lat` for the purpose of Ad Tracking.

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds the `kBCOVPlaybackSessionLifecycleEventAdSkipped` lifecycle event type to allow for detecting when a user has skipped an ad.

* Fixes an issue where VMAP documents were requested twice.

## Release 6.7.11 ##

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes the behavior of the Audio and Subtitles control in the presence of Live passthrough captions (608).

## Release 6.7.10 ##

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds the `BCOVTVPlayerViewDelegate` method `liveIndicatorViewForIsPlaying:atLiveEdge:` to allow for customization of the DVR Live indicator.

* Adds the `BCOVPlaybackControllerDelegate` method `playbackController:playbackSession:didChangeSelectedAudibleMediaOption` to be notified when the audible media option for the current video is changed.

* Adds the `BCOVPlaybackControllerDelegate` method `playbackController:playbackSession:didChangeSelectedLegibleMediaOption` to be notified when the legible media option for the current video is changed.

* Fixes an issue where BCOVPlaybackSessionLifecycleEvent `kBCOVPlaybackSessionLifecycleEventReady` or `kBCOVPlaybackSessionLifecycleEventFail` sometimes failed to reach the `BCOVPlaybackController` delegate.

* Fixes an issue where subtitles set with the Sidecar plugin could cause subsequent videos in a playlist to not play.

* Improves the appearance of the built-in TV Player Controls and the handling of Siri Remote gestures.

* Adds Objective-C and Swift sample projects for playing IMA preroll ads with Live SSAI streams. See SSAI/SLS_IMA-Player and SSAI/SLS_IMA-tvOSPlayer in brightcoveos/ios-player-samples.git on GitHub.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an issue where playback controls remained hidden after an ad failed to play when using a VAST ad profile.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds the optional `BCOVGoogleCastManagerDelegate` method `willBuildMediaInformationBuilder:` to allow for additional configuration of the `GCKMediaInformationBuilder` object.

* Adds the optional  `BCOVGoogleCastManagerDelegate` method `useSourceFromSources:` to allow for custom source selection.

* Adds the optional `BCOVGoogleCastManagerDelegate` method `willSendMediaLoadOptions:` to allow for additional configuration of the `GCKMediaLoadOptions` object.

* Adds the optional `BCOVGoogleCastManagerDelegate` method `shouldCastVideo:` to allow for customization of cast behavior. 

## Release 6.7.9 ##

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue where, while using an AVPlayerViewController, video could appear to freeze after a few seconds while audio continued to play.

* Fixes a crash in Sidecar Subtitles Playback Session Provider caused by an unexpected WebVTT text track.

* Fixes a crash that could occur when calling `setVideos:` multiple times on `BCOVPlaybackController`.

* Fixes a crash that could occur when an application certificate is not available during Fairplay license processing.

* Fixes an issue where a Fairplay video might not play back when using certain session providers.

## Release 6.7.8 ##

### Brightcove Player SDK for iOS (Core)

#### Breaking Changes

* Removes the `offlineVideoToken:didFinishAggregateDownloadWithError:` method of the `BCOVOfflineVideoManagerDelegate` protocol.

#### Additions and Improvements

* Resolves App Store submission issues related to use of the IDFA (Identifier for Advertisers) by moving those references out of the Core SDK framework.

* Fixes an issue where playback of DRM protected content could stop in mid-play when using certain authorization schemes.

* Adds support for customizing the layout of thumbnail previews. See `playerViewShouldDisplayThumbnailPreviewWithSize:` on the `BCOVTVPlayerViewDelegate` protocol and `playerViewShouldDisplayThumbnailPreviewWithRect:` on the `BCOVPUIPlayerViewDelegate` protocol for more information.

* Fixes an issue where the player layer of a custom view strategy was not updated as needed, resulting in a black video display. Updates the View Strategy section of the Core SDK README. Provides a new ViewStrategy sample project in PlayerUI/ViewStrategy of the [ios-sample-projects.git](https://github.com/BrightcoveOS/ios-player-samples) git repository.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds bitcode to the tvOS framework to fix app submission.

## Release 6.7.7 ##

#### Breaking Changes

* Several Brightcove Player SDK Podspecs have been renamed which might affect your project Podfile. Refer to the *Noteworthy* section of the SDK Core README.

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Updates the `Brightcove-Player-Core` podspec to install the dynamic SDK Core framework. To install the static framework, reference the `Brightcove-Player-SDK-static` podspec instead. 

* Fixes an issue where use of a custom layout prevented scrubbing.

* Fixes an issue where occasionally, a downloaded video could not be played while off-line.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for IMA pre-roll ads with SSAI live streams on iOS and tvOS.

* Adds support for version 3.11.4 of the Google IMA SDK for iOS. 

* Adds support for version 4.2.3 of the Google IMA SDK for tvOS.

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Updates the `Brightcove-Player-SSAI` podspec to install the dynamic SSAI framework. To install the static framework, reference the `Brightcove-Player-SSAI-static` podspec instead. 

* Improves the behavior of seeking around ads and Seek Without Ads.

### GoogleCast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Updates the `Brightcove-Player-GoogleCast` podspec to install the dynamic Core framework. To install the static Core framework, reference the `Brightcove-Player-GoogleCast-static` podspec instead.

## Release 6.7.6 ##

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds the optional `BCOVPUIPlayerViewDelegate` methods `progressSliderDidTouchDown:`, `progressSliderDidChangeValue:` and `progressSliderDidTouchUp:` for iOS.

* Adds the optional `BCOVTVPlayerViewDelegate` methods `progressViewPanGestureStateBegan:`, `progressViewPanGestureStateChanged:` and `progressViewPanGestureStateEnded:` for tvOS.

* Adds support for dual expiry for offline FairPlay protected videos. Refer to the _Download a Video_ section of OfflinePlayback.md for more information.

* Fixes an issue on tvOS where audio would continue to play after a player view had been removed from the view heirarchy.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for pre-roll and post-roll ad playback over AirPlay. Set `enableBackgroundPlayback` to `YES` on `IMASettings` along with enabling AirPlay on your `BCOVPlaybackController`. Refer to the _AirPlay_ section of the README for more information.

## Release 6.7.5 ##

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes a fatal exception on tvOS caused by multiple app launches.

* Adds support for preloading content keys for online FairPlay protected videos. See `preloadContentKeysForVideos:` on `BCOVFairPlayManager` for more information.

* Improves support for right-to-left languages.

* Adds support for localized number values.

* Fixes an issue where the Captions button was hidden after changing the controls layout.

* Fixes an issue where `offlineVideoToken:aggregateDownloadTask:didProgressTo:forMediaSelection:` was not being called after an app was moved from the background to the foreground.

### Pulse Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds the ability to pause and resume ads with support for Pulse PauseAd.

* Supports seeking without ads (resume).

* Fixes post-roll ad playback on tvOS.

* Improves handling for various error conditions such as bad ad paths.

* Improves support for right-to-left languages.

## Release 6.7.4

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds support for the Brightcove Playback Rights Management Service.

* Adds support for HEVC and HLSv7 video playback.

* Adds new localizations for Arabic (ar), French (fr), German (de), Japanese (ja), Korean (ko) and Spanish (es).

### Pulse Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds new support for integrating Pulse Video Advertising with your iOS and tvOS apps.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports version 3.11.3 of the Google IMA SDK for iOS. 

* Supports version 4.2.1 of the Google IMA SDK for tvOS.

* Fixes an issue where `kBCOVIMALifecycleEventAdsLoaderLoaded` was not triggered for VAST ad profiles.

## Release 6.7.3

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds improvements to some video analytics.

## Release 6.7.2

#### Breaking Changes

* The minimum Deployment Target for all Brightcove Native Player for iOS frameworks is now iOS 11.0 and tvOS 11.0.

#### Additions and Improvements

* Fixes an issue with apps crashing during launch on iOS Simulators running iOS 11 and 12 (`dyld: Symbol not found: _OBJC_CLASS_$_AVAssetDownloadURLSession`). The exception to the fix is apps built with the Google Cast SDK for iOS CocoaPod due to an issue with the google-cast-sdk Podspec. To work around the issue, for example in the Brightcove BasicCastPlayer sample project for Objective-C, follow these steps:

1. Run `pod install`
1. Open the BasicCastPlayer.xcworkspace document
1. In the Xcode Project Navigator, navigate to Pods -> Target Support Files -> Pods-BasicCastPlayer
1. In the files Pods-BasicCastPlayer.debug.xcconfig and Pods-BasicCastPlayer.release.xcconfig change this line:

```
OTHER_LDFLAGS = $(inherited) -ObjC -l"c++" -framework "AVFoundation" -framework "Accelerate" -framework "AudioToolbox" -framework "BrightcoveGoogleCast" -framework "BrightcovePlayerSDK" -framework "CFNetwork" -framework "CoreBluetooth" -framework "CoreData" -framework "CoreGraphics" -framework "CoreMedia" -framework "CoreText" -framework "Foundation" -framework "GoogleCast" -framework "MediaAccessibility" -framework "MediaPlayer" -framework "QuartzCore" -framework "Security" -framework "SystemConfiguration" -framework "UIKit" -framework "protobuf"
```

to this:

```
OTHER_LDFLAGS = $(inherited) -ObjC -l"c++" -framework "BrightcovePlayerSDK" -framework "BrightcoveGoogleCast" -framework "GoogleCast" -framework "protobuf"
```
### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds support for short-duration license renewal for FairPlay protected videos. See `updateLicenseRenewalInterval:` on `BCOVPlaybackController`  for more information.

## Release 6.7.1

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue that could prevent downloads from starting immediately when using `BCOVOfflineVideoManager`.

* Adds the `playbackController:determinedVideoType:forVideo:` delegate method to `BCOVPlaybackController`. See the `BCOVPlaybackController` header for more information, including all available types of `BCOVVideoType`. 

* Updates header documentation for the `BCOVVideo.playableOffline` property which can have an unexpected value when the video is loaded for playback.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for setting Audience Segment Targeting information on ad requests. See `updateAudienceSegmentTargetingValues:` in `BCOVPlaybackController` for more information. *This is currently only supported when using IMA + VAST.*

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes scrubbing behavior when using BCOVPlayerUI player controls and the SSAI plugin to play back VOD.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes bitcode embedding.

## Release 6.7.0

#### Additions and Improvements

* Adds support for the Brightcove Playback Rights Management Service which is in Limited Availability.

* Deprecates support for iOS 10 and tvOS 10 in the Core SDK and all plugin frameworks. Support for iOS 10 and tvOS 10 will end in the near future.

#### Breaking Changes

* Removes strings generated by Xcode Project Versioning as those settings are not used for SDK versioning. Version strings were declared in the SDK framework umbrella headers, for example, in BrightcovePlayerSDK.h: 

```c
FOUNDATION_EXPORT const unsigned char BrightcovePlayerSDKVersionString[];
```

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Deprecates support for downloading secondary tracks as a separate download request (`requestVideoDownload:parameters:completion:` and `requestMediaSelectionsDownload:offlineVideoToken:`). Update your apps to the newest download method described in the "*Downloading Secondary Tracks*" section of OfflinePlayback.md.

#### Breaking Changes

* Removes deprecated method `renewFairPlayLicense:parameters:completion` from `BCOVOfflineVideoManager`.

#### Known Issues

* After requesting a video download, the download can delay for several minutes. To work around this issue, implement the BCOVOfflineVideoManagerDelegate method, `didCreateSharedBackgroundSesssionConfiguration:`, and set the `discretionary` property of the `backgroundSessionConfiguration` object to `NO`. A permanent fix will be released in the near future.
 
```c
- (void)didCreateSharedBackgroundSesssionConfiguration:(NSURLSessionConfiguration *)backgroundSessionConfiguration
{
    backgroundSessionConfiguration.discretionary = NO;
}
```


### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for tvOS.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds the `prepareForReuse` method to clean up state of a `BCOVGoogleCastManager` instance if shared across view controllers.

#### Breaking Changes

* Deprecates support for `sharedManager`. In a future release, `BCOVGoogleCastManager` will need to be instantiated explicitly.

## Release 6.6.2

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue where the `didChangeSeekableRanges` delegate method was not being called. This issue first appeared in SDK release 6.6.0.

* Fixes an issue where the `kBCOVPlaybackSessionLifecycleEventReady` lifecycle event might be sent in response to seek starts and ends.

## Release 6.6.1

#### Additions and Improvements

 * Fixes an issue where successive calls to `BCOVPlaybackController -setVideos:` on a single `BCOVPlaybackController` caused resource leaks which could result in an app crash.

## Release 6.6.0

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Reduces the file size of the dynamic framework by ~10MB, and ~20MB for the static framework.

* Reduces CPU load up to 40% when playing video, decreases memory usage by up to 10%, and decreases energy usage by up to 30%.

* Fixes an issue causing **default** captions to not be automatically selected. Note that the **default** caption may not be selected when the user has enabled "Closed Captions + SDH".

* Fixes an issue where tapping the LIVE button on a paused live video did not begin playback after seeking to the live edge.

* Fixes an issue when retrying a download of secondary tracks after a previous attempt resulted in a failure.

* Enables playback of an IMA pre-roll ad with Live HLS streams.

* Adds functionality to specify an initial selection when setting bitrate options along with the ability to programmatically set a preferred bitrate.  Refer to the "*Setting a Preferred Bitrate*" section of the README for more information.

* Removes a reference to the deprecated UIWebKit.

#### Breaking Changes

* The Offline Downloads API has changed for iOS 13+. Refer to the "*Downloading Secondary Tracks*" section of OfflinePlayback.md for details.

* The minimum tvOS Deployment Target for all Brightcove Native Player for tvOS frameworks is now tvOS 10.0.

* Support for `BCOVBasicSessionLoadingPolicy` has been removed. Refer to the "*Preloading Videos*" section of the README for guidance on using multiple playback controllers to achieve a preloading effect.

* Requires Xcode 11+.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an issue where the delegate method  `playbackController:playbackSession:didExitAd:` was not being triggered when an applicable IMA ad was skipped.

* Fixes an issue where ads were not replayed when `ignoringPreviouslyProcessedCuePoints` on `BCOVCuePointProgressPolicy` was disabled.

## Release 6.5.0

#### Breaking Changes

* Support for Xcode 10 has been deprecated and Brightcove SDK releases after 6.5.0 will require you to build your apps with Xcode 11+.

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds support for Live streams with FairPlay DRM. Refer to the [Live DRM](https://live.support.brightcove.com/general/live-drm.html) support pages.

* Adds localizations for traditional Chinese (zh-hant) and simplified Chinese (zh-hans) language scripts.

* Fixes an issue causing the duration and progress labels to display in Times New Roman on devices running iOS 13.

* Fixes the public declarations of Playback Session lifecycle event types `kBCOVPlaybackSessionLifecycleEventPlayRequest`, `kBCOVPlaybackSessionLifecycleEventPauseRequest`, `kBCOVPlaybackSessionLifecycleEventAdSequenceEnter`, `kBCOVPlaybackSessionLifecycleEventAdSequenceExit`, `kBCOVPlaybackSessionLifecycleEventAdEnter`, `kBCOVPlaybackSessionLifecycleEventAdExit`, `kBCOVPlaybackSessionLifecycleEventAdProgress`, `kBCOVPlaybackSessionLifecycleEventAdPause` and `kBCOVPlaybackSessionLifecycleEventAdResume` which can be found in the framework header BCOVPlaybackSession.h.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports version 4.4.5 of the Google Cast SDK for iOS. 

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for Live Streams with Server-Side Ad Insertion. Refer to the [Overview: Advanced Player Toolkit for Live SSAI](https://live.support.brightcove.com/live-api/ssai/overview-player-enhancements-live-ssai.html) pages for details.

## Release 6.4.5

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an exception which occurred when calling `setVideos:` more than once for a single  `BCOVPlaybackController` object. The exception error message includes the text `Exception 'Cannot remove an observer...`.

## Release 6.4.4

### Brightcove Player SDK for tvOS (Core)

#### Additions and Improvements

* Extends support for Picture-in-Picture by adding `showPictureInPictureButton` to `BCOVPUIPlayerViewOptions`. When set to true, a Picture-in-Picture button will be added to the player controls on supported devices. Refer to the VidoCloudBasicPlayer sample project for example code.

* Adds support for AirPlay 2. Refer to the AirPlay section of the SDK Core README for details on adding AirPlay 2 support to your apps.

* Adds the optional BCOVTVPlayerViewDelegate method `- (BOOL)playerViewShouldRequireLinearPlayback:(BCOVTVPlayerView *)playerView;`. Refer to the [BCOVTVPlayerViewDelegate](https://docs.brightcove.com/ios-sdk/Protocols/BCOVTVPlayerViewDelegate.html) reference.

* Fixes an issue where setting the BCOVPlaybackController `shutter` property from a non-main thread generated an exception.

#### Breaking Changes

* Removes the `defaultControlsViewStrategy` option on `BCOVPlayerSDKManager`. Use the built-in PlayerUI controls instead; see the Built-In PlayerUI Controls section in the README for details.

### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes a crash which occurred when getting or setting the `shutter` property of the BCOVPlaybackController from a non-main thread.

## Release 6.4.3

#### Breaking Changes

* Release 6.4.3 of the Brightcove Player SDK for iOS deprecates BrightcoveOUX, replacing it with the SSAI Plugin for Brightcove Player SDK for iOS. Refer to the OnceUX or SSAI README for instructions on migrating your app to the new BrightcoveSSAI framework.

### Brightcove Player SDK for tvOS (Core)

#### Additions and Improvements

* Adds support for VoiceOver to the built-in BCOVTVPlayerUI controls.

* Adds the `BCOVTVAccessibilityDelegate` protocol to allow customization of some accessibility labels.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports version 3.9.0 of the Google IMA SDK for iOS. 

* Adds default values for the `playerType` and `playerVersion` properties of the IMASettings object.

### SSAI Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Introduces the SSAI Plugin. Refer to the OnceUX or SSAI README for instructions on migrating your apps to the new BrightcoveSSAI framework.

* Provides access to the VMAP data retrieved in response to a `-setVideos:` call to the Playback Controller. Refer to the SSAI README for details.

* Fixes an issue which could cause rewind or jump-back to fail, and which could prevent a preroll ad from playing.

### OnceUX Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Deprecates the OnceUX Plugin. Support for OnceUX is now provided by the SSAI Plugin for Brightcove Player SDK for iOS. Refer to the README for information on migrating your apps to BrightcoveSSAI.

* Provides access to the VMAP data retrieved in response to a `-setVideos:` call to the Playback Controller. Refer to the OnceUX README for details.

* Fixes an issue which could cause rewind or jump-back to fail, and which could prevent a preroll ad from playing.

## Release 6.4.2

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds support for the Brightcove Playback Authorization Service.

* Fixes an issue where `player_width` and `player_height` were being reported as 0 in analytics for 360° videos.

* Fixes an issue where the fullscreen toggle button remained visible after entering VR Goggles mode for 360° videos.

* Adds constants for common values in property/paramater dictionaries. You can find these near the top of:

    * BCOVAnalytics.h
    * BCOVAnalyticsSession.h
    * BCOVCuePoint.h
    * BCOVPlaybackService.h
    * BCOVPlaylist.h
    * BCOVSource.h
    * BCOVVideo.h
    
* BCOVBasicSessionLoadingPolicy has been deprecated. Refer to the `Preloading Videos` section of the README for guidance on using multiple playback controllers to achieve a preloading effect. 

### OnceUX Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an issue where the `creativeView` ad tracking event could be reported twice for each ad.

* Adds ability to obtain VMAP data after it has been recieved by observing the `kBCOVOUXVMAPResponseReceivedNotification` (now `kBCOVSSAIVMAPResponseReceivedNotification`) notification.

## Release 6.4.1

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds support for VoiceOver to the built-in BCOVPlayerUI controls.

* Removes the `kBCOVOfflineVideoManagerHTTPMaximumConnectionsPerHostKey` option to BCOVOfflineVideoManager initialization. Use the BCOVOfflineVideoManagerDelegate `-didCreateSharedBackgroundSesssionConfiguration:` method instead.

### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for honoring the video Advertising setting (Free or Ad Supported).

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for honoring the video Advertising setting (Free or Ad Supported).

## Release 6.4.0

#### Breaking Changes

* The minimum iOS Deployment Target for all Brightcove Native Player for iOS frameworks is now iOS 10.0.

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds functionality to select a preferred peak bitrate for AVPlayer. Refer to the `Setting a Preferred Bitrate` section of the README as well as the `preferredBitrateConfig` property on the `BCOVPUIPlayerViewOptions` class.

* Fixes an issue where the status information of offline video downloads was being deleted. This issue is present only in Release 6.3.11.

### Google Cast Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds new support for integrating Google Cast with your application.

### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for tvOS.

* Supports version 6.26.0 of the FreeWheel AdManager framework for iOS and tvOS.

## Release 6.3.12

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Removes references to UIWebView.

* Fixes an issue where the status information of offline video downloads was being deleted. This issue is present only in Release 6.3.11.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports IMA 3.11.3 for iOS which, among other improvements, removes references to UIWebView. When running on an iOS 9.x device, configure IMAAdsRenderingSettings to use Safari when opening landing pages in response to taps on "Learn More" or companions ads.

```objc
IMAAdsRenderingSettings *renderSettings = [[IMAAdsRenderingSettings alloc] init];
renderSettings.webOpenerPresentingController = nil;
renderSettings.webOpenerDelegate = self; // optional
```

## Release 6.3.11

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue where the BCOV Offline Video Manager failed to detect the deletion of videos via the device Settings app (General --> iPhone (or iPad) Storage).

* Clarifies documentation for the `BCOVVideo.playableOffline` property.

## Release 6.3.10

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes a documentation error in the BCOVOfflineVideoStatus Class Reference.

### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports version 6.25.0 of the FreeWheel AdManager framework for iOS.

* Fixes an issue where, while looping a video with postroll ads, the lifecycle event kBCOVPlaybackSessionLifecycleEventEnd was sent only the first time the video reached its end.

## Release 6.3.9 

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue with video downloads in which the load on the main thread increased as the number of stored videos increased.

## Release 6.3.8

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue where requesting a download of a rented video would fail FairPlay authentication in some regions when 24-Hour Time was turned off in the device Date & Time settings (Settings -> General -> Date & Time).

## Release 6.3.7

#### Additions and Improvements

* Corrects the release version number.

## Release 6.3.6

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Improves performance of the BCOVOfflineVideoManager method `-videoObjectFromOfflineVideoToken:`.

* Fixes a crash which could occur while downloading videos for offline viewing.

* Fixes a crash which could occur when a video failed to load.

## Release 6.3.5

#### Breaking Changes

* The Brightcove Native Player for iOS now requires Xcode 9.0 or higher.

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds SDK Reference documentation for built-in tvOS player controls (`BCOVTVPlayer`).

* Fixes an issue where downloading secondary tracks could cause an additional, unrequested video rendition to be downloaded.

* Fixes the declaration of the Closed Caption button in BCOVPlayerUI.

## Release 6.3.4

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Adds BCOVAttributions.h, acknowledging open source software which may be contained in some portions of the Brightcove Native Player SDK.

* Fixes an issue with Sidecar Subtitles where text tracks added to a manifest with pre-existing text tracks were not available to the user. Affects Dynamic Delivery only.

### OnceUX Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Fixes an issue where a `BCOVVideo` with a single `BCOVSource` failed to play when the `BCOVSource`'s `deliveryMethod` was not set to `kBCOVSourceDeliveryHLS` or `kBCOVSourceDeliveryOnce`.

## Release 6.3.3

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

- The TV Player UI now supports playback of live and live DVR streams with controls specific to each type of stream.

- The `BCOVTVPlayerView` class has a new `playerType` property, of type `BCOVTVPlayerType`. This property lets you specify whether the TV Player View will be used for VOD, live, or live DVR presentation.

- The `BCOVTVPlayerType` enumeration was added to let you specify VOD, live, or live DVR playback in the TV Player UI. The enumerated values are `BCOVTVPlayerTypeVOD` for video-on-demand, `BCOVTVPlayerTypeLive` for live, and `BCOVTVPlayerTypeLiveDVR` for live DVR playback.

- Fixes an issue in the Offline Video Manager where a download stopped by the user by terminating the app would result in a `downloadState` set to `BCOVOfflineVideoDownloadStateCompleted` instead of `BCOVOfflineVideoDownloadStateTracksError` in its associated `BCOVOfflineVideoStatus` object.

### OnceUX Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

- Fixes an issue where HTTP video sources could be selected over HTTPS sources. HTTPS is the preferred source.

### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

- Supports version 6.22.0 of the FreeWheel AdManager framework for iOS.

- Fixes an issue where a `videoView` event was sent before the `slotImpression` event when preroll ads were present.

## Release 6.3.2

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

##### Offline Video Manager

Additions and improvements in the `BCOVOfflineVideoManager` class.

**FairPlay License Renewal**

```
- (void)renewFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken
                       video:(BCOVVideo *)video
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;
```

This method, used for renewing the FairPlay license for an offline video, replaces the older method wtihout a `video` parameter. The video parameter is a recently retrieved `BCOVVideo` object from the Playback API or Playback Service class, and is used to provide updated key server exchange URLs. Key server URLs are set to expire after a certain amount of time, so this method will allow you to renew your licenses even after the original URLs have expired.

**FairPlay License Invalidation**

```
- (void)invalidateFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken;
```
This method allows you to invalidate a FairPlay license before the license has expired, by deleting the license from storage. This is a secure way to make sure that the video is not playable on the device. If desired, a new license can be acquired using the `renewFairPlayLicense:video:parameters:completion:` method above.

A new error code, `kBCOVOfflineVideoManagerErrorCodeInvalidLicense` will be returned in a playback session lifecycle event of type `kBCOVPlaybackSessionLifecycleEventFail` if you attempt to play a video with an invalid license.

**FairPlay License Expiration Retrieval**

```
- (NSDate *)fairPlayLicenseExpiration:(BCOVOfflineVideoToken)offlineVideoToken;
```
This method provides a convenient way to determine the date and time at which the video will no longer be playable. Normal FairPlay rental licenses return an `NSDate` object representing the expiration of the license. A purchase license, or videos without FairPlay, will return `NSDate.distantFuture`.

If the license was invalidated, or was never acquired, this method will return nil.

**Other Improvements**

- Improves task resume behavior for aggregate track downloads (secondary audio and caption tracks). Previously, a paused aggregate track download may not have been able to resume downloading if it was paused.

#### Breaking Changes

In the BCOVOfflineVideoManager class, this method has been deprecated.

```
- (void)renewFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;
```
A similar method with a new `video` parameter is now available for renewing a FairPlay license:

```
- (void)renewFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken
                       video:(BCOVVideo *)video
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;
```
You can pass `nil` as the `video` parameter, but if you do, this method will no longer work after the URLs from the original downloaded video have expired.

We recommend you always pass a `BCOVVideo` object that was recently retrieved from the Playback API or Brightcove Service class as the `video` parameter.


### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports version 3.7.0 of the Google IMA SDK for iOS. The Podspec for the IMA Plugin for Brightcove Player SDK for iOS references version 3.7.0.1 of the Google IMA iOS SDK as instructed by the [IMA Release History](https://developers.google.com/interactive-media-ads/docs/sdks/ios/v3/history).

* Adds the ability to modify an IMAAdsRequest object immediately before the IMA Plugin calls the `IMAAdsLoader -requestAdsWithRequest:`  method. For details, refer to the "Modifying the IMAAdsRequest" section of the Brightcove IMA Plugin README.

### OnceUX Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* VAST 3.0 CreativeExtensions embedded in an ad are now accessible through the `BCOVAd`'s properties dictionary. The header file BCOVOUXConstants.h has sample code showing how to access these values.

## Release 6.3.1

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

##### Offline Video Manager

Adds a new method to the `BCOVOfflineVideoManagerDelegate` protocol:

```
- (void)didCreateSharedBackgroundSesssionConfiguration:(NSURLSessionConfiguration *)backgroundSessionConfiguration;
```

This method is called after the background `NSURLSessionConfiguration` object is created, and before it's used to create the shared `AVAssetDownloadURLSession` object that's used to download videos. You can use this configuration object to set various options specified for the NSURLSessionConfiguration in NSURLSession.h, such as the `discretionary` flag, or the `HTTPMaximumConnectionsPerHost` setting.

You should *not* set the `allowsCellularAccess` property; that is set through the `kBCOVOfflineVideoManagerAllowsCellularDownloadKey` setting passed to `-initializeOfflineVideoManagerWithDelegate:options:`.

##### General

- Fixes an issue where the HTTP version of some WebVTT URLs was being used instead of HTTPS. This only occurred when using Sidecar Subtitles with a legacy Video Cloud account.

## Release 6.3.0

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

##### Built-In TV Player Controls for tvOS

Version 6.3 of the Brightcove Native Player SDK includes built-in controls for playback in tvOS on Apple TV. For full details about using the built-in TV Player UI with the Brightcove Native Player SDK, see our [TV Player guide](TVPlayer.md).

#### Breaking Changes

- The `BCOVPlaybackSessionProvider` protocol method `-(id)playbackSessionsForVideos:` has been deprecated. This method had no practical use so no code changes are required in your app.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements
* Fixes an issue where pre-roll ads would re-play after seeking to the start of the video when using an IMA ads request policy (`BCOVIMAAdsRequestPolicy`) with a `BCOVCuePointProgressPolicy` for which the `ignoringPreviouslyProcessedCuePoints` parameter is set to YES.
* Fixes an issue where some VMAP URLs would cause the Google IMA library to crash when a post-roll was played.

## Release 6.2.2

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

##### FairPlay License Renewal

Adds the ability to renew FairPlay licenses for downloaded videos without re-downloading the video. To support these feature, there are a few new items in BCOVOfflineVideo.h:

The following method lets you renew the FairPlay license by specifying new license terms along with the offline video token.

```
- (void)renewFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;
```

The `kBCOVOfflineVideoLicenseAbsoluteExpirationTimePropertyKey` is used to obtain the absolute expiration time of an offline `BCOVVideo` object that uses a FairPlay rental license.

```
extern NSString * const kBCOVOfflineVideoLicenseAbsoluteExpirationTimePropertyKey;
```
Previously downloaded videos wll not have this property, but it will be added once the license is renewed.

#### Other Improvements

* Fixes an issue where FairPlay licenses could not be generated on devices using non-Gregorian calendars.
* Fixes an issue where FairPlay rental licenses did not respect the set duration. To ensure that licenses have been issued properly for your users' content, we recommend renewing any FairPlay license issued using version 6.2.1 or earlier of the Brightcove SDK. License renewal will not require the video to be downloaded again. (Tip: if a downloaded video does not have the `kBCOVOfflineVideoLicenseAbsoluteExpirationTimePropertyKey` property, its license should be renewed.)
* Fixes an issue that caused apps using the Brightcove SDK to crash when running on iOS 9.
* Fixes an issue where VTT files containing extra empty lines could crash when downloaded and played back on iOS 10 (Sideband Subtitles).

## Release 6.2.1

#### Breaking Changes

* The minimum iOS Deployment Target for all Brightcove Native Player for iOS frameworks is now iOS 9.0.

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

Adds the ability to store playback analytics for videos that have been downloaded and played while offline. Analytics are transmitted to Brightcove servers once the device comes back online.

A few new items are added to support this feature:

* `kBCOVOfflineVideoManagerAnalyticsStorageFullWarningNotification` is a new NSNotification name that you can register to observe. This notification is sent when the storage for offline analytics has reached a prescribed limit (500 MiB by default). When this occurs, you have the option of encouraging your user to go back online, at which point stored analytics data will be sent to Brightcove servers.

* `kBCOVOfflineVideoManagerAllowsCellularAnalyticsKey` is the dictionary key for a setting passed to the Offline Video Manager when it is initialized. You can pass @(YES) to allow analytics collected while offline to be transferred over a cellular connection. Pass @(NO) to only transfer over a WiFi connection. This setting is optional, and the default value is @(YES).

* `kBCOVOfflineVideoManagerAnalyticsStorageLimitKey` is the dictionary key for a setting passed to the Offline Video Manager when it is initialized. This setting is an NSNumber that determines the maximum amount of storage space (in Bytes) that will be allowed for storing analytics collected for videos played offline. The default value is 500 MiB, and may be set as low as 1 MiB. When the limit is reached, only video_view events will be stored, and other events will start being dropped.

### Omniture Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Adds support for Adobe Marketing Cloud v4.14.1 and Adobe Video Heartbeat v2.0.1.

## Release 6.2.0

### Brightcove Player SDK for iOS (Core)

#### Breaking Changes

* The `BCOVCatalogService`, also referred to as the Brightcove Media API, has reached end-of-life status and been removed from the Brightcove Native Player SDK. If your app uses the BCOVCatalogService, you must update it to use the [BCOVPlaybackService](https://docs.brightcove.com/ios-sdk/Classes/BCOVPlaybackService.html).

* You can no longer download caption files using Sideband Subtitles in iOS 11. Sideband Subtitles is a workaround for incomplete track download support in iOS 10. As a result, you can no longer pass `kBCOVOfflineVideoManagerSubtitleLanguagesKey` as an option when requesting a video download. iOS 11 supports downloading of both subtitle and audio tracks; see "Addtions and Improvements" below for more details. Caption tracks that were downloaded using Sideband Subtitles will continue to play correctly on iOS 11.

#### Additions and Improvements

* The `BCOVPlayerSDKManager` has a new `version` class method which returns an NSString containing the SDK version.

* When developing for iOS 11 and later, in addition to HLS videos, you can download all secondary caption and audio tracks using iOS 11's new AVAggregateAssetDownloadTask class. This support includes the folowing changes:

##### BCOVOfflineVideoDownloadState
The `BCOVOfflineVideoDownloadState` enumeration adds the following values:

```
    /* iOS 11+ only: Download of extra tracks requested but not yet reporting progress */
    BCOVOfflineVideoDownloadStateTracksRequested = 7,
    
    /* iOS 11+ only: Download of extra tracks is progressing normally */
    BCOVOfflineVideoDownloadStateTracksDownloading = 8,
    
    /* iOS 11+ only: Download of extra tracks was paused */
    BCOVOfflineVideoDownloadStateTracksSuspended = 9,
    
    /* iOS 11+ only: Download of extra tracks completed normally */
    BCOVOfflineVideoDownloadStateTracksCancelled = 10,
    
    /* iOS 11+ only: Download of extra tracks completed normally */
    BCOVOfflineVideoDownloadStateTracksCompleted = 11,
    
    /* iOS 11+ only: Download of extra tracks terminated with an error */
    BCOVOfflineVideoDownloadStateTracksError = 12
```

##### BCOVOfflineVideoManagerDelegate
The `BCOVOfflineVideoManagerDelegate` protocol adds the following optional methods signatures:

This method is used on iOS 11.0+ to provide feedback about track downloads:

```
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
             aggregateDownloadTask:(AVAggregateAssetDownloadTask *)aggregateDownloadTask
            didProgressTo:(NSTimeInterval)progressPercent
        forMediaSelection:(AVMediaSelection *)mediaSelection
```

This method is called when an individual track download is complete:

```
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
didFinishMediaSelectionDownload:(AVMediaSelection *)mediaSelection
```

This method is called when all requested track downloads are complete:

```
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
didFinishAggregateDownloadWithError:(NSError *)error
```

##### BCOVOfflineVideoStatus
The `BCOVOfflineVideoStatus` class includes a new property for managing secondary track downloads:

```
@property (nonatomic, readonly) AVAggregateAssetDownloadTask *aggregateDownloadTask
```

##### BCOVOfflineVideoManager
Secondary track include captions, subtitles, and audio tracks. You create a list of tracks to download as an array of AVMediaSelections, and iOS will download them all together using an AVAggregateAssetDownloadTask. You can only start a track download after the primary video has been downloaded.

BCOVOfflineVideoManager has several new methods to help you start and manage secondary track downloads. These new methods apply only to iOS 11.

This method is used to begin downloading additional caption and audio tracks. Track selections are specified as AVMediaSelections. This request can only be made after the related video download has completed. Be sure the  `offlineVideoToken:didFinishDownloadWithError:` delegate callback method has already been called for this video.

```
- (void)requestMediaSelectionsDownload:(NSArray<AVMediaSelection *> *)mediaSelections
                     offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
```

This method returns the AVMediaSelectionGroup for a downloaded video.
You can get the media selection group for audio or caption tracks by specifying AVMediaCharacteristicAudible or AVMediaCharacteristicLegible respectively.

```
- (AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(NSString *)mediaCharacteristic
                                                   offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
```

This is a convenience method that returns the array of AVMediaSelectionOptions that have already been downloaded for an associated offline video as reported by the AVAssetCache for the underlying AVURLAsset.

You can specify AVMediaCharacteristicAudible or AVMediaCharacteristicLegible to find out what audio or caption tracks have been downloaded.

```
- (NSArray<AVMediaSelectionOption *> *)downloadedMediaSelectionOptionsForMediaCharacteristic:(NSString *)mediaCharacteristic
                                                                           offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
```
 
The `forceStopAllDownloadTasks` method is implemented as a workaround for a bug on iOS 11.0.x and iOS 11.1.x. On these iOS versions, a track download will resume to completion if it was paused and then cancelled. The only way to stop the download is to force all the downloads in progress to stop wtih an error.
 
This method should not be used on other versions of iOS; you can cancel an aggregate download task normally on iOS 11.2 by calling `cancelVideoDownload`.
 
```
- (void)forceStopAllDownloadTasks
```

For full details about downloading video for offline playback, see the *iOS App Developer's Guide to Video Downloading and Offline Playback with HLS in the Brightcove Player SDK for iOS*, in OfflinePlayback.md in the main SDK directory.

## Release 6.1.4

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements
* The PlayerUI controls, and full-screen view of the PlayerUI now respect the new iOS 11 Safe Areas. This ensures that PlayerUI views display properly on iPhone X.
* Fixes an issue that caused link errors when building with the core Native Player SDK framework using Xcode 8.
* The method `-[BCOVOfflineVideoManager variantBitratesForVideo:completion:]` now passes an array containing NSNumber objects to the completion handler, instead of incorrectly passing an array of NSString objects.

## Release 6.1.3

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements
* Fixes an issue that prevented subtitles from updating properly when playing back offline videos.

## Release 6.1.2

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements
* Fixes an issue that prevented FairPlay videos from playing on Apple TV. This only affected Video Cloud accounts using Dynamic Delivery.

## Release 6.1.1

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements
* Adds BCOVPUIAdControlView.h to the BrightcovePlayerSDK.h umbrella header to fix a compiler warning.
* Fixes an issue where code coverage symbols were present in the framework executables. This caused link errors in some build configurations.

## Release 6.1.0

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements
* Adds support for downloading and playing back clear (non-DRM) video content from Video Cloud accounts using Dynamic Delivery. Previously only FairPlay-protected content could be downloaded.
* Fixes an issue on iOS 11 where downloaded FairPlay videos would not play back until the app was restarted.
* The `BCOVVideo` class has a new BOOL `usesFairPlay` property that returns YES if the video contains a FairPlay-encrypted source. This only applies to videos retrieved from a Dynamic Delivery account.
* The `BCOVPlayerSDKManager` singleton class has a new `sessionID` property. This `NSString *` property is a unique read-only value that remains constant until the app is relaunched. This value is sent with all analytics reports and can be used to help diagnose playback issues. Please see the "Tracking Errors" section of the README for full details.
* The `BCOVPlaybackService` class has four new methods for converting JSON response data from the Playback Service API. These methods are useful if you need to retrieve data from the Playback Service API (through a proxy server, for example) and then convert them to objects you can work with in the SDK. These methods work identically to the methods found in the `BCOVCatalogService` class with the same names:
	* `+ (BCOVSource *)sourceFromJSONDictionary:(NSDictionary *)json`
	* `+ (BCOVCuePoint *)cuePointFromJSONDictionary:(NSDictionary *)json`
	* `+ (BCOVPlaylist *)playlistFromJSONDictionary:(NSDictionary *)json`
	* `+ (BCOVVideo *)videoFromJSONDictionary:(NSDictionary *)json`
* The `BCOVPUIAdControlView` class is now fully declared in BCOVPUIAdControlView.h so that you can use the `BCOVPUIPlayerView` property `adControlsView`. Previously, `BCOVPUIAdControlView` was only a forward class declaration.


### FreeWheel Plugin for Brightcove Player SDK for iOS

#### Breaking Changes

* Release 6.1.0 of the FreeWheel Plugin adds support for version 6.17.5 of the FreeWheel SDK, which introduces several deprecations and new classes. As a result, the return type of `BCOVFWSessionProviderAdContextPolicy` has changed from `id<FWContext>` to `BCOVFWContext*`. Please see the "Quick Start" section of the FreeWheel Plugin README, and the iOS Player Samples, for full details.

## Release 6.0.6

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* The `BCOVPlaybackController` protocol has a new `usesExternalPlaybackWhileExternalScreenIsActive` property. Setting this `BOOL` property sets the similarly named `usesExternalPlaybackWhileExternalScreenIsActive` property of the current playback session's AVPlayer, as well as that of any subsequent sessions. This property has no effect if `allowsExternalPlayback` is false.
* The `BCOVPlaybackController` protocol's `-setAllowsExternalPlayback:` method has been turned into the `BOOL allowsExternalPlayback` property.

### IMA Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements

* Supports version 3.6.0 of the Google IMA iOS SDK Framework.

## Release 6.0.5

#### Additions and Improvements

* Fixes an issue where dynamic frameworks were missing bitcode.


### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue where a zero-length file in the framework would cause a build warning.
* Fixes an issue where adding the Brightcove Player SDK using CocoaPods required the manual addition of the MediaAccessibility framework. 


## Release 6.0.4

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Fixes an issue where certain video names caused those videos to fail to download for offline playback. Refer to the _"Specifying the Download Display Name"_ section of the OfflinePlayback.md document.
* This release exposes the `HTTPMaximumConnectionsPerHost` property of the `NSURLSessionConfiguration` object used to construct the `AVAssetDownloadTask` which downloads a video for offline playback. Set this value when calling the `+initializeOfflineVideoManagerWithDelegate:options:` method of the `BCOVOfflineVideoManager` by providing an NSNumber value for the `kBCOVOfflineVideoManagerHTTPMaximumConnectionsPerHostKey` key in the `options` dictionary.

### OnceUX Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements
* Server-Side Ad Insertion (SSAI) is now supported for both non-DRM and DRM videos ingested for Dynamic Delivery.


## Release 6.0.3

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* When playing offline video, subtitles now render according to the user captioning preferences of the device.
* Fixes an issue in which the Live button would frequently change state during live streaming.
* Server-Side Ad Insertion (SSAI) is now supported for non-DRM videos ingested for Dynamic Delivery. This update requires the use of the OnceUX Plugin for Brightcove Player SDK for iOS.

### OnceUX Plugin for Brightcove Player SDK for iOS

#### Additions and Improvements
* Server-Side Ad Insertion (SSAI) is now supported for non-DRM videos ingested for Dynamic Delivery.


## Release 6.0.2

### Brightcove Player SDK for iOS (Core)

#### Additions and Improvements

* Improves error reporting for downloading videos. Previoiusly, some errors were recorded but not reported right away to the Offline Video Manager delegate.
* Fixes pause and resume functionality for downloading videos.
* Fixes an issue where the UI could hang when using the `AVPlayerViewController` class.


## Release 6.0.1

#### Breaking Changes

* This and future releases of Brightcove Native Player for iOS will include all software components, all having the same version number. When building your app with Brightcove Native Player for iOS components, the component version numbers must always match. As an example, when using version 6.0.1 of the FreeWheel Plugin for Brightcove Player SDK for iOS, you must also use version 6.0.1 of the core Brightcove Player SDK for iOS. Each component will continue to be available from individual GitHub repositories.

* The Brightcove Podspecs repository has moved and the Pods have been renamed. The Podspecs are now available at [https://github.com/brightcove/BrightcoveSpecs](https://github.com/brightcove/BrightcoveSpecs).

* All CocoaPods podfiles that use Brightcove frameworks should include a reference to the Brightcove Podspecs at the top of the podfile:

```
source 'https://github.com/brightcove/BrightcoveSpecs.git'
```

* CHANGELOG.md (this file) has been consolidated to include all Brightcove Native Player for iOS software components.

### Brightcove Player SDK for iOS (Core)

#### Breaking Changes

* The BrightcoveFairPlay module is now integrated into the core BrightcovePlayerSDK module and framework. No functional code changes are required, but you should make these changes for your build:
	* Remove BrightcoveFairPlay.framework from your project.
	* If using CocoaPods, remove all references to BrightcoveFairPlay from your Podfiles, and then update.
	* In your source code, change any #includes from `<BrightcoveFairPlay/header_name.h>` to `<BrightcovePlayerSDK/header_name.h>`.
	* Remove any imports that refer to the BrightcoveFairPlay module.
* The BrightcoveSidecarSubtitles module is now integrated into the core BrightcovePlayerSDK module and framework. No functional code changes are required, but you should make these changes for your build:
	* Remove BrightcoveSidecarSubtitles.framework from your project.
	* If using CocoaPods, remove all references to BrightcoveSidecarSubtitles from your Podfiles, and then update.
	* In your source code, change any #includes from `<BrightcoveSidecarSubtitles/header_name.h>` to `<BrightcovePlayerSDK/header_name.h>`.
	* Remove any imports that refer to the BrightcoveSidecarSubtitles module.

#### Additions and Improvements

* Supports downloading FairPlay-encrypted HLS videos, and playing them back from storage while online or offline.
* New classes and types to support offline playback: `BCOVOfflineVideoManager`, `BCOVOfflineVideoStatus`, `BCOVOfflineVideoToken`, `BCOVOfflineVideoDownloadState`.
* Please see our app developer's guide for full details: "iOS App Developer's Guide to Video Downloading and Offline Playback with FairPlay" in OfflinePlayback.md.
* The `BCOVVideo` class has three new properties:
	* `BOOL canBeDownloaded`: Returns YES if this video object can be downloaded for offline playback
	* `BOOL offline`: Returns YES if this instance refers to an offline video.
	* `BOOL playableOffline`: Returns YES if this instance refers to an offline video playable from the device's local storage. Returns NO if the video has not completed downloading, or if the video has been purged and needs to be re-downloaded.
* The publisher ID can be nil when calling `-[BCOVFPSBrightcoveAuthProxy initWithPublisherId:applicationId:]`. Neither value is needed for Dynamic Delivery accounts.
* Fixes an issue where multiple check marks could appear unintentionally when making language or audio selections in the Audio & Subtitles control's view in the PlayerUI.
* Adds the `BCOVPlayerSDKManager` class method `sharedManagerWithOptions:` that returns the same singleton `BCOVPlayerSDKManager` class instance, but accepts an options dictionary as a parameter. This is reserved for future use related to debug logging.


### FreeWheel Plugin for Brightcove Player SDK for iOS
#### Additions and Improvements
* The FreeWheel Plugin for Brightcove Player SDK now supports version 6.15.0 of the FreeWheel Ad Manager framework.

### IMA Plugin for Brightcove Player SDK for iOS
#### Additions and Improvements
* Fixes an issue where the video view start time was sometimes reported incorrectly for Quality of Service metrics.

### Omniture Plugin for Brightcove Player SDK for iOS
#### Additions and Improvements
* Fixes an issue where the video view start time was sometimes reported incorrectly for Quality of Service metrics.

### OnceUX Plugin for Brightcove Player SDK for iOS
#### Additions and Improvements
* Fixes an issue where the video view start time was sometimes reported incorrectly for Quality of Service metrics.
