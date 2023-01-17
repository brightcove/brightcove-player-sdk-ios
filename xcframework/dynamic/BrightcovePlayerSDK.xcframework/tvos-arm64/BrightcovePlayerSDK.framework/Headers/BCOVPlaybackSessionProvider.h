//
// BCOVPlaybackSessionProvider.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

@protocol BCOVBasicSessionProviderHelperDelegate;

/**
 * Objects that conform to this protocol vend a series of playback sessions
 * that correspond to the specified videos.
 */
@protocol BCOVPlaybackSessionProvider <NSObject>

@end
