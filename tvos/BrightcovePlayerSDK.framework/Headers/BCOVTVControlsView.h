//
// BCOVTVControlsView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

@class BCOVTVProgressView;

/**
 * View that holds all the playback controls
 */
@interface BCOVTVControlsView : UIView

/**
 * Amount by which the controls will be inset from the edge of the TV Player View.
 * Defaults values are (top, left, bottom, right) = (60, 90, 60, 90).
 */
@property (nonatomic) UIEdgeInsets insets;

/**
 * Set to YES to show the clock time in place of the video's current playback time.
 * Is reset to NO each time the controls fading view is hidden.
 */
@property (nonatomic) BOOL showClockTime;

/**
 * Set to YES to change the control view's UI to the advertising state.
 */
@property(nonatomic, readwrite) BOOL advertisingMode;

/**
 * Horizontal indicator showing the progress of the main video or advertisement.
 */
@property (nonatomic, weak, readonly) BCOVTVProgressView *progressView;

/**
 * Thin vertical view that indicates the current playback time on the progress view.
 * Contains an empty subview with a white background.
 * Can be resized and the subview replaced with your own view.
 */
@property (nonatomic, weak, readonly) UIView *currentTimeIndicatorView;

/**
 * UILabel displaying the currently elapsed time in the video, or the current clock time
 * (when showClockTime is YES).
 */
@property (nonatomic, weak, readonly) UILabel *currentTimeLabel;

/**
 * UILabel displaying the remaining time in the video,
 * or the clock time when the video will finish (when showClockTime is YES).
 */
@property (nonatomic, weak, readonly) UILabel *timeRemainingLabel;

/**
 *  UILabel that displays advertisement info, 360 Video, or a Live indicator.
 */
@property (nonatomic, weak, readonly) UILabel *descriptionLabel;

@end
