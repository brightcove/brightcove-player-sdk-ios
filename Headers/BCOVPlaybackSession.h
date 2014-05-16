//
// BCOVPlaybackSession.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#import "ReactiveCocoa.h"


@class BCOVSource;
@class BCOVVideo;


extern NSString * const kBCOVPlaybackSessionLifecycleEventReady;
extern NSString * const kBCOVPlaybackSessionLifecycleEventPlay;
extern NSString * const kBCOVPlaybackSessionLifecycleEventPause;
extern NSString * const kBCOVPlaybackSessionLifecycleEventEnd;
extern NSString * const kBCOVPlaybackSessionLifecycleEventTerminate;
extern NSString * const kBCOVPlaybackSessionLifecycleEventFail;

extern NSString * const kBCOVPlaybackSessionEventKeyPreviousTime;
extern NSString * const kBCOVPlaybackSessionEventKeyCurrentTime;
extern NSString * const kBCOVPlaybackSessionEventKeyCuePoints;

extern NSString * const kBCOVPlaybackSessionErrorDomain;
extern const NSInteger kBCOVPlaybackSessionErrorCodeLoadFailed;


/**
 * A playback session represents the playback of a single video. The session
 * provides a single point of access for everything related to the playback
 * experience for that video: the video and source selected for playback, the
 * player within which the playback occurs, and events that occur during the
 * playback session. Playback sessions are never reused for multiple videos
 * (even separate enqueueings of the same video).
 */
@protocol BCOVPlaybackSession <NSObject>

/**
 * The video whose playback this session represents.
 */
@property (nonatomic, readonly, copy) BCOVVideo *video;

/**
 * The source in `self.video` this session uses to load content.
 */
@property (nonatomic, readonly, copy) BCOVSource *source;

/**
 * The player this session uses to present content.
 */
@property (nonatomic, readonly, strong) AVPlayer *player;

/**
 * The layer that hosts the visible video output.
 */
@property (nonatomic, readonly, strong) AVPlayerLayer *playerLayer;

/**
 * Sends a dictionary for each cue point event that is sent after subscription.
 * Events will occur regardless of whether the playhead passes the cue point
 * time for standard progress (playback), or seeking (forward or backward)
 * through the media. When a delegate is set on a playback controller, this
 * method will only be called for future cue point events (any events that have
 * already occurred will not be reported).
 *
 * If multiple cue points are registered to a time or times that fall between
 * the "previous time" and "current time" for a cue point event, all cue points
 * after the "previous time" and before or on "current time" will be included
 * in the cue point collection. Put differently, multiple cue points at the
 * same time are aggregated into a single cue point event whose collection will
 * contain all of those cue points. The most likely scenario in which this
 * would happen is when seeking across a time range that includes multiple cue
 * points (potentially at different times) -- this will result in a single cue
 * point event whose previous time is the point at which seek began, whose
 * current time is the destination of the seek, and whose cue points are all of
 * the cue points whose time fell within that range.
 *
 * The dictionary contains the following keys and values: 
 *
 * kBCOVPlaybackSessionEventKeyCuePoints: the cue point collection of all
 *   cue point objects whose time is after the previous progress time interval,
 *   but before or on the current progress time interval.
 * kBCOVPlaybackSessionEventKeyPreviousTime: the progress interval immediately
 *   preceding the cue point event.
 * kBCOVPlaybackSessionEventKeyCurrentTime: the current progress interval (at
 *   which the cue point event is sent).
 *
 * This signal does not make guarantees about the scheduler on which it sends
 * its values. Clients must explicitly deliver its events to the main thread
 * scheduler (or another scheduler) if requirements dictate.
 *
 * @return A signal sending the cue point events in this session.
 */
- (RACSignal *)cuePoints;

/**
 * Sends a CMTime (wrapped in an NSValue) representing the new duration of
 * this session's player's item. Sends the most recently-set duration on
 * subscription.
 *
 * This signal does not make guarantees about the scheduler on which it sends
 * its values. Clients must explicitly deliver its events to the main thread
 * scheduler (or another scheduler) if requirements dictate.
 *
 * @return A signal sending the duration changes for this session's player
 * item.
 */
- (RACSignal *)durationChanges;

/**
 * Sends a Boolean (wrapped in an NSNumber) representing whether external
 * playback was enabled for this session. Sends the most recently-set external
 * playback configuration on subscription.
 *
 * This signal does not make guarantees about the scheduler on which it sends
 * its values. Clients must explicitly deliver its events to the main thread
 * scheduler (or another scheduler) if requirements dictate.
 *
 * @return A signal sending the external playback status changes for this
 * session.
 */
- (RACSignal *)isExternalPlaybackActive;

/**
 * Sends a BCOVPlaybackSessionLifecycleEvent representing a lifecycle change
 * event for this session. This is a hot signal, meaning that events that have
 * already been sent will not be re-sent for new subscribers.
 *
 * Sends an error if the session enters an unrecoverable error state.
 *
 * This signal does not make guarantees about the scheduler on which it sends
 * its values. Clients must explicitly deliver its events to the main thread
 * scheduler (or another scheduler) if requirements dictate.
 *
 * @return A signal sending the lifecycle change events for this session, or
 * an error if this session encounters a lifecycle error.
 */
- (RACSignal *)lifecycle;

/**
 * Sends a CMTime (wrapped in an NSValue) representing the current playhead
 * position for each progress event after subscription.
 *
 * This signal does not make guarantees about the scheduler on which it sends
 * its values. Clients must explicitly deliver its events to the main thread
 * scheduler (or another scheduler) if requirements dictate.
 *
 * @return A signal sending the session progress.
 */
- (RACSignal *)progress;

/**
 * Terminates this playback session, completing all of its playback event
 * signals and indicating readiness for a new session to be dequeued. A
 * terminated playback session should be discarded immediately.
 *
 * In a typical configuration using a BCOVPlaybackController, there is no need
 * to call this method directly. Methods on the controller are the preferred
 * mechanism for advancing to the next playback session. However, playback
 * session provider configurations which do not use a BCOVPlaybackController
 * may need to invoke this method to advance the queue.
 */
- (void)terminate;

@end


/**
 * An event occuring on the lifecycle signal of a playback session.
 */
@interface BCOVPlaybackSessionLifecycleEvent : NSObject <NSCopying>

/**
 * This lifecycle event's type.
 */
@property (nonatomic, readonly) NSString *eventType;

/**
 * Contextual information related to this event instance.
 */
@property (nonatomic, readonly) NSDictionary *properties;

/**
 * Designated initializer. Returns an event with the specified type and properties.
 *
 * @param eventType Type of the event.
 * @param properties Properties of the event
 * @return Initialized event.
 */
- (id)initWithEventType:(NSString *)eventType properties:(NSDictionary *)properties;

/**
 * Determines the equality of the events.
 *
 * @param event Event to check against.
 * @return Returns YES if the events are equal and NO if the events are no equal.
 */
- (BOOL)isEqualToPlaybackSessionLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)event;

/**
 * Returns a playback session lifecycle event of the specified type with no
 * properties.
 *
 * @param eventType The event type of the lifecycle event to return.
 * @return The playback session lifecycle event of the specified type.
 */
+ (instancetype)eventWithType:(NSString *)eventType;

@end