//
// BCOVTVControlsView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <BrightcovePlayerSDK/BCOVPlaybackController.h>

@class BCOVTVProgressView, BCOVTVInfoViewController;

/**
 * View that holds all the playback controls
 */
@interface BCOVTVControlsView : UIView<BCOVPlaybackSessionConsumer>

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
 * Set to YES to change the control view's UI to the bumper state.
 */
@property (nonatomic, readwrite) BOOL bumperModeActive;

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
 *  UILabel that displays advertisement info or a Live indicator.
 */
@property (nonatomic, strong, readonly) UILabel *descriptionLabel;

/**
 * UILabel that displays the name of the video
 */
@property (nonatomic, strong, readonly) UILabel *videoNameLabel;

/*
 * Use this property to provide tabs for client-specific content in the playback UI.
 * The order of the view controllers in the array is also the order in which they are inserted in the tab bar.
 * The display tab titles will be taken from the view controllers.
 * Implement -preferredContentSize to provide the desired view size (subject to maximum height constraints).
 * Each view controller should adhere to the BCOVPlaybackSessionConsumer protocol.
 */
@property (nonatomic, strong) NSArray<UIViewController<BCOVPlaybackSessionConsumer> *> *customInfoViewControllers;

@end
