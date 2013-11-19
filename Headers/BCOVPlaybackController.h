//
// BCOVPlaybackController.h
// BCOVPlayerSDK
//
// Copyright (c) 2013 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import <ReactiveCocoa/ReactiveCocoa.h>


@class BCOVPlaylist;
@class BCOVSource;
@class BCOVVideo;


/**
 * Protocol adopted by objects that provide playback functionality.
 *
 * Implementations of this formal protocol must support its standard playback
 * operations, but may extend the API to perform additional functions specific
 * to their feature set.
 */
@protocol BCOVPlaybackController <NSObject>

/**
 * Whether to begin playing a new playback session as soon as it is received.
 *
 * Defaults to NO.
 *
 * @return Whether to begin playback as soon as a new session is received.
 */
@property (nonatomic, assign, getter = isAutoPlay) BOOL autoPlay;

/**
 * Returns a UIView to present playback in a view hierarchy. The view is reused
 * across all playback sessions sent to this controller.
 *
 * @return A UIView to present playback in a view hierarchy.
 */
@property (nonatomic, readonly, strong) UIView *view;

/**
 * Specifies that the current playback session's player, as well the player of
 * any subsequent sessions (until this property is set to a different value),
 * should have external playback enabled.
 *
 * @param allowsExternalPlayback Whether players should have external playback
 * enabled.
 */
- (void)setAllowsExternalPlayback:(BOOL)allowsExternalPlayback;

/**
 * Instructs this instance to play the current session's content. If there is
 * no current session, this method has no effect.
 */
- (void)play;

/**
 * Instructs this instance to pause the current session's content. If the
 * content is already paused, or if no content is playing, this method has no
 * effect.
 */
- (void)pause;

/**
 * Seeks to the specified time in the current session's content, and returns a
 * signal that sends an error if the seek terminates prematurely due to being
 * interrupted by another seek, or sends complete if the seek finishes normally.
 * If your code does not depend on whether the seek prematurely terminates due
 * to being interrupted by another seek, you can disregard the returned signal.
 *
 * @param time The destination time of the seek operation.
 * @return A signal that sends an error if the seek terminates prematurely due
 * to being interrupted by another seek, or sends complete if the seek finishes
 * normally.
 */
- (RACSignal *)seekToTime:(CMTime)time;

@end
