//
// BCOVPlaybackSessionProvider.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>


@class RACSignal;


/**
 * Objects that conform to this protocol vend a cold signal of
 * id<BCOVPlaybackSession> objects, given a id<NSFastEnumeration> of BCOVVideos.
 */
@protocol BCOVPlaybackSessionProvider <NSObject>

/**
 * Returns a cold signal of id<BCOVPlaybackSession> objects that correspond
 * to the specified videos. The first playback session will be sent on the
 * returned signal as soon as it becomes available. Each subsequent playback
 * session will be sent after its previous (leading) playback session is
 * terminated. Playback sessions may be delivered asynchronously.
 *
 * @param videos The BCOVVideo objects to which the returned playback session
 * objects should correspond.
 * @return The BCOVPlaybackSession objects that correspond to the specified
 * videos.
 */
- (RACSignal *)playbackSessionsForVideos:(id<NSFastEnumeration>)videos;

@end
