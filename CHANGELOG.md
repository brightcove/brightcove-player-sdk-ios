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

* The minimum iOS Deployment Target for all Brightcove Native Player for iOS frameworks is now iOS 9.0. Details are available [here](https://support.brightcove.com/announcement-ios-sdk-deprecating-support-ios-9-and-eol-support-ios-8).

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

* The `BCOVCatalogService`, also referred to as the Brightcove Media API, has reached end-of-life status and been removed from the Brightcove Native Player SDK. If your app uses the BCOVCatalogService, you must update it to use the [BCOVPlaybackService](https://brightcovelearning.github.io/Brightcove-API-References/ios-sdk/index.html#PlaybackService).
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

* This and future releases of Brightcove Native Player for iOS will include all software components, all having the same version number. When building your app with Brightcove Native Player for iOS components, the component version numbers must always match. As an example, when using version 6.0.1 of the FreeWheel Plugin for Brightcove Player SDK for iOS, you must also use version 6.0.1 of the core Brightcove Player SDK for iOS. Each component will continue to be available from an individual GitHub repositories.
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
* Please see our app developer's guide for full details: [iOS App Developer's Guide to Video Downloading and Offline Playback with FairPlay](OfflinePlayback.md)
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
