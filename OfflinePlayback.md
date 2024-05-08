
# iOS App Developer's Guide to Video Downloading and Offline Playback with HLS in the Brightcove Player SDK for iOS, version 6.13.1.2627


The Brightcove Native Player SDK allows you to download and play back HLS videos, including those protected with FairPlay encryption. Downloaded videos can be played back with or without a network connection.

## Requirements

- Brightcove Native Player SDK v6.6.2+
- Brightcove Account with Dynamic Delivery

iOS does not allow FairPlay-protected video to display in a simulator, nor does it allow video downloads to a simulator, so it's important to develop on an actual device.

## Basic Concepts

When you request a video download, you will be given a token that is used to keep track of both the active download and the offline video in device storage. The token is of type `BCOVOfflineVideoToken`, and is referred to as a token rather than an object because it can be persisted, and is valid across instances of the app.

Videos are stored in the app's Library directory, in a subdirectory determined by iOS. Apple specifically requires that these videos stay in this location. Be aware that videos can be deleted by iOS under low-storage conditions, and users can delete downloaded videos directly from the iOS Settings app. Also, videos and their associated metadata are not backed up to iCloud.

A FairPlay license can be requested either when the video download is requested, or preloaded ahead of time with a separate method call. You can specify either a purchase license, or a rental license with an associated rental duration. The license rental duration begins from the moment the request is made with the license server.

When a download begins, you can receive notification of progress and completion by setting your own class as a delegate of the `BCOVOfflineVideoManager` singleton object. Be sure that your object inherits the `BCOVOfflineVideoManagerDelegate` protocol.

By default, downloads are only allowed over WiFi connections, but this can be changed to enable downloads over cellular as well. Similarly, during playback, iOS may request some additional resources (like subtitle tracks if they were not downloaded). This will only happen on WiFi, but can be changed as well.

## Initialization

The `BCOVOfflineVideoManager` is a singleton class that manages all video downloads. Before using any `BCOVOfflineVideoManager` methods, you should call

```
[BCOVOfflineVideoManager initializeOfflineVideoManagerWithDelegate:self
							options:@{ kBCOVOfflineVideoManagerAllowsCellularDownloadKey : @(YES) }];
```

The options dictionary may be nil, but this example shows how to allow downloads over cellular networks.

After initialization, you can refer to the Offline Video Manager with the `BCOVOfflineVideoManager.sharedManager` property.

As part of setup, you also need to create and assign an authorization proxy to handle the details of FairPlay key exchange. You can use the supplied Brightcove FairPlay proxy to do this work:

```
// Publisher/application IDs not required for Dynamic Delivery
self.authProxy = [[BCOVFPSBrightcoveAuthProxy alloc] initWithPublisherId:nil
                                                           applicationId:nil];
    
BCOVOfflineVideoManager.sharedManager.authProxy = self.authProxy;
```

If you want to change the `kBCOVOfflineVideoManagerAllowsCellularDownloadKey` value later on in your app to allow or disallow cellular access, you can call `-[BCOVOfflineVideoManager initializeOfflineVideoManagerWithDelegate:options:]` again with a new options dictionary and/or delegate.

**NOTE: Changing the value of `kBCOVOfflineVideoManagerAllowsCellularDownloadKey` will not have an effect on active downloads, only downloads initialized after the value has been changed.**

## Check Whether a Video Can Be Downloaded

In your user interface, you should indicate if a video is eligible for download. To do this,  examine the `BCOVVideo.canBeDownloaded` property. This Boolean property checks the status of the video's `offline_enabled` flag that is settable through the [Brightcove CMS API](https://sdks.support.brightcove.com/features/offline-playback-native-player-sdks.html#Download_management).

## Download a Video

There are two approaches to download a video. The first utilizes an array of `AVMediaSelection` objects and the second utilizes `AVAssetDownloadConfiguration` which was introduced in iOS 15.

### When downloading with AVMediaSelections

```
[BCOVOfflineVideoManager.sharedManager requestVideoDownload:video
                                            mediaSelections:nil
                                                 parameters:parameters
                                                 completion:^(BCOVOfflineVideoToken offlineVideoToken,
                                                              NSError *error) {

    // store offlineVideoToken or handle error

}];
```

