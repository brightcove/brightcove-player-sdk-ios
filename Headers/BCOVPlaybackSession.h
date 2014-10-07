//
// BCOVPlaybackSession.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>


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
 * Terminates this playback session, indicating readiness for a new session to
 * be dequeued. A terminated playback session should be discarded immediately.
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
 * A lifecycle event for a playback session.
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
- (instancetype)initWithEventType:(NSString *)eventType properties:(NSDictionary *)properties;

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
