//
// BCOVTVProgressView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>


/**
 * A subclass of UIView that provides a "buffered" track
 * with markers for advertising or generic use, plus an
 * "advertising mode" used to display progress of advertisements.
 */

@interface BCOVTVProgressView : UIView

/**
 * Height of the track area
 * Default value is 10.
 */
@property(nonatomic, readwrite) CGFloat trackHeight;

/**
 * The amount of video progress, in seconds.
 */
@property(nonatomic, readwrite) double progress;

/**
 * The amount of buffer, in seconds.
 */
@property(nonatomic, readwrite) double bufferProgress;

/**
 * The duration (in seconds) that the progress view represents.
 * The default value is 30, but should be set to the length of its associated video.
 * The duration will be set automatically for the progress view installed into
 * the TV Player UI at playerView.controlsView.progressView.
 */
@property (nonatomic, readwrite) double duration;

/**
 * Set to YES to change the progress view's UI to the advertising mode.
 * In advertising mode this hides the buffer indicator and markers,
 * and sets the min/max track colors to advertisingMinimumTrackTintColor
 * and advertisingMaximumTrackTintColor.
 */
@property(nonatomic, readwrite) BOOL advertisingMode;

/**
 * The tint color used for the minimum track area representing normal video progress.
 * The default minimum track color is magenta.
 * Set to nil to restore the default color.
 */
@property(nonatomic) UIColor *minimumTrackTintColor;

/**
 * The tint color used for the maximum track area representing normal video progress.
 * The default advertising minimum track color is dark gray.
 * Set to nil to restore the default color.
 */
@property(nonatomic) UIColor *maximumTrackTintColor;

/**
 * The tint color used for the buffered area.
 * The default buffer track color is white.
 * Set to nil to restore the default color.
 */
@property(nonatomic) UIColor *bufferProgressTintColor;

/**
 * The tint color used for the minimum track area when in advertising mode.
 * This color is also used for ad markers in normal mode.
 * The default advertising minimum track color is yellow.
 * Set to nil to restore the default color.
 */
@property(nonatomic) UIColor *advertisingMinimumTrackTintColor;

/**
 * The tint color used for the maximum track area when in advertising mode.
 * The default advertising minimum track color is dark gray.
 * Set to nil to restore the default color.
 */
@property(nonatomic) UIColor *advertisingMaximumTrackTintColor;

/**
 * Colors used for markers drawn in the track area
 * when no custom marker colors are supplied.
 * Set each color to nil to restore the default color.
 */

/**
 * Ad marker color for the minimum track, the side of the progress view to the left of the current time indicator.
 * The default value (used when minimumTrackMarkerColor is nil) is RGB(0.425, 0.075, 0.26).
 */
@property(nonatomic) UIColor *minimumTrackAdMarkerColor;

/**
 * Ad marker color for the buffer track.
 * The default value (used when bufferTrackMarkerColor is nil) is white.
 */
@property(nonatomic) UIColor *bufferTrackAdMarkerColor;

/**
 * Ad marker color for the maximum track, the far right side of the progress view.
 * The default value (used when bufferTrackMarkerColor is nil) is white.
 */
@property(nonatomic) UIColor *maximumTrackAdMarkerColor;

/**
 * Marker color for the minimum track, the side of the progress view to the left of the current time indicator.
 * The default value (used when minimumTrackMarkerColor is nil) is RGB(0.425, 0.075, 0.26).
 */
@property(nonatomic) UIColor *minimumTrackMarkerColor;

/**
 * Marker color for the buffer track.
 * The default value (used when bufferTrackMarkerColor is nil) is white.
 */
@property(nonatomic) UIColor *bufferTrackMarkerColor;

/**
 * Marker color for the maximum track, the far right side of the progress view.
 * The default value (used when bufferTrackMarkerColor is nil) is white.
 */
@property(nonatomic) UIColor *maximumTrackMarkerColor;

/**
 * Add a marker that will be displayed on the progress view at a specific location.
 * @param position The location (in seconds) in the progress view where the marker should be placed. See the "duration" property for related details.
 * @param duration The duration in seconds represented by the marker; can be set to zero to draw the smallest size marker (a circle).
 * @param isAd YES indicates this marker represents an ad. NO indicates this is a generic marker (drawn in white by default). Generally you should pass NO for this value since ad markers are removed and re-added each time you advance to a new session.
 * @param color A UIColor that will be used to draw the marker. Can be set to nil.
 */
- (void)addMarkerAt:(double)position duration:(double)duration isAd:(BOOL)isAd color:(UIColor *)color;

/**
 * Remove all markers at the specified position.
 * @param position The location in the progress view (in seconds) of the marker to be removed.
 */
- (void)removeMarkerAtPosition:(double)position;

/**
 * Remove all markers from the progress view.
 */
- (void)removeAllMarkers;

/**
 * Remove all generic markers from the progress view.
 */
- (void)removeGenericMarkers;

/**
 * Remove all ad markers from the progress view.
 */
- (void)removeAdMarkers;

@end