### When downloading with AVAssetDownloadConfiguration

```
[BCOVOfflineVideoManager.sharedManager requestVideoDownload:video
                                      downloadConfiguration:downloadConfiguration
                                                 parameters:parameters
                                                 completion:^(BCOVOfflineVideoToken offlineVideoToken, NSError *error) {

    // store offlineVideoToken or handle error

}];
```

### Configuring the parameters for download

The video parameter is a normal `BCOVVideo` object that you get by querying the `BCOVPlaybackService`. You should make sure that its `canBeDownloaded` property is `YES` before downloading.

The parameters argument is an `NSDictionary` in which you specify the terms for the offline FairPlay license, preferred bitrate, and other values. 

The following are the valid parameter keys that you may use when requesting a video download:

* kBCOVFairPlayLicensePlayDurationKey
* kBCOVFairPlayLicensePurchaseKey
* kBCOVFairPlayLicenseRentalDurationKey
* kBCOVOfflineVideoManagerRequestedBitrateKey

Here are some examples of video download parameters for common license-types:

```
// A purchased video download
// In this case only `kBCOVFairPlayLicensePurchaseKey` is required
// but you may also specify the bitrate you'd like to download
parameters = @{
    kBCOVFairPlayLicensePurchaseKey: @(YES),
    // kBCOVOfflineVideoManagerRequestedBitrateKey: @(1000000)
};
```
```
// A rented video valid for 30 days
// You could also specify the bitrate as in the purchased video example
parameters = @{
    // 30 days in seconds
    kBCOVFairPlayLicenseRentalDurationKey: @(60 * 60 * 24 * 30)
};
```
```
// A rented video valid for 30 days or 24 hours after playback begins
// This is known as "Dual Expiry" or a "Rental Profile"
// You could also specify the bitrate as in the purchased video example
parameters = @{
    // 30 days in seconds
    kBCOVFairPlayLicenseRentalDurationKey: @(60 * 60 * 24 * 30),
    // 24 hours in seconds
    kBCOVFairPlayLicensePlayDurationKey: @(60 * 60 * 24)
};
```

**NOTE: If a license expires during playback of a video the video will not stop, but attempting to reload the video will result in a "license expired" error.**

The completion handler is where you asynchronously receive the offline video token or the error. You can store a reference to this offline video token if the error is nil. You will receive notficiation of progress and completion thorugh delegate methods.

## Preload a FairPlay license

If you plan to download multiple FairPlay-protected videos, it's a good idea to preload all the FairPlay licenses beforehand, because FairPlay license exchange cannot happen while the app is in the background. Preload a FairPlay license with a similar call:

```
[BCOVOfflineVideoManager.sharedManager preloadFairPlayLicense:video
                                                   parameters:parameters
                                                   completion:^(BCOVOfflineVideoToken offlineVideoToken,
                                                                NSError *error) {

    // store offlineVideoToken or handle error

}];
```
An offline video token will be established for the download at this point. After the license has been acquired, you can then request the video download without any parameters:

### When downloading with AVMediaSelections

```
[BCOVOfflineVideoManager.sharedManager requestVideoDownload:video
                                            mediaSelections:nil
                                                 parameters:nil
                                                 completion:^(BCOVOfflineVideoToken offlineVideoToken,
                                                              NSError *error) {

    // returns the same offline video token here

}];
```

### When downloading with AVAssetDownloadConfiguration

```
[BCOVOfflineVideoManager.sharedManager requestVideoDownload:video
                                      downloadConfiguration:downloadConfiguration
                                                 parameters:nil
                                                 completion:^(BCOVOfflineVideoToken offlineVideoToken, NSError *error) {

    // returns the same offline video token here

}];
```

At this point, the download will continue even if the user sends the app to the background. Keep in mind, however, that a FairPlay license rental duration begins from the time when the license is requested.

## Downloading Secondary Tracks

Subtitle, caption and audio tracks for a language are known collectively as a Media Selection and are represented by Apple's `AVMediaSelection` class. A video can have multiple media selections, for example, English, French and Spanish. The language settings of the device determine the *preferred* media selection, for example, English.

