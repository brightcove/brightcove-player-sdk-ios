# Using FairPlay With The Brightcove Player SDK for iOS, version 7.2.4.13

## Quick Start

Brightcove FairPlay is a bridge between Apple FairPlay and the [Brightcove Player SDK for iOS][bcovsdk]. The following sections show how to set up your code for basic playback.

**Please note the following FairPlay limitations with iOS/tvOS:**

* While the plugin contains simulator architectures, you can not play FairPlay protected content in a simulator.

* FairPlay streaming content will not be rendered in AirPlay Mirroring mode. For more details, see the 2015 WWDC presentation 502: [Content Protection for HLS][wwdc502].

[wwdc502]: https://developer.apple.com/videos/play/wwdc2015/502/

## Video Cloud Dynamic Delivery

When you use Video Cloud Dynamic Delivery, a reference to the FairPlay application certificate is embedded in the BCOVVideo object returned from the playback service. The SDK uses this reference to retrieve the application certificate when you play your FairPlay videos.

Here are the basic steps you need to follow:

```swift
var playbackController: BCOVPlaybackController?

-------

// Create a BCOVFPSBrightcoveAuthProxy object.
// Use the built-in authorization proxy to take advantage of Dynamic Delivery.
// The application id and publisher id are not needed with Dynamic Delivery.
// You also don't need to worry about retrieving any application certificates.
let proxy = BCOVFPSBrightcoveAuthProxy(withPublisherId: nil,
                                       applicationId: nil)

let sdkManager = BCOVPlayerSDKManager.sharedManager()

// Brightcove FairPlay adds some category methods to BCOVPlaybackManager.
let playbackController = sdkManager.createFairPlayPlaybackController(withAuthorizationProxy: proxy)
playbackController.delegate = self
self.playbackController = playbackController
view.addSubview(playbackController.view)

let playbackService = BCOVPlaybackService.init(withAccountId: "<account-id>",
                                               policyKey: "<policy-key>")

let configuration = [
    BCOVPlaybackService.ConfigurationKeyAssetID: "<video-id>"
]

playbackService.findVideo(withConfiguration: configuration,
                          queryParameters: nil) { (video: BCOVVideo?,
                                                   jsonResponse: Any?,
                                                   error: Error?) in
    if let video {
        self.playbackController?.setVideos([video])
    }
}
```

## Legacy Video Cloud Workflow

If you are using a legacy Video Cloud workflow, you need to retrieve a FairPlay certificate prior to playing your videos.
This code shows basic setup and playback:

```swift
var playbackController: BCOVPlaybackController?

-------

// Create a BCOVFPSBrightcoveAuthProxy object.
// Use the built-in authorization proxy to take advantage of Dynamic Delivery.
// The application id and publisher id are not needed with Dynamic Delivery.
// You also don't need to worry about retrieving any application certificates.
let proxy = BCOVFPSBrightcoveAuthProxy(withPublisherId: nil,
                                       applicationId: nil)

let sdkManager = BCOVPlayerSDKManager.sharedManager()

// Brightcove FairPlay adds some category methods to BCOVPlaybackManager.
let playbackController = sdkManager.createFairPlayPlaybackController(withAuthorizationProxy: proxy)
playbackController.delegate = self
self.playbackController = playbackController
view.addSubview(playbackController.view)

// Using the proxy, retrieve the FairPlay application certificate.
// In a production app, you might want to do this as soon as the app starts up.
proxy.retrieveApplicationCertificate { (applicationCetificate: Data?, error: Error?) in
    
    if let applicationCetificate {
        // Add the application certificate to the playback controller
        playbackController.addFairPlayApplicationCertificate(applicationCetificate,
                                                             identifier: kBCOVDefaultFairPlayApplicationCertificateIdentifier)
        
        let playbackService = BCOVPlaybackService.init(withAccountId: "<account-id>",
                                                       policyKey: "<policy-key>")
        
        let configuration = [
            BCOVPlaybackService.ConfigurationKeyAssetID: "<video-id>"
        ]

        playbackService.findVideo(withConfiguration: configuration,
                                  queryParameters: nil) { (video: BCOVVideo?,
                                                           jsonResponse: Any?,
                                                           error: Error?) in
            if let video {
                self.playbackController?.setVideos([video])
            }
        }
    }

}

```

You can add multiple FairPlay application certificates to the playback controller, but with legacy playback you would typically need only one. If you are playing videos from two different accounts with the same playback controller, you can add an application certificate for each account with the account ID as the "identifier" parameter.

If you are using older methods to create the playback controller, those method will continue to work. The newer methods were created to provide more flexibility by letting you retrieve the FairPlay application certificate before or after the playback controller is created, and in the case of Dynamic Delivery, you don't need to retrieve or pass in the application certificate at all.

