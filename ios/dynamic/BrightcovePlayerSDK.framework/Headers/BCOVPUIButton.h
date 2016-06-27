//
// BCOVPUIButton.h
// BrightcovePlayerSDK
//
// Copyright (c) 2016 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import "BCOVPUICommon.h"


@interface BCOVPUIButton : UIButton

/**
 * Primary and secondary button titles.
 */

/**
 * The primary title is the default title; e.g. the "play" icon for the play button.
 */
@property (nonatomic, copy, readwrite) NSString *primaryTitle;

/**
 * The secondary title is the alternate title; e.g. "pause" for the play button.
 */
@property (nonatomic, copy, readwrite) NSString *secondaryTitle;

/**
 * Show the primary or secondary button title text.
 * @param primary YES displays the primary button title; otherwise the secondary title.
 */
- (void) showPrimaryTitle:(BOOL)primary;

@end