Media Selection are properties of the `AVAsset` class. `BCOVOfflineVideoManager` provides the utility method `-[BCOVOfflineVideoManager urlAssetForVideo:error:]` to help you assemble `AVMediaSelection` objects of interest. Refer to the "*Finding Media Selections*" methods of `AVAsset`.

### When downloading with AVMediaSelections

Internally, the SDK manages the download of a video and its secondary tracks using a single `AVAggregateAssetDownloadTask`.

Downloading for offline viewing involves these basic steps:

1. Choose the media selections to be downloaded.
1. Create an `NSArray<AVMediaSelection *>` of your media selections, and pass it to `-[BCOVOfflineVideoManager requestVideoDownload:mediaSelections:parameters:completion:]` or pass `nil` to automatically download the *preferred* `AVMediaSelection` objects.
1. Track download progress using the `offlineVideoToken:aggregateDownloadTask:didProgressTo:forMediaSelection:` of the `BCOVOfflineVideoManagerDelegate` protocol. Note that when downloading additional media selections, progress callbacks are made for each downloaded item individually, with each ranging in progress from 0% to 100%.

The [Discover how to download and play HLS offline](https://developer.apple.com/videos/play/wwdc2020/10655) session from **WWDC 2020** covers reccomended methods of gathering the media selections (4:55) you'd like to download in addition to handling download progress for an `AVAggregateAssetDownloadTask` (5:22).

### When downloading with AVAssetDownloadConfiguration

Internally, the SDK manages the download of a video and its secondary tracks using a single `AVAssetDownloadTask`.

Downloading for offline viewing involves these basic steps:

1. Choose the media selections to be downloaded.
1. Create an `NSArray<AVMediaSelection *>` of your media selections, and set as the value for `primaryContentConfiguration.mediaSelections` on your `AVAssetDownloadConfiguration`
1. You can use the `offlineVideoToken:assetDownloadTask:willDownloadVariants:` delegate method to verify which variants will be downloaded.
1. Track download progress using the `offlineVideoToken:assetDownloadTask:didProgressTo:` of the `BCOVOfflineVideoManagerDelegate` protocol.

The [Explore HLS variants in AVFoundation](https://developer.apple.com/videos/play/wwdc2021/10143/) session from **WWDC 2021** covers selecting primary and auxilary media selections on an `AVAssetDownloadConfiguration`.

## Displaying Sideband Subtitles

The PlayerUI built-in controls will automatically detect and present your available Sideband Subtitles in the same, familiar closed caption control for you, so don't need to do anything if you are using a standard `BCOVPUIPlayerView`.

If you are creating your own user interface, you should check the downloaded `BCOVVideo` for a `kBCOVOfflineVideoUsesSidebandSubtitleKey` property. If set to YES, you should then get the available subtitle languages from the `kBCOVOfflineVideoManagerSubtitleLanguagesKey`. This is an array of standard language codes that can be converted to display format to the end user.

To present the subtitles for a particular language, set the `kBCOVOfflineVideoManagerPlaybackSubtitleLanguageKey` in the active `BCOVPlaybackController`'s options dictionary with your selected language as the value.

If the `kBCOVOfflineVideoUsesSidebandSubtitleKey` is missing or NO, you can assume that the video is using standard iOS subtitles, and you can set your media selection on the `AVPlayer` as always.

## Specifying a Variant Bitrate

### When downloading with AVMediaSelections

If you do not specify a bitrate for your download, you will get the lowest rendition that has a video track. To pick a specific variant based on the bitrate or resolution, you can call:

```
[BCOVOfflineVideoManager.sharedManager
    variantAttributesDictionariesForVideo:video
    completion:(void (^)(NSArray<NSDictionary *> *variantAttributesDictionariesArray, NSError *error))completionHandler {
   
       // Check attributes of each variant
    
}];
```
"Variants" are video renditions with different bitrates and/or video dimensions.

The `variantAttributesDictionariesArray` array will contain an array of dictionaries, one for each variant in the HLS manifest. Each dictionary contains a variety of attributes, the most important of which are the "BANDWIDTH" and "RESOLUTION values. You can use these to determine the best variant for your application.

Once you have chosen the best variant, you can use its "BANDWIDTH" value as your preferred bitrate.

If all you need are the available bitrates for a video, you can call:

```
[BCOVOfflineVideoManager.sharedManager
    variantBitratesForVideo:video
    completion:(void (^)(NSArray<NSNumber *> *bitrates, NSError *error))completionHandler {
   
       // Check list of available bitrates
    
}];
```
Then you can pass your preferred bitrate as the value for the `kBCOVOfflineVideoManagerRequestedBitrateKey` key.


```
long int preferredBitrate = 1996500; // value in bits per second
parameters = @{
	// Purchase license
	kBCOVFairPlayLicensePurchaseKey: @(YES),
	
	// Specify variant using the bitrate
	kBCOVOfflineVideoManagerRequestedBitrateKey: @( preferredBitrate )
};

[BCOVOfflineVideoManager.sharedManager requestVideoDownload:video
                                            mediaSelections:mediaSelections
                                                 parameters:parameters
                                                 completion:^(BCOVOfflineVideoToken offlineVideoToken,
                                                              NSError *error) {

    // store offlineVideoToken or handle error

}];
```

### When downloading with AVAssetDownloadConfiguration

You can select a specific `AVAssetVariant` or can use an `NSPredicate` to pick an appropriate variant.

```
// Selecting a specific variant
AVAssetVariantQualifier *desiredVariantQualifier = [AVAssetVariantQualifier assetVariantQualifierWithVariant:desiredVariant];
AVAssetDownloadConfiguration *downloadConfiguration = [AVAssetDownloadConfiguration downloadConfigurationWithAsset:avURLAsset title:video.properties[kBCOVVideoPropertyKeyName]];
downloadConfiguration.primaryContentConfiguration.variantQualifiers = @[desiredVariantQualifier];
```

```
// Using an NSPredicate
NSPredicate *peakBitRatePredicate = [NSPredicate predicateWithFormat:@"peakBitRate > 1268300"];
AVAssetVariantQualifier *predicateQualifier = [AVAssetVariantQualifier assetVariantQualifierWithPredicate:peakBitRatePredicate];
downloadConfiguration.primaryContentConfiguration.variantQualifiers = @[predicateQualifier];
```

## Check Download Size

Before a download is requested, it's a good idea to make sure there is enough space in device storage for the download.

The method `[BCOVOfflineVideoManager estimateDownloadSize:options:completion:]` can be used to get an estimate of how much space, in megabytes, the download will require. If there is not enough space for a download, it will result in an error.

iOS needs a cushion to run properly, so you should not allow downloads to fill up all the free space on the device. If you use up all the free storage, the system may start deleting cached data in other apps, and may eventually remove a downloaded video from your own app.

The Brightcove SDK does not enforce any free space requirements, but we suggest making sure you leave at least 1 GB free to prevent storage cleanup policies from taking effect.

## Get All Downloads

The `BCOVOfflineVideoManager` has an `offlineVideoTokens` property that returns an array of all the current offline video tokens. This includes tokens for videos that are currently preloaded or downloading, and tokens for videos that are already in storage and have finished downloading. You can examine this property at any time to present to the user a list of videos that are downloading, or a list of videos that have been downloaded and are available for offline playback.

## Get the Status of Downloads

For any given offline video token, you can determine its status by calling `[BCOVOfflineVideoManager offlineVideoStatusForToken:]`. This method returns a `BCOVOfflineVideoStatus` object that contains various bits of useful data about the download:

- Download state (requested, started, suspended, completed, canceled, or failed)
- License request time
- Start time
- End time (if finished)
- Progress (percentage)
- Associated `AVAssetDownloadTask` (if the download is still in progress)

This call is essential for providing feedback in your user interface about what each download is doing.

To get information about the status of all offline videos at once, use the `BCOVOfflineVideoManager.offlineVideoStatus` property. This returns an array of `BCOVOfflineVideoStatus` objects, one for each offline video.

## Determining FairPlay License Expiration

You can find out when the FairPlay license for an offline video expires by querying the Offline Video Manager as follows:

```
NSDate *licenseExpirationDate = [BCOVOfflineVideoManager.sharedManager fairPlayLicenseExpiration:offlineVideoToken];
```

The method returns the expiration of the FairPlay license as an `NSDate` object. If the FairPlay license is a purchase license, or the video is not encrypted with FairPlay, `NSDate.distantFuture` is returned. If the FairPlay license is missing, `nil` is returned.

## Get Metadata from Offline Video Tokens

`BCOVVideo` objects contain a host of metadata stored in a properties dictionary. When working with offline video tokens, you can access this associated metadata by first converting the token to a `BCOVVideo` object, and then accessing the properties directly.

This example shows how to get the file path to the offline poster image associated with the downloaded video token:

```
    BCOVVideo *video = [BCOVOfflineVideoManager.sharedManager videoObjectFromOfflineVideoToken:offlineVideoToken];
    NSString *posterPathString = video.properties[kBCOVOfflineVideoPosterFilePathPropertyKey];
    UIImage *posterImage = [UIImage imageWithContentsOfFile:posterPathString];
```

Here are some of the more useful dictionary keys for the offline-specific properties from the `BCOVVideo`'s properties dictionary:

**`kBCOVOfflineVideoTokenPropertyKey`**

Offline video token for this video.

**`kBCOVOfflineVideoLicenseRequestTimePropertyKey`**

Time that the FairPlay license was requested.

This time is stored as an NSNumber representing the of seconds since the standard `NSDate` reference date.
You can generate an `NSDate` object from this number with: `-[NSDate dateWithTimeIntervalSinceReferenceDate:]`.


**`kBCOVOfflineVideoDownloadStartTimePropertyKey`**

Time that the offline video download was requested.

This time is stored as an NSNumber representing the number of seconds since the standard `NSDate` reference date.
This value is useful when sorting by the time each download process started.
You can generate an `NSDate` object from this number with: `-[NSDate dateWithTimeIntervalSinceReferenceDate:]`.

**`kBCOVOfflineVideoDownloadEndTimePropertyKey`**

Time that the offline video download completed (whether normally, cancelled, or failed).

This time is stored as an NSNumber representing the number of seconds since the standard `NSDate` reference date. This value is useful when sorting by the time each download completes. This value is not set until the download completes.
You can generate an `NSDate` object from this number with: `-[NSDate dateWithTimeIntervalSinceReferenceDate:]`.

**`kBCOVOfflineVideoLicenseAbsoluteExpirationTimePropertyKey`**

Time that the offline video download will expire if using a FairPlay license. This value is only stored with version 6.2.2 and later of the iOS Native Player SDK.

This time is stored as an NSNumber representing the number of seconds since the standard `NSDate` reference date. This value is set every time a FairPlay license is acquired.
You can generate an `NSDate` object from this number with: `-[NSDate dateWithTimeIntervalSinceReferenceDate:]`.

**`kBCOVOfflineVideoOnlineSourceURLPropertyKey`**

URL of the original online video that was downloaded to storage for this `BCOVVideo` object, as an `NSString`.

Note that this URL may have expired, so this is primarily useful as a reference.

**`kBCOVOfflineVideoThumbnailNamePropertyKey`**

Name of the downloaded thumbnail image file in device storage, as an `NSString`.

This name is used to generate the full path of the file at runtime.

**`kBCOVOfflineVideoThumbnailFilePathPropertyKey`**

Full path to the downloaded thumbnail image file in device storage, as an `NSString`.

Even if the path is present, the image file may not be present. Due to app sandboxing, this path may change when the app is launched, so you should not store the full path.

**`kBCOVOfflineVideoPosterNamePropertyKey`**

Name of the downloaded poster image file in device storage, as an `NSString`.

This name is used to generate the full path of the file at runtime.

**`kBCOVOfflineVideoPosterFilePathPropertyKey`**

Full path to the downloaded poster image file in device storage, as an `NSString`.

Even if the path is present, the image file may not be present. Due to app sandboxing, this path may change when the app is launched, so you should not store the full path.

**`kBCOVOfflineVideoRelativeFilePathPropertyKey`**

Relative file path of the downloaded FairPlay video bundle in device storage, as an `NSString`.

This name is used to generate the full path of the file at runtime.

**`kBCOVOfflineVideoFilePathPropertyKey`**

Full path to the downloaded FairPlay video bundle in device storage, as an `NSString`.

Due to app sandboxing, this path may change when the app is launched, so you should not store the full path.

**`kBCOVOfflineVideoUsesSidebandSubtitleKey`**

Boolean value, stored as an NSNumber, that is set to YES when this video is using Sideband Subtitles.
When using Sideband Subtitles, you can get the array of downloaded languages from the `kBCOVOfflineVideoManagerSubtitleLanguagesKey` property.
When playing back the video, you can select the subtitle to present by setting it as the value for the `kBCOVOfflineVideoManagerPlaybackSubtitleLanguageKey` key in the `BCOVPlaybackController`'s options property.

## Play Offline Videos

To play an offline video, convert the offline video token to a `BCOVVideo` object, and then play the video as you would any normal online video object. Since videos can be deleted without warning by iOS, or the user, it's a good idea to check that the video is playable.

Here's how you might create the playback controller in your setup code for playing FairPlay videos:

```
BCOVPlayerSDKManager *sdkManager = [BCOVPlayerSDKManager sharedManager];

// Create standard authorization proxy. No pub/app id needed for Dynamic Delivery.
// If desired, you can use the same authProxy that you created when you initialized the Offline Video Manager.
self.authProxy = [[BCOVFPSBrightcoveAuthProxy alloc] initWithPublisherId:nil applicationId:nil];

// Set up the session provider chain
<BCOVPlaybackSessionProvider> psp = [sdkManager createBasicSessionProviderWithOptions:nil];
<BCOVPlaybackSessionProvider> fps = [sdkManager createFairPlaySessionProviderWithAuthorizationProxy:self.authProxy upstreamSessionProvider:psp];

// Create the playback controller
id<BCOVPlaybackController> playbackController = [sdkManager createPlaybackControllerWithSessionProvider:fps viewStrategy:nil];

// Configure and save
playbackController.autoAdvance = YES;
playbackController.autoPlay = YES;
playbackController.delegate = self;
self.playbackController = playbackController;
```

Then, to play the video, convert the token to a `BCOVVideo` object, check its availability, and pass to the playback controller:

```
BCOVVideo *video = [BCOVOfflineVideoManager.sharedManager videoObjectFromOfflineVideoToken:offlineVideoToken];

If (video.playableOffline)
{
  [self.playbackController setVideos:@[video]];
}
else
{
  // alert user that the video needs to be re-downloaded
}
```

Note that `video.playableOffline` indicates whether a video is fully downloaded and stored locally and can therefore be played without a network connection. A video download in progress can be played even if `video.playableOffline` is `false`. Refer to the section "Playback During Download".

## Pause/Resume/Cancel Downloads

When a video is being downloaded, you can pause, resume, or cancel the download using the following `BCOVOfflineVideoManager` methods:

- `-(void)pauseVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken`
- `-(void)resumeVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken`
- `-(void)cancelVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken`

You should use these methods rather than operating on the internal `AVAssetDownloadTask` itself.

## Renewing a FairPlay License

Starting with version 6.2.2 of the iOS Native Player SDK, you can renew the FairPlay license for a downloaded video without re-downloading the video. The device must be online for license renewal to succeed.

To renew a license, call `-renewFairPlayLicense:video:parameters:completion:` with the offline video token for your previously-downloaded video, and a parameter dictionary specifying the new license terms. The parameter dictionary must not contain bitrate or subtitle language information.

You should also specify a `BCOVVideo` object for the `video` argument. This video object should be the same video that you originally downloaded, but freshly retrieved from the Playback API, either directly, or through the `BCOVPlaybackService` class. This video object's data are not re-downloaded; the object is used to refresh your license exchange URLs in case the original ones used to download the video have expired. If the referenced video is no longer available through the Playback API, you can use a substantially similar video, meaning the video should be from the same account, and also have the same FairPlay configuration.

For example, here is how you can renew a FairPlay license with a new 30-day rental license:

```
  // Get fresh video object for this offline video
  NSDictionary *configuration = @{
    kBCOVPlaybackServiceConfigurationKeyAssetID: offlineVideoID
  };
  [playbackService findVideoWithConfiguration:configuration
                              queryParameters:nil
                                   completion:^(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error)
   {

     parameters = @{
       // Renew license with a 30-day rental
       kBCOVFairPlayLicenseRentalDurationKey: @( 30 * 24 * 60 * 60 ), // 30 days in seconds
     };

     // Request license renewal
     [BCOVOfflineVideoManager.sharedManager renewFairPlayLicense:offlineVideoToken
                                                           video:video // recent video from Playback API or Playback Service
                                                      parameters:parameters
                                                      completion:^(BCOVOfflineVideoToken offlineVideoToken,
                                                                   NSError *error)
      {

         // handle errors

      }];
      
}];


```

If you are using the Playback Authorization Service you'll need to use the renew FairPlay license method that accepts an authorization token:

```
    // Request license renewal
    [BCOVOfflineVideoManager.sharedManager renewFairPlayLicense:offlineVideoToken
                                                          video:video // recent video from Playback API or Playback Service
                                                      authToken:authToken
                                                     parameters:parameters
                                                     completion:^(BCOVOfflineVideoToken offlineVideoToken,
                                                                  NSError *error)
    {

        // handle errors

    }];
```

When license renewal is finshed, the completion block will be called with the same offline video token that was passed in, plus an `NSError` indicating any problem that occurred (or `nil` if no error). This block is not called on any specific thread.

## FairPlay Application Certificates

As part of Dynamic Delivery, a reference to the FairPlay application certificate associated with each video is stored inside each FairPlay-encrypted `BCOVVideo` object. The certificate is retrieved from a remote server as needed, so you do not need to load or set any FairPlay application certificates on your own.

The same application certificate is used across each Brightcove account, so there will often be a single application certificate used for all your videos. Application certificates are cached for re-use so they will typically be retrieved only once.

## Downloading Videos in the Background

iOS allows HLS video downloads to run in a background thread, even if an app is suspended or terminated under certain conditions.

When an app is relaunched, `BCOVOfflineVideoManager` will restore downloads whenever possible, but it is important to understand the limitations.

After an app is terminated, the SDK can recover downloads in progress in the following cases:

- App termination due to memory pressure in foreground
- App termination due to high memory usage when the app is suspended
- App crashes (null pointers, exceptions, etc.)
- App termination while suspended due to limited system resources

The SDK can't recover downloads in progress when:

- Running with Xcode (when Xcode terminates the process)
- Termination via the App Switcher (e.g., on devices with a home button, a double-home-press and slide up)
- Termination while the app is suspended and the device reboots

Downloads are restored once during the call to `initializeOfflineVideoManagerWithDelegate:options:`. Downloads that cannot be recovered will be reported immediately through the normal delegate methods; at this point you can delete them like any other video.

## Downloading Multiple Videos

When downloading multiple videos, you can download them all at once, or with a download queue.

With either technique, it's a good idea to preload any FairPlay licenses before starting any downloads, because although downloads can run in the background, FairPlay license exchange cannot happen while the app is in the background.

**Concurrent Downloads**

It's possible to download multiple videos at the same time, but performance may take a hit, so it's probably not a good idea to download more than a couple of videos at the same time.

When you request a video download, the first thing that happens is FairPlay license generation and key exchange, if needed. After this, the download proceeds to completion.

If you request multiple downloads at the same time, it may take a while for the licence and key requests for some of the videos to begin processing and/or complete. It's important that the key exchange for all the videos happen before allowing the user to move the app to the background.

If the app moves to the background before all the key exchanges are complete, FairPlay may not get a chance to make its callbacks in a timely fashion, and the download with an incomplete license will result in an error.

There are several ways to address this:

- Only allow the user to download one or two videos at a time. This ensures that the license is secured as soon as possible, and that the video will download successfully.
- If allowing multiple concurrent downloads, inform the user that they should not move the app to the background until all the downloads have started to report progress. You could simply put up a "please wait" notice until you detect progress from all the downloads.

You may want to limit the number of allowed concurrent downloads for practical reasons. The more downloads you begin at once, the longer it takes for them to begin and complete. You should test with your own videos to see what works best for your app.

**Sequential Downloads**

You can preload FairPlay licenses for a set of videos, and then create a queue for downloading videos one at a time until they are all complete.

When doing this it's a good idea to enable the "Background Fetch" mode for the application so that you can be woken up periodically to handle download completions and kick off new downloads.

Please note that iOS does not wake up your application from the background immediately when a download has completed. This can take 10 to 15 minutes or longer; iOS has complete control over the timing and seems to minimize this activity for maximum energy efficiency. In some cases, when downloading multiple videos in the background, iOS may not complete your download at all in the background, opting instead to finish the download when the application has been brought back to the foreground. For the most reliable results, you may want to preload a single video license, download one video, and then post a notification to the user to return to the foreground to kick off another download.

## Playback During Download

### When downloading with AVMediaSelections

While a movie is downloading, you can play the movie by passing a `BCOVVideo` object created from the offline video token to the `BCOVPlaybackController` just like any other movie. We do this by using an internal reference stored in the currently active `AVAssetDownloadTask` (this is the method recommended by Apple to make the download and playback as efficient as possible).

Doing this has several potentially unexpected side effects:

- When you start playing, progress on the download task may stop. The `AVPlayer` appears to take over all network activity to give priority to buffering and displaying the playing video. This is normal behavior.

- When you stop playing, the download task may not resume. This will happen if the video's session is still active in the `BCOVPlaybackController`. To clear out the current session, you can play a new video, or delete the playback controller. Be sure you don't store the current session in a strong property.

## AirPlay

You cannot stream an offline HLS video to an AirPlay device for playback. This is an AVFoundation limitation.

## Playing the Same Offline Video Twice

Unexpected network activity can occur when playing the same offline video two times in a row in a certain way. If you play a video with one playback controller, and then immediately play the same video with another playback controller, the `AVPlayer` for the second video attempts to retrieve its video data from the Internet rather than from local storage. If the device is not online then the `AVPlayer` will not play the second video.

This happens when two `AVPlayer`s and their associated objects are in memory together for a brief time referencing the same video in local storage. It's unknown exactly why the `AVPlayer` switches to playing the online version; we have isolated this behavior and submitted a bug report to Apple (39354411).

When possible, a better way to play the same video twice is to simply seek the same playback controller to timecode zero and play again.

If this is not possible, and you still need to create another playback controller, another alternative is to remove the first `AVPlayer`'s current `AVPlayerItem` when you are done with the current session, and just before you destroy the playback controller. You can accomplish this with a single call:

```
[session.player removeAllItems];
```

## Specifying the Download Display Name

Users can directly examine and optionally delete downloaded videos using the Settings app.

### When downloading with AVMediaSelections

The displayed video name is taken from the "name" property of the `BCOVVideo` object. If the "name" property is not present, the offline video token's value will be used instead.

To provide a more customized experience, you can set a display name for the video asset in the options dictionary passed to `-requestVideoDownload:mediaSelections:parameters:completion:` (or when preloading the license). Use the `kBCOVOfflineVideoManagerDisplayNameKey` key to set an `NSString` as the new asset display name.

Note that iOS uses the asset name string as part of the downloaded video's file path, so you should avoid characters that would not be valid in a POSIX path, like a "/" character.

You may choose to replace these with more standardized names using the `kBCOVOfflineVideoManagerDisplayNameKey` option.

### When downloading with AVAssetDownloadConfiguration

The displayed video name is taken from value you use for `title` argument when initializing `AVAssetDownloadConfiguration`.

You can also provide a value for the `artworkData` property on `AVAssetDownloadConfiguration`. This will display an image next to the video name in the Settings app.

```
NSURL *thumbnailURL = [NSURL URLWithString:video.properties[kBCOVVideoPropertyKeyThumbnail]];
downloadConfiguration.artworkData = [NSData dataWithContentsOfURL:thumbnailURL];
```
