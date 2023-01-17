//
// BCOVFairPlayManager.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//


#import <Foundation/Foundation.h>

@class BCOVVideo;

NS_ASSUME_NONNULL_BEGIN

@interface BCOVFairPlayManager : NSObject

/**
 * Attempts to preload content keys for FairPlay protected videos. Typically
 * a content key for a FairPlay protected video is processed when the video
 * begins playback. By preloading the content key you can improve the playback
 * startup experience for your users.
 *
 * This is only applicable to online videos and will not have any effect on offline videos.
 *
 * @param videos The source of BCOVVideo objects for which content keys
 * will be processed.
*/
+ (void)preloadContentKeysForVideos:(NSArray<BCOVVideo *> *)videos;

@end

NS_ASSUME_NONNULL_END
