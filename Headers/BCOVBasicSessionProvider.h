//
// BCOVBasicSessionProvider.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

#import "BCOVPlaybackSessionProvider.h"


@class BCOVBasicSessionProviderOptions;
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


/**
 * The basic playback session provider provides core functionality to yield
 * playback sessions corresponding to an enumeration of BCOVVideo objects.
 */
@interface BCOVBasicSessionProvider : NSObject <BCOVPlaybackSessionProvider>

/**
 * Returns a basic session provider initialized with the specified options.
 *
 * @param options The options for the session provider to return.
 * @return A basic playback session provider configured with the specified
 * options.
 */
- (id)initWithOptions:(BCOVBasicSessionProviderOptions *)options;

@end


/**
 * Optional configuration for basic session providers.
 */
@interface BCOVBasicSessionProviderOptions : NSObject

/**
 * The default policy selects the first source with a deliveryType of "HLS". If no
 * source is found, it falls back to first source with a deliveryType of
 * "MP4". If neither are found, it returns nil.
 */
@property (nonatomic, copy) BCOVSource *(^sourceSelectionPolicy)(BCOVVideo *video);

@end
