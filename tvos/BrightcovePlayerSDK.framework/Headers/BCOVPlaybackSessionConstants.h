//
// BCOVPlaybackSessionConstants.h
// BrightcovePlayerSDK
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

/**
 * The video loaded successfully and is ready to play.
 *
 * If `autoPlay` is enabled It is possible for this event to be triggered
 * after seeing `kBCOVPlaybackSessionLifecycleEventPlay`. If you require
 * this event to be triggered prior to `kBCOVPlaybackSessionLifecycleEventPlay`
 * you can disable `autoPlay` and call `play` on your `BCOVPlaybackController`
 * after observing `kBCOVPlaybackSessionLifecycleEventReady`.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventReady;

/**
 * The video failed to load. The event properties will contain the underlying error
 * keyed by kBCOVPlaybackSessionEventKeyError.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventFail;

/**
 * The video has been set to play mode, and the video will play when it is ready
 * and has buffer.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPlay;

/**
 * The video has been set to pause mode, and the video will pause.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPause;

/**
 *  A request to play the current video has been made.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPlayRequest;

/**
 * A request to pause the current video has been made.
*/
extern NSString * const kBCOVPlaybackSessionLifecycleEventPauseRequest;

/**
 * The video failed during playback and was unable to recover, possibly due to a
 * network error. The event properties will contain the underlying error keyed
 * by kBCOVPlaybackSessionEventKeyError.
 *
 * It may be possible to recover from this error once the network has recovered,
 * by using the -[BCOVPlaybackController resumeVideoAtTime:withAutoPlay:] method.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventFailedToPlayToEndTime;

/**
 * A call to -[BCOVPlaybackController resumeVideoAtTime:withAutoPlay:] was made
 * and the player is attempting to reload the video.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventResumeBegin;

/**
 * A call to -[BCOVPlaybackController resumeVideoAtTime:withAutoPlay:] was made
 * and the player was able to reload the video.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventResumeComplete;

/**
 * A call to -[BCOVPlaybackController resumeVideoAtTime:withAutoPlay:] was made
 * and the player was unable to reload the video.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventResumeFail;

/**
 * The end of the video has been reached. This event will come after any post-roll
 * ads.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventEnd;

/**
 * Playback of the video has stalled. When the video recovers,
 * kBCOVPlaybackSessionLifecycleEventPlaybackRecovered will be sent.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPlaybackStalled;

/**
 * Playback has recovered after being stalled. This event will come after
 * kBCOVPlaybackSessionLifecycleEventPlaybackStalled.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPlaybackRecovered;

/**
 * The playback buffer is empty. This will occur when the video initially loads,
 * after a seek occurs, and when playback stops because of a slow or disabled
 * network. When the buffer is full enough to start playback again,
 * kBCOVPlaybackSessionLifecycleEventPlaybackLikelyToKeepUp will be sent.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPlaybackBufferEmpty;

/**
 * After becoming empty, this event is sent when the playback buffer has filled
 * enough that it should be able to keep up with playback. This event will come after
 * kBCOVPlaybackSessionLifecycleEventPlaybackBufferEmpty.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPlaybackLikelyToKeepUp;

/**
 * The session will be disposed of by the player.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventTerminate;

/**
 * A cast session has started.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventStartCastSession;

/**
 * A cast session has ended.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventEndCastSession;

/**
 * A generic error has occurred. The event properties may contain the underlying
 * error keyed by kBCOVPlaybackSessionEventKeyError.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventError;

/**
 * A bumper video has started to play.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventBumperEnter;

/**
 * A bumper video has ended.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventBumperExit;

/**
 * The bumper video has been paused.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventBumperPause;

/**
 * The bumper video has been resumed.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventBumperResume;

/**
 * A progress event for the currently playing bumper.
 * Information about the current bumper may be found in the properties dictionary.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventBumperProgress;

/**
 * The video failed during playback and was unable to recover, possibly due to a
 * network error. The event properties will contain the underlying error keyed
 * by kBCOVPlaybackSessionEventKeyError.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventBumperFailedToPlayToEndTime;

/**
 * The key for the bumper video in the Event properties.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPropertiesKeyBumperVideo;

/**
 * The key for the bumper progress in the Event properties.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventPropertiesKeyBumperProgress;

/**
 * The video has entered an ad sequenece.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdSequenceEnter;

/**
 * The video has exited an ad sequenece.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdSequenceExit;

/**
 * The video has entered an ad.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdEnter;

/**
 * The video has exited an ad.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdExit;

/**
 * A progress event for the currently playing ad.
 * Information about the current ad may be found in the properties dictionary.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdProgress;

/**
 * The current ad has been paused.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdPause;

/**
 * The current ad has been resumed.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdResume;

/**
 * The current ad has been skipped.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventAdSkipped;

/**
 * Sent when the content video will be paused to play back an ad.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventWillPauseForAd;

/**
 * The thumbnail seeking asset failed to load. The event properties may contain the underlying
 * error keyed by kBCOVPlaybackSessionEventKeyError.
 */
extern NSString * const kBCOVPlaybackSessionLifecycleEventThumbnailAssetFailedToLoad;

/**
 * The key for the error in the Event properties.
 */
extern NSString * const kBCOVPlaybackSessionEventKeyError;

/**
 * The key for the didPassCuePoints: payload for the progress interval
 * immediately preceding the cue points for which the payload was received.
 */
extern NSString * const kBCOVPlaybackSessionEventKeyPreviousTime;

/**
 * The key for the didPassCuePoints: payload for the progress interval on or
 * immediately after the cue points for which the payload was received.
 */
extern NSString * const kBCOVPlaybackSessionEventKeyCurrentTime;

/**
 * The key for the didPassCuePoints: payload for the BCOVCuePointCollection of cue
 * points for which the payload was received.
 */
extern NSString * const kBCOVPlaybackSessionEventKeyCuePoints;

/**
 * Error domain for the SDK.
 */
extern NSString * const kBCOVPlaybackSessionErrorDomain;

/**
 * The video failed to load.
 */
extern const NSInteger kBCOVPlaybackSessionErrorCodeLoadFailed;

/**
 * The video failed during playback and was unable to recover, possibly due to a
 * network error.
 */
extern const NSInteger kBCOVPlaybackSessionErrorCodeFailedToPlayToEnd;

/**
 * No playable Source was available for this Video.
 */
extern const NSInteger kBCOVPlaybackSessionErrorCodeNoPlayableSource;

/**
 * No WiFi network is available and allowsCellularPlayback is disabled.
 */
extern const NSInteger kBCOVPlaybackSessionErrorCodeWifiUnavailable;
