//
// BCOVPUIButton.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVPUICommon.h>

@class BCOVPUIButton;

/**
 * A protocol that allows for users to easily override
 * the defeault values of OOTB control buttons' accessibility labels
 */
@protocol BCOVPUIButtonAccessibilityDelegate <NSObject>

- (NSString *)accessibilityLabelForButton:(BCOVPUIButton *)button isPrimaryState:(BOOL)isPrimaryState;

@end


/**
 * A subclass of UIButton that contains two titles,
 * a primary and a secondary title.
 * This is used for buttons that change titles when they
 * toggle between two different states, like the play/pause button.
 */

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
- (void)showPrimaryTitle:(BOOL)primary;

@property (nonatomic, weak) id<BCOVPUIButtonAccessibilityDelegate> accessibilityDelegate;

@end
