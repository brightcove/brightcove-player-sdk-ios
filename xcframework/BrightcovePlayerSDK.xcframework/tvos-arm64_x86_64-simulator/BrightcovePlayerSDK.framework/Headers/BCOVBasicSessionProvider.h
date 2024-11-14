//
// BCOVBasicSessionProvider.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

@class BCOVSource;
@class BCOVVideo;

/**
 * Each time a new video is ready to be loaded into a playback session, this
 * block is called and the video is passed in. The block must return a source,
 * which will be used to configure the AVPlayer of the playback session.
 * If the block returns nil, the session provider will not deliver this session
 * and will move on to the next session.
 *
 * @param video The video from which a source is chosen.
 * @return The source to be used by the playback session.
 */
typedef BCOVSource *(^BCOVBasicSessionProviderSourceSelectionPolicy)(BCOVVideo *video);
