Brightcove Native Player SDK
============

iOS App Developer's Guide to Video Downloading and Offline Playback with FairPlay
--------------

The Brightcove Native Player SDK allows you to download and play back HLS videos protected with FairPlay encryption. Downloaded videos can be played back with or without a network connection.

### Requirements:

- iOS 10.0+
- Brightcove Native Player SDK v6.0.0+
- Brightcove FairPlay plugin v1.2.0+
- Brightcove Dynamic Delivery

iOS does not allow FairPlay-protected video to display in a simulator, nor does it allow video downloads to a simulator, so it's important to develop on an actual device.

### Basic Concepts

When you request a video download, you will be given a token that is used to keep track of both the active download and the offline video in device storage. The token is of type `BCOVOfflineVideoToken`, and is referred to as a token rather than an object because it can be persisted, and is valid across instances of the app.

Videos are stored in the app's Library directory, in a subdirectory determined by iOS. Apple specifically requires that these videos stay in this location. Be aware that videos can be deleted by iOS under extreme low-storage conditions. Also, videos and their associated metadata are not backed up to iCloud.

The FairPlay license is set up when the video download is requested. You can specify either a purchase license, or a rental license with an associated rental duration. The license rental duration begins from the moment the download request is made.

When a download begins, you can receive notification of progress and completion by setting yourself as a delegate of the `BCOVOfflineVideoManager` singleton object. Be sure that your object inherits the `BCOVOfflineVideoManagerDelegate` protocol.

By default, downloads are only allowed over WiFi connections, but this can be changed to enable downloads over cellular as well. Similarly, during playback, iOS may request some additional resources (like subtitle tracks if they were not downloaded). This will only happen on WiFi, but can be changed as well.

### Initialization

The `BCOVOfflineVideoManager` is a singleton class that manages all video downloads. Before using any `BCOVOfflineVideoManager` methods, you should call

```
[BCOVOfflineVideoManager initializeOfflineVideoManagerWithDelegate:self
							options:@{ kBCOVOfflineVideoManagerAllowsCellularDownloadKey : @(YES) }];
```

The options dictionary may be nil, but this example shows how to allow downloads over cellular networks.

After initialization, you can refer to the Offline Video Manager with the `BCOVOfflineVideoManager.sharedManager` property.

As part of setup, you also need to create and assign an authorization proxy to handle the details of FairPlay key exchange. You can use the Brightcove FairPlug's proxy to do this work:

```
// Publisher/application IDs not required for Dynamic Delivery
self.authProxy = [[BCOVFPSBrightcoveAuthProxy alloc] initWithPublisherId:nil
                                                       applicationId:nil];
    
BCOVOfflineVideoManager.sharedManager.authProxy = self.authProxy;
```

### Check If A Video Can Be Downloaded

In your user interface, you should indicate if a video is eligible for download. To do this,  examine the `BCOVVideo.canBeDownloaded` property. This Boolean property checks the status of the video's `offline_enabled` flag that is settable through the [Brightcove CMS API](http://docs.brightcove.com/en/video-cloud/cms-api/getting-started/overview-cms.html).

### Download A Video

When a user requests a video download, call

```
[BCOVOfflineVideoManager.sharedManager
    requestVideoDownload:video
    parameters:parameters
    completion:^(BCOVOfflineVideoToken offlineVideoToken, NSError *error) {

    // store offlineVideoToken or handle error

}];
```

The video parameter is a normal `BCOVVideo` object that you get by querying the `BCOVPlaybackService`. You should make sure that its `canBeDownloaded` property is `YES` before downloading.

The parameters argument is an `NSDictionary` in which you specify the license terms. For example, to request a license with a 30 day rental duration, you would use this:

```
licenseParameters = @{
	// 30 days in seconds
	kBCOVFairPlayLicenseRentalDurationKey: @(60 * 60 * 24 * 30),
};
```

The completion handler is where you asynchronously receive the offline video token or the error. You can store a reference to this offline video token if the error is nil.

### Check Download Size

Before a download is requested, it's a good idea to make sure there is enough space in storage for the download.

The method `[BCOVOfflineVideoManager estimateDownloadSize:options:completion:]` can be used to get an estimate of how much space, in megabytes, the download will require. If there is not enough space for a download, it will result in an error.

