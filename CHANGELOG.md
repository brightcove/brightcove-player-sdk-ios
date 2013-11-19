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
