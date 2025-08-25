//
// BCOVTVTrackSelectionButton.h
// BrightcovePlayerSDK
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

/**
 * Specialized button used for track selection (audio/text tracks) in tvOS player controls.
 * Provides customizable icon, highlight effects, and visual styling.
 */
@interface BCOVTVTrackSelectionButton : UIButton

/**
 * Label containing the button's icon character.
 * Change the text property to customize the icon displayed.
 */
@property (nonatomic, strong, readonly) UILabel *iconLabel;

/**
 * View displayed when the button is highlighted/focused.
 * Customize backgroundColor and other properties for focus styling.
 */
@property (nonatomic, strong, readonly) UIView *highlightedView;

/**
 * Visual effects view providing blur background effect.
 * Can be customized for different blur styles and appearance.
 */
@property (nonatomic, strong, readonly) UIVisualEffectView *visualEffectsView;

@end