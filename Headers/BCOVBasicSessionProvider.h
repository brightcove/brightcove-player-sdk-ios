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

@end
