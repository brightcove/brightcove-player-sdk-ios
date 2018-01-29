//
// BCOVPUIAdControlView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

#import "BCOVPUICommon.h"


@class BCOVPUIButton;

/**
 * Advertising controls view.
 */
@interface BCOVPUIAdControlView : UIView


/**
 * Ad pod information for the current video.
 * These values will be detected and set automatically.
 * We do not recommend changing them.
 */
@property (nonatomic) int adPodCount;
@property (nonatomic) float adPodRemaining;
@property (nonatomic) int adPodIndex;
@property (nonatomic) float adDuration;
@property (nonatomic) float adCurrentTime;
@property (nonatomic) BOOL adIsSkippable;
@property (nonatomic) float adSkipTime;

/** Set to YES to change the Ad Control's UI to the advertising state. */
@property(nonatomic, readwrite) BOOL advertisingMode;

/** Ad pod countdown button */
@property (nonatomic, readonly) BCOVPUIButton *adPodCountdownButton;

/** Learn more button */
@property (nonatomic, readonly) BCOVPUIButton *learnMoreButton;

/** Skip ad countdown button */
@property (nonatomic, readonly) BCOVPUIButton *skipAdCountdownButton;

/** Skip ad button */
@property (nonatomic, readonly) BCOVPUIButton *skipAdButton;

/** Height of control bar area. Used to compute location of controls.
    Should be set whenever control bar height changes. */
@property (nonatomic, readwrite) float controlBarHeight;


/**
 * Show or hide all the standard controls
 *
 * @param show YES to show; NO to hide.
 */
- (void)showControls:(BOOL)show;

/**
 * Enable or disable all the standard controls
 *
 * @param enabled YES to enable; NO to disable.
 */
- (void)enableControls:(BOOL)enabled;

/**
 * Updates all label components with the specified font size.
 *
 * @param fontSize The font size to update components with.
 */
- (void)setFontSizeForControls:(CGFloat)fontSize;

/**
 * Updates all controls with the specified color.
 *
 * @param textColor The color with which to update the control text.
 * @param state Controls state that these changes will apply to.
 */
- (void)setTextColorForControls:(UIColor *)textColor forState:(UIControlState)state;

@end