iOS needs a cushion to run properly, so you should not allow downloads to fill up all the free space on the device. If you use up all the free storage, the system may start deleting cached data in other apps, and may eventually remove a downloaded video from your own app.

The Brightcove SDK does not enforce any free space requirements, but we suggest making sure you leave at least 100 MB free.

### Get All Downloads

The `BCOVOfflineVideoManager` has an `offlineVideoTokens` property that returns an array of all the current offline video tokens. This includes tokens for videos that are currently downloading, and tokens for videos that are already in storage and have finished downloading. You can examine this property at any time to present to the user a list of videos that are downloading, or a list of videos that have been downloaded and are available for offline playback.

### Get Status Of Downloads

For any given offline video token, you can determine its status by calling `[BCOVOfflineVideoManager offlineVideoStatusForToken:]`. This method returns a `BCOVOfflineVideoStatus` object that contains various pieces of useful data about the download:

- Download state (requested, started, suspended, completed, canceled, or failed)
- Start time
- End time (if finished)
- Progress (percentage)
- Associated `AVAssetDownloadTask` (if the download is still in progress)

This call is essential for providing feedback in the user interface about what each download is doing.

To get information about the status of all offline videos at once, use the `BCOVOfflineVideoManager.offlineVideoStatus` property. This returns an array of `BCOVOfflineVideoStatus` objects, one for each offline video.

### Get Metadata From Offline Video Tokens

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

**`kBCOVOfflineVideoDownloadStartTimePropertyKey`**

Time that the offline video download was initially requested.

This time is stored as the floating point number of seconds since the standard `NSDate` reference date.
This value is useful when sorting by the time each download process started.
You can generate an `NSDate` object from this as follows: `[NSDate dateWithTimeIntervalSinceReferenceDate:number]`.

**`kBCOVOfflineVideoDownloadEndTimePropertyKey`**

Time that the offline video download completed (whether normally, cancelled, or failed).

This time is stored as the floating point number of seconds since the standard `NSDate` reference date. This value is useful when sorting by the time each download completes. This value is zero until the download completes.
You can generate an `NSDate` object from this as follows: `[NSDate dateWithTimeIntervalSinceReferenceDate:number]`.

**`kBCOVOfflineVideoOnlineSourceURLPropertyKey`**

URL of the original online video that was downloaded to storage for this `BCOVVideo` object, as an `NSString`.

Note that this URL may have expired, so this is primarily useful as a reference.

**`kBCOVOfflineVideoThumbnailNamePropertyKey`**

Name of the downloaded thumbnail image file in device storage, as an `NSString`.

This name is used to generate the full path of the file at runtime.

**`kBCOVOfflineVideoThumbnailFilePathPropertyKey`**

Full path to the downloaded thumbnail image file in device storage, as an `NSString`.

Even if the path is present, the image file may not be present. Due to app sandboxing, this path will likely change each time the app is launched, so you should not store the full path.

**`kBCOVOfflineVideoPosterNamePropertyKey`**

Name of the downloaded poster image file in device storage, as an `NSString`.

This name is used to generate the full path of the file at runtime.

**`kBCOVOfflineVideoPosterFilePathPropertyKey`**

Full path to the downloaded poster image file in device storage, as an `NSString`.

Even if the path is present, the image file may not be present. Due to app sandboxing, this path will likely change each time the app is launched, so you should not store the full path.

**`kBCOVOfflineVideoRelativeFilePathPropertyKey`**

Relative file path of the downloaded FairPlay video bundle in device storage, as an `NSString`.

This name is used to generate the full path of the file at runtime.

**`kBCOVOfflineVideoFilePathPropertyKey`**

Full path to the downloaded FairPlay video bundle in device storage, as an `NSString`.

Due to app sandboxing, this path will likely change each time the app is launched, so you should not store the full path.

### Play Back Offline Videos

To play an offline video, convert the offline video token to a `BCOVVideo` object, and then play the video as you would any normal online FairPlay video. Since videos can be deleted without warning by iOS, it's a good idea to check that the video is playable.

First, here's how you might create the playback controller in your setup code:

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

### Pause/Resume/Cancel Downloads

When a video is being downloaded, you can pause, resume, or cancel the download using the following `BCOVOfflineVideoManager` methods:

