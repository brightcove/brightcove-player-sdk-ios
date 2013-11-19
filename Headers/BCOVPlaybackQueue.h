//
// BCOVPlaybackQueue.h
// BCOVPlayerSDK
//
// Copyright (c) 2013 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>


@class RACSignal;


/**
 * Protocol adopted by objects that serve as a queue for playback sessions.
 *
 * Implementations of this formal protocol must support its standard queue
 * management operations, but may extend the API to perform additional
 * functions specific to their feature set.
 */
@protocol BCOVPlaybackQueue <NSObject>

/**
 * Whether to advance to the next playback session when its previous playback
 * session sends kBCOVPlaybackSessionLifecycleEventEnd. If this event is sent
 * more than once by a playback session, the subsequent sends are ignored.
 *
 * Defaults to NO.
 *
 * @return True if this queue should send the next session when the previous
 * session sends kBCOVPlaybackSessionLifecycleEventEnd.
 */
@property (nonatomic, assign, getter = isAutoAdvance) BOOL autoAdvance;

/**
 * Instructs this instance to advance this facade's queue, dequeueing a new
 * playback session for delivery on the queue's `playbackSessions` signal.
 * This may occur asynchronously.
 */
- (void)advanceToNext;

/**
 * Specifies the source from which this instance will draw its upcoming videos
 * for playback. Note that setting a new source will not automatically send
 * a new playback session on `playbackSessions`; use `-advanceToNext` to send
 * a playback session for the first video in the source.
 *
 * The source is enumerated immediately upon being set and each video element
 * is defensively copied into this queue.
 *
 * @param videos The source of BCOVVideo objects from which this instance
 * should construct a queue for playback. This value is enumerated immediately
 * and its elements are copied.
 */
- (void)setVideos:(id<NSFastEnumeration>)videos;

/**
 * Returns a signal of playback sessions dequeued by this instance. Whenever
 * a session is dequeued (by means of this instance's `-advanceToNext` method),
 * the session is delivered on the returned signal. Sessions may be delivered
 * asynchronously.
 *
 * @return A signal of this instance's playback sessions.
 */
- (RACSignal *)playbackSessions;

@end