If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at [https://groups.google.com/forum/#!forum/brightcove-native-player-sdks][forum] .

[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios
[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

## Error Handling

FairPlay license related errors will be passed through in a `kBCOVPlaybackSessionLifecycleEventError` lifecycleEvent. These can include license server request failures or AVContentKeySession errors. You can access the `NSError` object with the `kBCOVPlaybackSessionEventKeyError` in the lifecycleEvent's properties dictionary. 

If the issue is related to a license server request (which can include concurrency-limit and device-limit errors) you'll be able to retrieve the response data from the userInfo dictionary on the `NSError` with the `BCOVFPSBrightcoveAuthProxy.ResponseData` key.

Here is an example of logging errors from an `kBCOVPlaybackSessionLifecycleEventError` lifecycleEvent:

```swift
func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didReceive lifecycleEvent: BCOVPlaybackSessionLifecycleEvent) {

    if kBCOVPlaybackSessionLifecycleEventError == lifecycleEvent.eventType {

        if let error = lifecycleEvent.properties[kBCOVPlaybackSessionEventKeyError] as? NSError {

            if let responseData = error.userInfo[BCOVFPSBrightcoveAuthProxy.ResponseData] as? Data,
               let responseString = String(data: responseData, encoding: .utf8) {

                print("License Server Error: \(responseString)")

            } else {
                print("Error: \(error.localizedDescription)")

                // Some errors may contain an underlying NSError
                if let underlyingError = error.userInfo[NSUnderlyingErrorKey] as? NSError {
                    print("Underlying Error: \(underlyingError.localizedDescription)")
                }
            }

        }

    }

}
```

## Content Key Preloading

You may preload content keys for videos by calling  the `preloadContentKeysForVideos:` class method on `BCOVFairPlayManager`. Typically a content key for a FairPlay protected video is processed when the video begins playback. By preloading the content key you can improve the playback startup experience for your users. For example:

```swift
let configuration = [
    BCOVPlaybackService.ConfigurationKeyAssetID: "<video-id>"
]

playbackService.findVideo(withConfiguration: configuration,
                          queryParameters: nil) { (video: BCOVVideo?,
                                                   jsonResponse: Any?,
                                                   error: Error?) in
    if let video {
        // The `preloadContentKeys:` method does not retain a reference
        // to the videos array passed so you must hold on to the reference
        // until, at least, `setVideos()` has been called on your `BCOVPlaybackController`
        // which does retain the array.
        self.video = video
        BCOVFairPlayManager.preloadContentKeys(forVideos: [video])
    }
}
```

## Application Certificates

Playabck of FairPlay-protected videos requires an application certificate associated with the content. 

If you are using Video Cloud Dynamic Delivery, application certificates are downloaded and used as needed by the Brightcove SDK. Certificates are cached for re-use so there will typically be a single download per account.

If you are using legacy Video Cloud services, you still need to retrieve an application certificate to pass in with your initialization methods. The `BCOVFPSBrightcoveAuthProxy` class offers a convenience method to retrieve this from fps.brightcove.com.

If you store your own application certificate remotely, you can retrieve it with a normal `NSURLSessionDataTask` retrieving the certificate as an `NSData` object. Once received, you can add the certificate to your playback controller using `playbackController?.addFairPlayApplicationCertificate(_,identifier:)`. In most cases you would use `kBCOVDefaultFairPlayApplicationCertificateIdentifier` as the identifier.

## Using a Third-Party FairPlay License Server

The `BCOVFPSBrightcoveAuthProxy` is intended to work with `fps.brightcove.com`. If you need to use another FairPlay license server, you can either implement the `BCOVFPSAuthorizationProxy` protocol to handle the license communication, or if your needs are simple you can override a few of the `BCOVFPSAuthorizationProxy` properties:

```swift
/// The base url for FairPlay related license requests. The default URL points to
/// fps.brightcove.com.
/// If set to nil, the default URL pointing at fps.brightcove.com will be re-created.
@objc public var fpsBaseURL: URL?
	
/// The key request URL for FairPlay related key requests.
/// Normally set to nil, in which case the key request URL
/// will be retrieved from the Video Cloud Playback API response.
@objc public var keyRequestURL: URL?
```

The `fpsBaseURL` property is also used to set the base URL for application certificate requests. Certificates are requested as follows:

```
[fpsBaseURL]/application_certificate/[publisherID]/[applicationID]
```

Whether using Video Cloud or your own server, your `BCOVVideo` object should contain a `BCOVSource` object whose URL points to some FairPlay-protected content. Unprotected video URLs will still play in a FairPlay workflow.
