#6.0.0
### Additions and Improvements
* Supports downloading FairPlay-encrypted HLS videos, and playing them back from storage while online or offline.
* New classes and types to support offline playback: `BCOVOfflineVideoManager`, `BCOVOfflineVideoStatus`, `BCOVOfflineVideoToken`, `BCOVOfflineVideoDownloadState`.
* Please see our app developer's guide for full details: [iOS App Developer's Guide to Video Downloading and Offline Playback with FairPlay](OfflinePlayback.md)
* The `BCOVVideo` class has three new properties:
	* `BOOL canBeDownloaded`: Returns YES if this video object can be downloaded for offline playback
	* `BOOL offline`: Returns YES if this instance refers to an offline video.
	* `BOOL playableOffline`: Returns YES if this instance refers to an offline video playable from the device's local storage. Returns NO if the video has not completed downloading, or if the video has been purged and needs to be re-downloaded.
* The publisher ID can be nil when calling `-[BCOVFPSBrightcoveAuthProxy initWithPublisherId:applicationId:]`. Neither value is needed for Dynamic Delivery accounts.


### Breaking Changes
* The `BrightcoveFairPlay` module is now integrated into the core `BrightcovePlayerSDK` module and framework. No functional code changes are required, but you should make these changes for your build:
	* Remove BrightcoveFairPlay.framework from your project.
	* If using CocoaPods, remove all references to `BrightcoveFairPlay` from your Podfiles, and then update.
	* In your source code, change any #includes from `<BrightcoveFairPlay/header_name.h>` to `<BrightcovePlayerSDK/header_name.h>`.
	* Remove any imports that refer to the `BrightcoveFairPlay` module.

# 5.3.3
* The default source selection policy has been changed to prefer HTTPS sources over HTTP.
* Fixes an issue where switching AirPlay between an AppleTV and an iOS device could cause the iOS device to stall.

# 5.3.2
### Additions and Improvements
* Adds a dictionary key to BCOVPlaybackController for an AVPlayerViewController compatibility mode. Setting this dictionary key to @YES allows apps (particularly on tvOS) to use the AVPlayerViewController's playerLayerView. Setting this key to @NO uses the BCOVSessionProvider's internal AVPlayerLayer. Please note that the use of Advertising plugins with this key set to @YES is not supported.

# 5.3.1
### Additions and Improvements
* Fixes an issue where panning a 360 video did not work properly at the bottom of the video view when controls were hidden.
* Fixes an issue where an unused reference to UIImagePickerController unnecessarily requires the app developer to declare reasons for its usage in the app submission process (the NSPhotoLibraryUsageDescription privacy desciption). The reference to UIImagePickerController has been removed.
* The constant `NSString` `kBCOVDefaultFairPlayApplicationCertificateIdentifier` was created to pass as an identifier for default application certificates passed to `-addFairPlayApplicationCertificate:identifier:`.
* The `BCOVPlaybackController` method `-addFairPlayApplicationCertificate:identifier:` was created to let you add FairPlay application certificates to a playback controller after it has been created. This is used in conjunction with the Brightcove FairPlay plugin. See the Brightcove FairPlay plugin's README.md for full details.

