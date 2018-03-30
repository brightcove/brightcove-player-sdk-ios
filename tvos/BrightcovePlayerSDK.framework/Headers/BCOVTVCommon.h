//
// BCOVTVCommon.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>


@interface BCOVTVCommon : NSObject

/**
 * Color used as a "live" indicator for the stream.
 * Red:0.33 green:0.60 blue:0.25 alpha:1.0
 */
+ (UIColor *)liveViewTitleColorForLive;

/**
 * Default color used by the TV Player progress view maximum track.
 * Red:0.55 green:0.56 blue:0.55 alpha:1.0
 */
+ (UIColor *)progressViewMaximumTrackColor;

/**
 * Default color used by the TV Player progress view minimum track.
 * Red:0.85 green:0.15 blue:0.52 alpha:1.0
 */
+ (UIColor *)progressViewMinimumTrackColor;

/**
 * Default color used by the TV Player progress view buffer track.
 * Red:1.0 green:1.0 blue:1.0 alpha:0.8
 */
+ (UIColor *)progressViewBufferTrackColor;

@end