- `-(void)pauseVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken`
- `-(void)resumeVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken`
- `-(void)cancelVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken`

You should use these methods rather than operating on the internal `AVAssetDownloadTask` itself.

### FairPlay Application Certificates

As part of Dynamic Delivery, a reference to the FairPlay application certificate associated with each video is stored inside each FairPlay-encrypted `BCOVVideo` object. The certificate is retrieved from a remote server as needed, so you do not need to load or set any FairPlay application certificates on your own.

The same application certificate is used across each Brightcove account, so there will often be a single application certificate used for all your videos. Application certificates are cached for re-use so they will typically be retrieved only once.

### Downloading Videos In The Background

iOS allows HLS video downloads to run in a background thread, even if an app is suspended or terminated under certain conditions.

The `BCOVOfflineVideoManager` will restore downloads whenever possible, but it is important to understand the limitations.

After an app is terminated, the SDK can recover downloads in progress in the following cases:

- App termination due to memory pressure in foreground
- App termination due to high memory usage when the app is suspended
- App crashes (null pointers, exceptions, etc.)
- App termination while suspended due to limited system resources

We can't recover downloads in progress when:

- Running with Xcode (when Xcode terminates the process)
- Termination via the App Switcher (double-home-press and slide up)
- Termination while app is suspended and the device reboots

Downloads are restored once during the call to `initializeOfflineVideoManagerWithDelegate:options:`. There is nothing else that you need to do.

### Multiple Concurrent Downloads

It's possible to download multiple videos at the same time, but it is important to understand some aspects of this behavior.

When you request a video download, the first thing that happens is FairPlay license generation and key exchange. After this, the download proceeds to completion.

If you request multiple downloads at the same time, it may take a while for the licence and key requests for some of the videos to begin processing and/or complete. It's important that the key exchange for all the videos happen before allowing the user to move the app to the background.

If the app moves to the background before all the key exchanges are complete, FairPlay may not get a chance to make its callbacks in a timely fashion, and the download with an incomplete license will result in an error.

There are several ways to address this:

- Only allow the user to download a single video at a time. This ensures that the license is secured as soon as possible, and that the video will download successfully.
- If allowing multiple concurrent downloads, inform the user that they should not move the app to the background until all the downloads have started to report progress. You could simply put up a "please wait" notice until you detect progress from all the downloads.

You may want to limit the number of allowed concurrent downloads for practical reasons. The more downloads you begin at once, the longer it takes for them to begin and complete. You should test with your own videos to see what works best for your app.

### Playback During Download

While a movie is downloading, you can play the movie by passing a `BCOVVideo` object created from the offline video token to the `BCOVPlaybackController` just like any other movie. We do this by using an internal reference stored in the currently active `AVAssetDownloadTask` (this is the method recommended by Apple to make the download and playback as efficient as possible).

Doing this has several potentially unexpected side effects:

- When you start playing, progress on the download task may stop. The `AVPlayer` appears to take over all network activity to give priority to buffering and displaying the playing video. This is normal.

- When you stop playing, the download task may not resume. This will happen if the video's session is still active in the `BCOVPlaybackController`. To clear out the current session, you can play a new video, or delete the playback controller. Be sure you don't store the current session in a strong property.

- When you begin playback of a video that is downloading, the `AVPlayer` may initially seek to the end of the video, requiring the user to manually seek back to the beginning. This does not appear to be expected behavior and we are currently exploring workarounds.

### AirPlay

You cannot stream an offline HLS video to an AirPlay device for playback. This appears to be an AVFoundation limitation.

### Playing the Same Offline Video Twice

Unexpected network activity can occur when playing the same offline video two times in a row in a certain way. If you play a video with one playback controller, and then immediately play the same video with another playback controller, the `AVPlayer` for the second video may opt to retrieve its video data from the Internet rather than from local storage. (If the device is not online then the `AVPlayer` may not play the second video.)

We believe this happens when two `AVPlayer`s are in memory for a brief time referencing the same video in local storage. It's unknown exactly why the `AVPlayer` switches to playing the online version; we will address this with Apple when we can more precisely narrow down the behavior.

When possible, a better way to play the same video twice is to simply seek the same playback controller to timecode zero and play again.