# 5.3.0
### Breaking Changes
* The `BCOVCatalogService` (Media API) class has been deprecated. The `BCOVCatalogService` class methods generate compiler deprecation warnings, but are still fully functional. Please update your projects to use the `BCOVPlaybackService` (Playback API) for retrieving video playlists. Code examples are available in the Quick Start section of the README.md and in the [iOS Player Samples](https://github.com/brightcoveos/ios-player-samples) on Github.
* The `BCOVMediaRequestFactory` is an extension of the Brightcove Media API and has therefore been deprecated.

### Additions and Improvements

####Video 360

This release includes support for 360 degree videos. Videos that are tagged in Video Cloud with a "projection" field with the value "equirectangular" are identified as Video 360. These videos will be loaded and played in the same way as other videos, but they will be displayed in an OpenGL ES layer instead of an AVPlayerLayer.

The PlayerUI also has built-in support for Video 360, providing default panning gestures, gyroscopic motion detection for the view, and a new Video 360 button that appears when a Video 360 asset is playing. This button appears only on iPhones, and lets you toggle between the normal view and a "VR Goggles" view, where the screen is split in two, with the same scene rendered for each eye so that the device can be used with head-mounted VR Goggles, such as Google Cardboard.

Additions for each file are as follows.

####BCOVPlaybackController.h
The `BCOVVideo360SourceFormat` enumeration type has been added to indicate the format of the current video 360 projection. The following values are supported:

* `BCOVVideo360SourceFormatNone`: used for normal (non-360) videos
* `BCOVVideo360SourceFormatEquirectangular`: indicates a video supplied in equirectangular format. No other 360 formats are supported at this time.

The `BCOVVideo360ProjectionStyle` enumeration type has been added to indicate how the 360 video is projected on to the OpenGL ES layer. The following values are supported:

* `BCOVVideo360ProjectionStyleNormal`: typical projection of a single viewport viewing a rectangular portion of the 360 video mapped onto a sphere.
* `BCOVVideo360ProjectionStyleVRGoggles`: double projection of a viewport viewing a rectangular portion of the 360 video mapped onto a sphere.

The constant `kBCOVVideo360BaseAngleOfView` has been added to give the approximate vertical angle of a 360 view when the view orientation's zoom is 1.0. Its value is 75 degrees.

The `BCOVVideo360ViewProjection` specifies the position of the virtual camera in Video 360. This class provides the renderer details about how to present the Video 360 view. The following properties are available:

* `CGFloat pan`: Horizontal angle of view in degrees
* `CGFloat tilt`: Vertical angle of view in degrees
* `CGFloat zoom`: Magnification of view
* `CGFloat roll`: Angle of rotation in degrees about the virtual camera's longitudinal axis.
* `CGFloat xOffset`: Horizontal offset of the rendered 360 video in the view. When using a split screen VR Goggles view, the x offset is applied to the left view, and the negative of the offset is applied to the right view.
* `CGFloat yOffset`: Vertical offset of the rendered 360 video in the view.
* `BCOVVideo360SourceFormat sourceFormat`: the format of the source video. Currently only the equirectangular input format, `BCOVVideo360SourceFormatEquirectangular`, is supported.
* `BCOVVideo360ProjectionStyle projectionStyle`: the method for presenting the 360 video on the OpenGL ES layer.

The class method `+(instancetype)viewProjection` is a convenience method for allocating a `BCOVVideo360ViewProjection` instance.

The `BCOVPlaybackController` protocol has a new `BCOVVideo360ViewProjection viewProjection` property. This allows you to set new parameters for the current projection. To change values, read the current `viewProjection` (this gives you a copy of the current `viewProjection` instance), modify the values you want to change, and then set it again with the new modified instance.

####BCOVPUIBasicControlView.h

The `BCOVPUIBasicControlView` class has a new property for the Video 360 button, `BCOVPUIButton *video360Button`.


####BCOVPUICommon.h
The `BCOVPUIViewTag` enumeration has a new `BCOVPUIViewTagButtonVideo360` value for the Video 360 button.

####BCOVPUIPlayerView.h

The `BCOVPUIVideo360NavigationMethod` enumeration type has been added to indicate how the 360 view is physically controlled. The following values are supported:

* `BCOVPUIVideo360NavigationNone`: the PlayerUI will not control the view orientation. Use this if you want to set your own `viewProjection` values in the `BCOVPlaybackController` class.
* `BCOVPUIVideo360NavigationFingerTracking`: the PlayerUI will install finger tracking gestures for panning (pan/tilt) and pinching (zoom).
* `BCOVPUIVideo360NavigationDeviceMotionTracking`: In addition to the finger tracking gestures above, the PlayerUI will use CoreMotion to determine the pan and tilt values for the view.

The `BCOVPUIPlayerViewDelegate` protocol has a new method related to Video 360:

* `- (void)didSetVideo360NavigationMethod:(BCOVPUIVideo360NavigationMethod)navigationMethod projectionStyle:(BCOVVideo360ProjectionStyle)projectionStyle`: This optional delegate method will be called when a new selection has been made with the Video 360 button in the control bar. When this method is called, set the device orientation to landscape if you are using the `BCOVVideo360ProjectionStyleVRGoggles` projection style.

The `BCOVPUIPlayerViewOptions` class has new properties related to Video 360:

* `float panMin`: The minimum allowable value for the pan setting when finger tracking.
* `float panMax`: The maximum allowable value for the pan setting when finger tracking.
* `float panInertia`: Determines speed with which a pan gesture fling decays. Defaults to 1.0. Larger values cause the fling to decay more slowly. Smaller values cause the fling to stop quickly. A value of 0.0 stops panning immediately after touch-up.
* `float tiltMin`: The minimum allowable value for the tilt setting when finger tracking.
* `float tiltMax`: The maximum allowable value for the tilt setting when finger tracking.
* `float zoomMin`: The minimum allowable value for the zoom setting when finger tracking.
* `float zoomMax`: The maximum allowable value for the zoom setting when finger tracking.
* `float rotateMin`: The minimum allowable value for the rotate setting when finger tracking.
* `float rotateMin`: The maximum allowable value for the rotate setting when finger tracking.

The `BCOVPUIPlayerView` class has the following new property:

* `BCOVPUIVideo360NavigationMethod video360NavigationMethod`: The method for controlling the view orientation of a 360 video in the player view.

# 5.2.0
### Additions and Improvements
* Adds buffer optimization to the AVPlayer's playback behavior. See the Buffer Optimization section of the README document for more details.
* Adds an `NSDictionary *options` property. This is a dictionary of key-value pairs used to set options specific to the `BCOVPlaybackController`, such as buffer optimization controls.
* Adds the kBCOVBufferOptimizerMethodKey, kBCOVBufferOptimizerMinimumDurationKey, and kBCOVBufferOptimizerMaximumDurationKey keys for use in the `BCOVPlaybackController`'s `options` dictionary. These keys are used to set values that control buffer optimization behavior. See the Buffer Optimization section of the README document for more details.
* Adds the `BCOVBufferOptimizerMethod` enumeration type. This enum specifies the type of buffer optimization being used in the playback controller. The available values are `BCOVBufferOptimizerMethodNone` and `BCOVBufferOptimizerMethodDefault`.
* Adds a new `- (void)seekWithoutAds:(CMTime)time completionHandler:(void (^)(BOOL finished))completionHandler` method to the `BCOVPlaybackController` class for seeking to a specific time in a video stream without displaying any ads. This call should only be used in conjunction with ad plugins like the Brightcove FreeWheel Plugin or the Brightcove IMA plugin; without them it will have no effect.

# Please note:
* The Brightcove PlayerUI Plugin is integrated into the core Brightcove Player SDK Framework as of Player SDK release 5.1.0. This provides a fully-featured and customizable set of controls in your player.
  * PlayerUI controls are not supported on Apple TV.
  * PlayerUI controls automatically switch to ad mode during playback. This works with Once and FreeWheel ads. Google IMA ads use their own ad controls.

# 5.1.4
### Additions and Improvements
* Fixes a problem where some clickthrough tracking beacons were not sent when tapping the "Learn More" button (and using the OnceUX plugin). Tracking URLs are now handled correctly.

# 5.1.3
### Additions and Improvements
* Superfluous didProgressTo: delegate method calls are filtered out of the progress callback stream. These were generated by the AVPlayer after a seek as it honed in on a specific timecode, and could cause some backwards progress values to be reported.
* The `BCOVPUIPlayerView` has a new `controlsFadingViewVisible` property that allows you to manually set the visible state of the `controlsFadingView`.
* The `BCOVPUIPlayerView` has a new `resetHideControlsIntervalTimer` method that allows you to reset the timer that keeps track of when to hide the controls. If you implement your own controls, you can call this after a user tap to prevent the controls from hiding too soon.
* The `BCOVPUIPlayerViewDelegate` protocol has a new `- (void)playerView:(BCOVPUIPlayerView *)playerView willTransitionToScreenMode:(BCOVPUIScreenMode)screenMode` method. This method will be called just before a screen mode transition (e.g., normal to full screen) occurs. The corresponding `didTransitionToScreenMode...` method will still be called when the transition is complete.
* Fixed a problem where unknown video source types (like Widevine) would not be passed as a `BCOVSource` from the `BCOVCatalogService` or the `BCOVPlaybackService`.
* The full screen behavior of the PlayerUI has been improved. Previously, the full screen button would move the current player view to a new full screen view controller. Now, the player view is moved to a view within the same presenting view controller. This fixes problems related to Google IMA controls; clicking IMA's Learn More button now works properly in full screen mode.
* Fixed a problem where the main thread would stall while waiting for closed caption data from the AVPlayer's current item. This would typically manifest under poor network conditions. Now the closed caption data is retrieved asynchronously. This issue was only present when using the closed caption button in the PlayerUI controls or the closed caption button in the older built-in controls.
* The popover view presented by the closed caption/audio track button in the PlayerUI on an iPad now resizes itself to fit the presented items.

# 5.1.2
### Additions and Improvements
* Fixes a CocoaPods installation problem that caused the PlayerUI controls to display improperly.

# 5.1.1
### Additions and Improvements
* The PlayerView's view states are now reset properly when a new playback controller is installed.
* The delegate property of the Playback Controller is now fully KVO compliant.
* Fixed a crash in iOS 8.x which occurred in rare situations when scrubbing with the progress bar. 

# 5.1.0
### Additions and Improvements
* If you are using any Brightcove plugins with the Brightcove Player SDK, be sure to use the minimum versions listed here:
  * Brightcove Sidecar Subtitles plugin: 2.1.0
  * Brightcove FairPlay plugin: 1.1.0
  * Brightcove Widevine plugin: 2.1.0
  * Brightcove OnceUX plugin: 2.1.0
  * Brightcove FreeWheel plugin: 2.1.0
  * Brightcove IMA plugin: 2.1.0
  * Brightcove Omniture plugin: 1.1.0
  * Brightcove PlayerUI plugin: integrated into the Brightcove Player SDK

* The `BCOVPlaybackController` protocol has an `adsDisabled` property that allows you to disable ad playback in specific situations like restoring an AVPlayer's playback state. To use this feature, follow these steps:
  1. Set `adsDisabled` to `YES`
  2. Seek to the desired time position in the current video
  3. Set `adsDisabled` to `NO` again to resume normal ad behavior

  This feature currently works only with the Brightcove OnceUX plugin, but will be expanded to work with all ad plugins.
* The `BCOVPlaybackController` protocol has a `shutter` property.
  * When set to `YES`, an opaque black view is placed in front of the Playback Controller's view. This can be used to hide the AVPlayer's video at any time.
  * When set to its default value of `NO`, the view becomes transparent.
* The `BCOVPlaybackController` protocol has a `shutterFadeTime` property that lets you set the duration of the animation when showing or hiding the shutter. The default value is zero.
* The `BCOVPUIPlayerViewOptions` class has a new property, `learnMoreButtonBrowserStyle` of type `BCOVPUILearnMoreButtonBrowserStyle`.
   * This property lets you choose whether tapping the "Learn More" button in an ad will launch an external browser (default value), or use an in-app browser. 
   * The in-app browser uses a SFSafariViewController in iOS 9, a WKWebView in iOS 8, or a UIWebView in iOS 7.
* There are several new delegate methods in the `BCOVPUIPlayerViewDelegate` protocol to give you information about what's happening after a "Learn More" button is tapped:
  * `- (void)willOpenInAppBrowserWithAd:(BCOVAd *)ad`
  * `- (void)didOpenInAppBrowserWithAd:(BCOVAd *)ad`
  * `- (void)willCloseInAppBrowserWithAd:(BCOVAd *)ad`
  * `- (void)didCloseInAppBrowserWithAd:(BCOVAd *)ad`
  * `- (void)willOpenExternalBrowserWithAd:(BCOVAd *)ad`
  * `- (void)didReturnFromExternalBrowserWithAd:(BCOVAd *)ad`
* The `BCOVPUIPlayerView` class has the following changes:
  * The `playbackController` property has been changed from `readonly` to `readwrite`. You can assign a new playbackController to the `BCOVPUIPlayerView` at any time to associate the playbackController's view with the `BCOVPUIPlayerView`.
  * `controlsContainerView` is a new `UIView` property that contains all of the controls subviews (both static and fading).
  * The `controlsView` property is now `strong` instead of `weak`.
  * `adControlsView` is a new property of type `BCOVPUIAdControlView`. This is a `UIView` subclass and does not currently expose any new properties or methods.
* The `BCOVPUIBasicControlView` class has a new `advertisingMode` property.
  *  When set to `YES`, controls are set to their advertising mode.
  This is done automatically when OnceUX or FreeWheel ads begin playing.
* Four new tags have been added to the `BCOVPUIViewTag` enumeration:
  * `BCOVPUIViewTagButtonAdPodCountdown`
  * `BCOVPUIViewTagButtonLearnMore`
  * `BCOVPUIViewTagButtonSkipAdCountdown`
  * `BCOVPUIViewTagViewButtonSkip`

  These tags can be used to locate new buttons related to ad controls within the view hierarchy.  
* The `BCOVPUISlider` class has a new `trackHeight` property that can be used to change the height of the scrubbing slider.
* The `BCOVPUISlider`'s `bufferProgressTintColor` property no longer has a `copy` attribute.
* The `BCOVPUISlider` class has new properties:
  * `advertisingMinimumTrackTintColor`
  * `advertisingMaximumTrackTintColor`
  
  These properties allow you to change the track tint colors that are used while in advertising mode.
* The `BCOVPUISlider` class has a new `markerTickColor` property that lets you set the color of generic markers on the slider.
* The `BCOVPUISlider` class has a new `duration` property that lets you set the length of the video, in seconds, represented by the range of the slider. This is used for positioning markers.
* The `BCOVPUISlider` class has new methods for managing markers on the slider track. Ad markers are added automatically, but you can add your own markers at any position.
  * `- (void)addMarkerAt:(double)position duration:(double)duration isAd:(BOOL)isAd image:(UIImage *)image`
  * `- (void)removeMarkerAtPosition:(double)position`
  * `- (void)removeAllMarkers`
  * `- (void)removeGenericMarkers`
  * `- (void)removeAdMarkers`

* `BCOVPUISlider`'s `setBufferProgress:animated:` method has been removed. You can set the buffer progress using the `bufferProgress` property directly.

* In the `BCOVPUISlider` class, `setContentTrackImage:forState:` and `setBufferTrackImage:forState:` have been replaced by `setCustomMinimumTrackImage:forState:` and `setCustomMaximumTrackImage:forState:`. You can no longer set an image for the progress area, but you can still set a tint.


### Deprecations
* In `BCOVPlayerSDKManager.h`, the method `-[BCOVPlayerSDKManager defaultControlsViewStrategy]` has been deprecated. Use the integrated PlayerUI controls instead. See the README file for full details.



# 5.0.7
### Additions and Improvements
* Fixed an issue where live streaming assets could not be retrieved or played through the Playback Service.

# 5.0.6
### Additions and Improvements
* Internal support for the FairPlay plugin for Brightcove Player SDK for iOS. Please note that if you are using version 1.0.3 of the FairPlay plugin for Brightcove Player SDK for iOS, you must use version 5.0.6 or later of the Brightcove Player SDK.

# 5.0.5
### Additions and Improvements
* Introduced convenience methods for accessing optional soundtracks, subtitles and closed captions from the AVPlayerItem of the current `BCOVPlaybackSession`. Apple API documentation refers to soundtracks as
audible media options, while subtitles and closed captions are referred to as legible media options.


  `-[BCOVPlaybackSession audibleMediaSelectionGroup]`,  
  `-[BCOVPlaybackSession  selectedAudibleMediaOption]`,  
  `-[BCOVPlaybackSession legibleMediaSelectionGroup]`,  
  `-[BCOVPlaybackSession  selectedLegibleMediaOption]`,  
  `-[BCOVPlaybackSession selectAudibleMediaOptionAutomatically]`,  
  `-[BCOVPlaybackSession selectLegibleMediaOptionAutomatically]`,  
  `-[BCOVPlaybackSession displayNameFromAudibleMediaSelectionOption:]`, and  
  `-[BCOVPlaybackSession displayNameFromLegibleMediaSelectionOption:]`.

* DASH sources are ignored.

# 5.0.4
### Additions and Improvements
* When a OnceUX or FairPlay-encoded stream stalls due to network slowdowns or interruptions, it can now be restarted using ` [BCOVPlaybackController resumeVideoAtTime:withAutoPlay:]`. Previously, only streams without OnceUX or FairPlay could be restarted.
* New lifecycle events are available for detecting the various states of the playback buffer (see `BCOVPlaybackSession.h` for details on each event): `kBCOVPlaybackSessionLifecycleEventPlaybackStalled`, `kBCOVPlaybackSessionLifecycleEventPlaybackRecovered`,  `kBCOVPlaybackSessionLifecycleEventPlaybackBufferEmpty`, and `kBCOVPlaybackSessionLifecycleEventPlaybackLikelyToKeepUp`.  



# 5.0.3
### Additions and Improvements
* Added support for using Picture in Picture and background audio at the same time by setting the new `pictureInPictureActive` property of the `BCOVPlaybackController` to `YES`. Please see README.md for usage details.
* When the `BCOVPlaybackController` delivers a new `BCOVPlaybackSession` for a video, it calls the delegate method `-[BCOVPlaybackControllerDelegate playbackController:didAdvanceToPlaybackSession:]` method as usual. Now, however, the delegate method will not be called until the `currentItem` on the `AVPlayer` inside the `BCOVPlaybackSession` has been loaded. Previously the delegate method was called immediately while the `AVPlayer` was still loading the `AVPlayerItem`, and thus `currentItem` could still be `nil`. This makes it easier to work with the `AVPlayer` when each session is delivered.
* Internal improvements.


# 5.0.2
### Additions and Improvements
* Reformatted the framework's short version string to comply with App Store submission requirements.

# 5.0.1
### Additions and Improvements
* Playing video in the background is supported by setting the new `allowsBackgroundAudioPlayback` property of the `BCOVPlaybackController` to `YES`. Please see README.md for usage details. 
* Internal improvements.

# 5.0.0
### Breaking Changes
* Calls to `[AVPlayer play]`, `[AVPlayer pause]`, and `[AVPlayer seekToTime:]` must be changed to call the corresponding method on the `BCOVPlaybackController`. Failure to do so will cause undefined behavior.
* The static library distributable has been removed. If installed manually (not CocoaPods), you will need to remove libBCOVPlayerSDK.a and its headers from the Header Search Path. Please see README.md for new install options (including a static library framework).
* Header `BCOVPlayerSDK.h` has been removed. Please see README.md for new import options.

### Additions and Improvements
* tvOS support (including analytics). 
* Bitcode support.
* The SDK is now distributed as a static or dynamic framework.
* `BCOVPlaybackController` now offers play, pause, and seek methods.
* Internal improvements.

# 4.4.3
* Introduce `kBCOVPlaybackSessionLifecycleEventWillPauseForAd` event to be send on the lifecycle delegate by ad plugins.

# 4.4.2
### Additions and Improvements
* Fixed an issue where calling `-[BCOVPlaybackController setVideos:nil]` didn't clear out the player correctly.
* Fixed a crash in `BCOVAnalyticsSession`.
* Updated internal network calls to use NSURLSession instead of NSURLConnection.
* `BCOVPlaybackService` now allows you to override the NSURLSession used for requests, by setting the `sharedURLSession` property.

# 4.4.1
### Additions and Improvements
* Added `-[BCOVPlaybackService findPlaylistWithPlaylistID:completion:]` and `-[BCOVPlaybackService findPlaylistWithReferenceID:completion:]`.
* Added `+[BCOVBasicSourceSelectionPolicy sourceSelectionHLSWithScheme:]` to prefer HTTPs sources. Please see README.md for more information on HTTPs and source selection.

# 4.4.0
### Breaking Changes
* Player is now paused when entering the background and therefore no longer resumes automatically when entering the foreground. This was added to work around an AVPlayer play state corruption when becoming active. If you would like to regain the original functionality, you will need to call play on the player when entering the foreground.

### Additions and Improvements
* Added `-[BCOVPlaybackControllerAdsDelegate playbackController:didPauseAd:]` and `-[BCOVPlaybackControllerAdsDelegate playbackController:didResumeAd:]` to be implemented by ad session providers.
* Updated to Analytics API v2, including quality of service metrics.
* Updated internal ReactiveCocoa version from 2.3.1 to 2.5.
* Internal improvements to support BCOVPlayerUI.

# 4.3.5
### Additions and Improvements
* Fixes memory leaks introduced by v4.3.4.

# 4.3.4
### Additions and Improvements
* Added `- [BCOVPlaybackController resumeVideoAtTime:withAutoPlay:`. This API can be used to re-initialize the AVPlayer in case of a network disruption. Progress and lifecycle events will be suppressed during this action.  Lifecycle events `kBCOVPlaybackSessionLifecycleEventResumeBegin`, `kBCOVPlaybackSessionLifecycleEventResumeComplete`, and `kBCOVPlaybackSessionLifecycleEventResumeFail` were added to provide updates on this action.
* Added `kBCOVPlaybackSessionLifecycleEventFailedToPlayToEndTime`. This event will fire when the AVPlayer has given up trying to play content. This even can be used in conjunction with `- [BCOVPlaybackController resumeVideoAtTime:withAutoPlay:` to re-initialize the player once network conditions have improved.

# 4.3.3
### Breaking Changes
* Preloading of videos is now disabled by default. If you wish to turn preloading back on, please consult the README.md for more information about `BCOVBasicSessionLoadingPolicy`.

### Additions and Improvements
* Added new APIs for enabling preloading of videos called `BCOVBasicSessionLoadingPolicy`. Please see the README.md for more information.
* Fixed a bug in the default controls that could prevent seeks to the end of the video from completing.

# 4.3.2
### Additions and Improvements
* Added Playback Service classes: `BCOVPlaybackService` and `BCOVPlaybackServiceRequestFactory`. These APIs provide an alternative way to retrieve Brightcove video assets via the Brightcove CMS API with more rich meta information such as text tracks.

# 4.3.1
### Additions and Improvements
* The seek bar on the default controls is now disabled until the AVPlayer is capable of seeking.

# 4.3.0
### Additions and Improvements
* Added `BCOVAdvertising` APIs. These APIs introduce the concept of Ads to our core SDK. Playback controller delegate and session consumer apis have also been added to provide ad information. In the future, our advertising plugins will be updated to provide ad events through these apis.  For more information, please see the README.md.
* `BCOVPlaybackSession` protocol now includes a providerExtention property. In the future, some of our plugins will be updated to provide plugin specific functionality through this property.
* The default controls now include a closed caption button for testing.
* Internal bug fixes.

# 4.2.3
### Additions and Improvements
* Switch analytics to https.

# 4.2.2
### Additions and Improvements
* Fixes a bug where the default controls playhead label will show a the incorrect playhead at the end of a video when running on device.
* Fixes a bug where the default controls slider isn't reset to 0 after calling advanceToNext or using AutoAdvance.

# 4.2.1
### Breaking Changes
* iOS 6 is still deprecated in this release. We have not removed support yet.  iOS 6.x currently accounts for ~2% of global SDK traffic.
* This release has been built with Xcode 6. In Xcode 6, Apple removed armv7s from the list of standard architectures. This release no longer includes an armv7s architecture slice.
* Use of `BCOVDelegatingSessionConsumer` and `BCOVDelegatingSessionConsumerDelegate` has been deprecated. Delegate methods equivilent to those provided by `BCOVDelegatingSessionConsumerDelegate` have been added to the `BCOVPlaybackSessionConsumer` protocol. Objects should now implement `BCOVPlaybackSessionConsumer` protocol and its methods.

| Deprecated Method (BCOVDelegatingSessionConsumerDelegate)           | Replaced By (BCOVPlaybackSessionConsumer)          |
| ------------------------------------------------------------------- | -------------------------------------------------- |
| `playbackConsumer:didAdvanceToPlaybackSession:`                     | `didAdvanceToPlaybackSession:`                     |
| `playbackConsumer:playbackSession:didChangeDuration:`               | `playbackSession:didChangeDuration:`               |
| `playbackConsumer:playbackSession:didChangeExternalPlaybackActive:` | `playbackSession:didChangeExternalPlaybackActive:` |
| `playbackConsumer:playbackSession:didPassCuePoints:`                | `playbackSession:didPassCuePoints:`                |
| `playbackConsumer:playbackSession:didProgressTo:`                   | `playbackSession:didProgressTo:`                   |
| `playbackConsumer:playbackSession:didReceiveLifecycleEvent:`        | `playbackSession:didReceiveLifecycleEvent:`        |

* `[<BCOVPlaybackSessionConsumer> consumeSession:]` method has been deprecated.  Use `[<BCOVPlaybackSessionConsumer> didAdvanceToSession:]` instead.

### Additions and Improvements
* Fixed a bug that prevented plugins from cleaning up correctly.
* Fixed a bug where didProgressTo delegate methods weren't called after a seek if the player is paused.
* Performance and object allocation improvements.

# 4.2.0

### Breaking Changes
* iOS 6 is still deprecated in this release. We have not removed support yet.
* All deprecated symbols within the Player SDK for iOS have been removed from this release.
* Use of ReactiveCocoa in public APIs within the Player SDK for iOS has been removed from this release.
* If using Cocoapods, ReactiveCocoa will no longer be installed by including our library. Running `pod update` to update to 4.2 will remove it. If you wish to continue using ReactiveCocoa for your own use, you will need to declare ReactiveCocoa in your podfile.
* If you installed ReactiveCocoa manually in your project, it can be removed. To remove it, you will need to at least perform the following:
    * Remove any "Target Dependencies" on ReactiveCocoa.
    * Remove any ReactiveCocoa references from the "Header Search Paths".
    * Remove libReactiveCocoa-iOS.a from the "Link Binary With Libraries" phase.
    * Remove the ReactiveCocoa.xcodeproj from your project or workspace.

### Additions and Improvements
* Fixed a bug that could cause sessions to leak if a playback controller is deallocated immediately after calling `-setVideos:`.

# 4.1.9

### Additions and Improvements
* Internal bug fixes.

# 4.1.8

### Breaking Changes
* iOS 6 is deprecated in this release. Version 4.2 of the Brightcove Player SDK for iOS is not supported on versions of iOS below 7.1 .
* Use of ReactiveCocoa in public APIs within the Player SDK for iOS is deprecated in this release. Version 4.2 of the Brightcove Player SDK for iOS will not require clients to install any version of ReactiveCocoa, and properties or methods that return or expect RACSignal objects will be removed. See the header files for guidance on how to update deprecated functionality for compatibility with 4.2. The deprecations include the following:
  * `-[AVPlayer bcov_periodicTimeObserverSignalForInterval:]`
  * `-[AVPlayer bcov_periodicTimeObserverSignalForInterval:queue:]`
  * `-[BCOVCatalogService findPlaylistWithPlaylistID:parameters:]`
  * `-[BCOVCatalogService findPlaylistDictionaryWithPlaylistID:parameters:]`
  * `-[BCOVCatalogService findPlaylistWithReferenceID:parameters:]`
  * `-[BCOVCatalogService findPlaylistDictionaryWithReferenceID:parameters:]`
  * `-[BCOVCatalogService findVideoWithVideoID:parameters:]`
  * `-[BCOVCatalogService findVideoDictionaryWithVideoID:parameters:]`
  * `-[BCOVCatalogService findVideoWithReferenceID:parameters:]`
  * `-[BCOVCatalogService findVideoDictionaryWithReferenceID:parameters:]`
  * `-[BCOVCuePointProgressPolicy signalWithValue:]`
  * `-[BCOVPlaybackSession cuePoints]`
  * `-[BCOVPlaybackSession durationChanges]`
  * `-[BCOVPlaybackSession isExternalPlaybackActive]`
  * `-[BCOVPlaybackSession lifecycle]`
  * `-[BCOVPlaybackSession progress]`
* Duration changes reported by a BCOVPlaybackSession will no longer include the initial value of `kCMTimeNegativeInfinity`.
* A lifecycle event of type `kBCOVPlaybackSessionLifecycleEventProgress` will now be reported during a seek, even if the AVPlayer's rate is 0.0 (paused).

### Additions and Improvements
* Fixed a bug in which the AirPlay button could randomly appear in the default video playback controls.
* Added methods that return NSOperation objects to BCOVCatalogService. The operations replace similar (deprecated) RACSignal-returning methods.
* Fixed a bug that could cause repeated, immediate calls to `-[BCOVPlaybackController pause]` and `-[BCOVPlaybackController play]` to execute out of order.
* Return `instancetype` instead of `id` from methods that return instances of the current class type, in preparation for compatibility with Swift.
* Made refinements and enhancements to the information sent to Brightcove analytics, including the ability to programmatically specify the account ID, destination, and source properties to be included in all analytics reporting.
* Fixed an analytics bug that could prevent the sending of a video impression.
* Fixed an analytics bug in which video engagement was not being reported for live streams.
* Fixed an analytics bug in which video engagement could be reported when the seeking in reverse.
* Fixed an analytics bug in which one second of video engagement reporting could be dropped periodically.
* The underlying error is included in the event payload when a lifecycle event of type `kBCOVPlaybackSessionLifecycleEventFail` occurs.

# 4.1.7

### Breaking Changes
* The return type of `-[BCOVPlaylist count]` has been corrected to return a value of type `NSUInteger` (previously it returned a value of type `int`).

### Additions and Improvements
* Added an `arm-64` architecture slice to the static library, for applications that wish to target the 64-bit architecture.
* Introduced a new class, BCOVCuePointProgressPolicy. This class isn't used directly by the Brightcove Player SDK for iOS at this time, but may be used in plugins.
* Fixed a bug in the firing of cue point events of type `kBCOVCuePointPositionTypeAfter`.
* The SDK now correctly reports the `video_name` and `device_type` parameters to Brightcove Video Cloud Analytics.
* NSOperationQueues used internally within the SDK are now given more useful logical names, to help with debugging code that executes in the queue.
* Fixed a bug in which the `kBCOVPlaybackSessionLifecycleEventPlay` lifecycle event would fire multiple times in response to the AVPlayer/s `rate` being set to a nonzero value more than once.

# 4.1.6

### Breaking Changes
* We reversed one change introduced in 4.1.5: if no BCOVSource with a HLS or MP4 `deliveryMethod` is found in a given playback session's BCOVVideo, the default source selection policy will select the first of the video's sources. We made this reversal due to the number of customers who reported that their videos  failed to play (because none of the sources in those videos had the expected `deliveryMethod`). This means that, as of 4.1.6, if you are not using a custom source selection policy, the playback controller will *not* advance to the next video if it cannot find an HLS or MP4 source in the current video; it will attempt to use the first source regardless of its delivery method.

### Additions and Improvements
* Automatically advance to the next playback session if the current playback session has no video, or if its video has no sources.
* Fixed a bug in which a video with a single cue point could cause a crash.

# 4.1.5

### Breaking Changes
* This release introduces an improved default source selection policy, and a mechanism to override the default source selection. Prior to 4.1.5, the default policy would select the first source on each video, regardless of the source's `url` or `deliveryMethod` properties. In 4.1.5, the default policy now selects the first source whose `deliveryMethod` is `kBCOVSourceDeliveryHLS` ("HLS"). If no HLS source is found, its fallback behavior will select the first source whose `deliveryMethod` is `kBCOVSourceDeliveryMP4` ("MP4"). If no source with a `deliveryMethod` of "HLS" or "MP4" exists on the video, the playback controller will advance to the next playback session. Most videos retrieved via BCOVCatalogService will have the expected sources.
* UIViews are prohibited from being added as children of the playback controller's video view.

### Additions and Improvements
* Added the `-[BCOVPlayerSDKManager createPlaybackController]` convenience overload for when a view strategy isn't needed.
* Fixed a bug to ensure the elapsed time label on the default controls is reset when advancing to a new session.
* Fixed video engagement reporting for Brightcove Analytics.
* Fixed a bug that prevented listeners for BCOVCuePoints of type `kBCOVCuePointPositionTypeAfter` from firing when advancing to a new session.
* Fixed a harmless bug where BCOVPlayerSDKManager could redundantly register components.

# 4.1.4

### Breaking Changes
* When `-[BCOVPlaybackController setVideos:]` is called, the current playback session is removed. Previously, calling `-setVideos:` would add the new videos to the playback controller, but would not affect the current session.
* BCOVPlaybackFacade and BCOVPlaybackQueue protocols are deprecated in this release, as we have consolidated their functionality within the BCOVPlaybackController protocol. We apologize for any inconvenience this may cause, but the migration path to update code that uses these protocols is straightforward:
    1. There is no longer any reason to create a BCOVPlaybackQueue object. Remove code that calls `-[BCOVPlayerSDKManager createPlaybackQueue]` altogether, as it will no longer compile.
    1. Replace calls to `-[BCOVPlayerSDKManager createPlaybackFacadeWithFrame:]` with `-[BCOVPlayerSDKManager createPlaybackControllerWithViewStrategy:]`. You can pass `nil` to this method. Then you can set your frame directly on the returned playback controller's `view`.
    1. If you implemented BCOVPlaybackFacadeDelegate, modify your delegate to implement BCOVPlaybackControllerDelegate instead. Replace each delegate method with the corresponding method from the BCOVPlaybackControllerDelegate protocol. For example, `-playbackFacade:playbackSession:didProgressTo:` would become `-playbackController:playbackSession:didProgressTo:`. There is no need to change the behavior of your delegate methods, it is just a renaming.
    1. Remaining references to `id<BCOVPlaybackFacade>` can be changed to `id<BCOVPlaybackController>`. In other words, wherever you previously used a facade, you should now use a playback controller.
    1. Remove any calls to `BCOVPlaybackFacade.controlsEnabled`. This property will no longer have any effect. If you are still developing your app and do not yet have your own controls implemented, you can re-enable the default playback controls by passing `-[BCOVPlayerSDKManager defaultControlsViewStrategy]` when you create the playback controller, instead of passing a `nil` strategy.
* Methods that create BCOVPlaybackController objects with a frame have been deprecated. If you used `-[BCOVPlayerSDKManager createPlaybackControllerWithFrame:]` or `-[BCOVPlayerSDKManager createPlaybackControllerWithSessions:frame:]`, the migration path is also straightforward:
    1. Use `-[BCOVPlayerSDKManager createPlaybackControllerWithViewStrategy:]`. You can pass `nil` to this method. Then you can set your frame directly on the returned playback controller's `view`.
    1. That's it.
* `-[BCOVPlaybackController seekToTime:]` has been deprecated. It should be replaced with a call to `-[AVPlayer seekToTime:completionHandler:]` on the given playback session's AVPlayer object.

### Additions and Improvements
* This release introduces support for loading plugin components into the BCOVPlayerSDKManager. With this 4.1.4 release, we are simultaneously releasing our first plugins: BCOVIMA, a plugin that offers built-in integration with Interactive Media Ads, and BCOVWidevine, a plugin that allows you to use Widevine-encrypted content with the Player SDK for iOS.
* Playback controllers obtain their playback sessions from a BCOVPlaybackSessionProvider object. Session providers provide a mechanism for plugins to affect content playback by stepping into the session construction process. The Player SDK for iOS ships with a basic session provider (aptly named BCOVBasicSessionProvider), which provides the default playback functionality.
* Playback controllers send their playback sessions to a list of BCOVPlaybackSessionConsumer objects. Session consumers provide a mechanism for plugins to respond to playback events without affecting the app developer's ability to specify a BCOVPlaybackControllerDelegate.
* Playback sessions now send a "terminate" event on their lifecycle signal when the playback controller is finished with them. Clients can listen for this event to know when to discard a reference to a playback session. A playback session should not be used after it has terminated.
* App developers can specify a view strategy that specifies how the playback controller should construct its `view`. For further information, refer to the README.
* Apps no longer have to wait for a playback session to be advanced before calling `-[BCOVPlaybackController play]`. If this method is called before advancing to a playback session, playback will begin as soon as the first session is advanced to.
* Detection of cue points during video playback has been significantly optimized to pose less of a burden on CPU and battery.
* Methods to pause and resume ads have been added to BCOVPlaybackController. However, these are merely stubs when used without an advertising plugin that supports them.
* API documentation is generated from header comments, and is available in the `html/` directory of the Player SDK for iOS.
* Corrected the documentation of the behavior of the `-[BCOVPlaybackSession lifecycle]` signal. Previously, this signal was described as sending its entire history of events to each subscriber, when in fact it is a hot signal and sends only events that occur *after* subscription. Note that this does not represent a change in functionality, but rather a fix to incorrect documentation about that functionality.

# 4.0.3

### Breaking Changes
* `-[BCOVPlayerSDKManager newPlaybackQueue]` is an [invalid method name for code built with ARC][arcnotes]. In 4.0.3, we renamed that method to `-createPlaybackQueue`, and for consistency, we renamed the other methods in BCOVPlayerSDKManager that begin with the word `new`. The following table illustrates the changes:

|              Removed Method                 |                  Replaced By                   |
| --------------------------------------------| ---------------------------------------------- |
| `-newPlaybackQueue`                         | `-createPlaybackQueue`                         |
| `-newPlaybackFacadeWithFrame:`              | `-createPlaybackFacadeWithFrame:`              |
| `-newPlaybackControllerWithSessions:frame:` | `-createPlaybackControllerWithSessions:frame:` |

[arcnotes]: https://developer.apple.com/library/mac/releasenotes/ObjectiveC/RN-TransitioningToARC/Introduction/Introduction.html

### Additions and Improvements
* Fixes for memory leaks that could occur when destroying and recreating BCOVPlaybackFacade, BCOVPlaybackQueue, and BCOVPlaybackController instances.


# 4.0.2

### Breaking Changes
* BCOVPlaybackSession objects are released shortly after a new playback session is dequeued. Prior to 4.0.2, playback session objects would leak until the last session for any given collection of videos was dequeued (at which time the previous sessions would be released).
* Event signals on BCOVPlaybackSession objects send complete when a new playback session is dequeued.

### Additions and Improvements
* Fixed a bug in which cue point events could be sent (erroneously) for playback sessions that are no longer active.
* Corrections to reporting `video_engagement` metrics for Brightcove Analytics.
* Throttle the check for cue points down to only once per second, to avoid unnecessary calculations.
* Fixed a bug in which BCOVPlaybackFacadeDelegate event methods were called at inappropriate times, such as when new playback session were dequeued.
* Fixed a race condition that could occur if two threads concurrently attempted to access `-[BCOVPlaybackController view]`. (This race could result in creating two UIView objects.)
* Corrected the header documentation of the `-[AVPlayer+BCOVSignalSupport bcov_periodicTimeObserverSignalForInterval:]` and `-[AVPlayer+BCOVSignalSupport bcov_periodicTimeObserverSignalForInterval:queue:]` category methods, which misleadingly stated that the signals returned by these methods would complete if the AVPlayer deallocates. The implementation of `-[AVPlayer addPeriodicTimeObserverForInterval:queue:usingBlock:]`, used internally by these signals, prevents its AVPlayer from being released while these signals have active subscriptions. Furthermore, these signals never send complete; subscriptions to these signals live until explicitly disposed.


# 4.0.1

### Breaking Changes
* `Brightcove-Player-SDK.podspec` now uses the `~>` operator to declare its dependency on the latest `2.1.x` version of ReactiveCocoa. This means that running `pod install` or `pod update` will install the latest version of ReactiveCocoa up to, but not including, `2.2.0`.
* `NaN` values received by `-[BCOVPlaybackFacadeDelegate playbackFacade:playbackSession:didChangeDuration:]` due to an unknown duration are now suppressed. The `NaN` values were sent for `kCMTimeIndefinite` durations, which is the duration of AVPlayerItems prior to the `kBCOVPlaybackSessionLifecycleEventReady` lifecycle event. The `-[BCOVPlaybackSession durationChanges]` signal continues to report all durations, including the initial `kCMTimeIndefinite`, for clients that require this level of detail.

### Additions and Improvements
* Fixed a bug that could prevent AVPlayer objects from being released.
* Fixed a bug so that `-[BCOVPlaybackFacade setControlsEnabled:]` performs the expected behavior of enabling or disabling the default controls.
