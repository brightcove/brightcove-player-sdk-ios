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
