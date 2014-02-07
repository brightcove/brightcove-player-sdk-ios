//
// BCOVDelegatingSessionConsumer.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//


#import "BCOVPlaybackController.h"

@protocol BCOVDelegatingSessionConsumerDelegate;


/**
 * This is a simple implementation of the session consumer protocol that
 * provides convenient delegate methods for accessing session information.
 */
@interface BCOVDelegatingSessionConsumer : NSObject <BCOVPlaybackSessionConsumer>

/**
 * Designated initializer. When this objected is added as a session consumer to
 * a playback controller, this object will call delegate methods on the specified
 * delegate.
 *
 * @param delegate Delegate for this consumer.
 * @return Initialized instance.
 */
-(id)initWithDelegate:(id<BCOVDelegatingSessionConsumerDelegate>)delegate;

@end


/**
 * Methods which may be implemented by delegates of a session consumer.
 * The delegating session consumer delegate protocol offers a simplified API
 * for responding to the various changes and events in the playback
 * sessions consumed by the session consumer. If you are comfortable using
 * ReactiveCocoa's signal API, the signal methods offered by
 * BCOVPlaybackSession offer similar functionality, and with better
 * flexibility. This delegate is intended for clients who do not wish to use
 * signals directly.
 */
@protocol BCOVDelegatingSessionConsumerDelegate <NSObject>

@optional

/**
 * Called when the session consumer receives a new playback session.
 *
 * @param consumer The session consumer registered on the playback controller.
 * @param session The playback session that was advanced.
 */
- (void)playbackConsumer:(id<BCOVPlaybackSessionConsumer>)consumer didAdvanceToPlaybackSession:(id<BCOVPlaybackSession>)session;

/**
 * Called when a playback session's duration is updated. A session duration can
 * change as the media playback continues to load, as it is refined with more 
 * precise information.
 *
 * @param consumer The session consumer registered on the playback controller.
 * @param session The playback session whose duration changed.
 * @param duration The most recently updated session duration.
 */
- (void)playbackConsumer:(id<BCOVPlaybackSessionConsumer>)consumer playbackSession:(id<BCOVPlaybackSession>)session didChangeDuration:(NSTimeInterval)duration;

/**
 * Called when a playback session's external playback active status is updated.
 *
 * @param consumer The session consumer registered on the playback controller.
 * @param session The playback session whose external playback status changed.
 * @param externalPlaybackActive Whether external playback is active.
 */
- (void)playbackConsumer:(id<BCOVPlaybackSessionConsumer>)consumer playbackSession:(id<BCOVPlaybackSession>)session didChangeExternalPlaybackActive:(BOOL)externalPlaybackActive;

/**
 * Called when a session's playhead passes cue points registered with its video.
 * This will occur regardless of whether the playhead passes the cue point time
 * for standard progress (playback), or seeking (forward or backward) through
 * the media.
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
 * The cuePointInfo dictionary will contain the following keys and values for
 * each cue point event:
 *
 *   kBCOVPlaybackSessionEventKeyPreviousTime: the progress interval immediately
 *     preceding the cue points for which this event was received.
 *   kBCOVPlaybackSessionEventKeyCurrentTime: the progress interval on or
 *     immediately after the cue points for which this event was received.
 *   kBCOVPlaybackSessionEventKeyCuePoints: the BCOVCuePointCollection of cue
 *     points for which this event was received.
 *
 * @param consumer The session consumer registered on the playback controller.
 * @param session The playback session whose cue points were passed.
 * @param cuePointInfo A dictionary of information about the cue point event.
 */
- (void)playbackConsumer:(id<BCOVPlaybackSessionConsumer>)consumer playbackSession:(id<BCOVPlaybackSession>)session didPassCuePoints:(NSDictionary *)cuePointInfo;

/**
 * Called with the playback session's playback progress. As the session's
 * media plays, this method is called periodically with the latest progress
 * interval.
 *
 * @param consumer The session consumer registered on the playback controller.
 * @param session The playback session making progress.
 * @param progress The time interval of the session's current playback progress.
 */
- (void)playbackConsumer:(id<BCOVPlaybackSessionConsumer>)consumer playbackSession:(id<BCOVPlaybackSession>)session didProgressTo:(NSTimeInterval)progress;

/**
 * Called when a playback session receives a lifecycle event.
 *
 * The lifecycle event types are listed along with the
 * BCOVPlaybackSessionLifecycleEvent class.
 *
 * @param consumer The session consumer registered on the playback controller.
 * @param session The playback session whose lifecycle events were received.
 * @param lifecycleEvent The lifecycle event received by the session.
 */
- (void)playbackConsumer:(id<BCOVPlaybackSessionConsumer>)consumer playbackSession:(id<BCOVPlaybackSession>)session didReceiveLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)lifecycleEvent;

@end

