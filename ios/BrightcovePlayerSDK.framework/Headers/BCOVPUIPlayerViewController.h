//
// BCOVPUIPlayerViewController.h
// BrightcovePlayerSDK
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVPlaybackController.h>
#import <BrightcovePlayerSDK/BCOVPUIPlayerView.h>

/**
 * A UIViewController that wraps a BCOVPUIPlayerView.
 *
 * This view controller is designed to simplify integration with SwiftUI and other
 * contexts where a proper view controller container is needed for the player view.
 *
 * The view controller automatically:
 * - Sets itself as the presentingViewController for the player view
 * - Provides proper view controller hierarchy for IMA ads and other features
 * - Forwards BCOVPUIPlayerViewDelegate methods to its own delegate
 *
 * For UIKit apps, you can continue using BCOVPUIPlayerView directly.
 * For SwiftUI apps, wrap this view controller in a UIViewControllerRepresentable.
 */
@interface BCOVPUIPlayerViewController : UIViewController <BCOVPUIPlayerViewDelegate>

/**
 * The player view managed by this view controller.
 *
 * Note: The view controller sets itself as playerView.delegate to forward
 * BCOVPUIPlayerViewDelegate callbacks to its own delegate property.
 * Do not modify playerView.delegate directly as it will break the forwarding
 * mechanism. Use the view controller's delegate property instead.
 */
@property (nonatomic, readonly) BCOVPUIPlayerView *playerView;

/**
 * The playback controller associated with the player view.
 * This is a convenience property that forwards to playerView.playbackController.
 */
@property (nonatomic, weak) id<BCOVPlaybackController> playbackController;

/**
 * The content overlay view from the player view.
 * This view is commonly used as the ad container for IMA ads.
 * This is a convenience property that forwards to playerView.contentOverlayView.
 */
@property (nonatomic, readonly) UIView *contentOverlayView;

/**
 * A delegate that conforms to BCOVPUIPlayerViewDelegate.
 * Delegate methods from the player view will be forwarded to this delegate.
 */
@property (nonatomic, weak) id<BCOVPUIPlayerViewDelegate> delegate;

/**
 * Not supported. Use initWithPlaybackController:options:controlsView: instead.
 * Storyboard and XIB instantiation is not supported for this view controller
 * because the playback controller cannot be encoded.
 */
- (instancetype)initWithNibName:(NSString *)nibNameOrNil
                         bundle:(NSBundle *)nibBundleOrNil NS_UNAVAILABLE NS_SWIFT_UNAVAILABLE("Use init(playbackController:options:controlsView:) instead");

/**
 * Not supported. Use initWithPlaybackController:options:controlsView: instead.
 * NSCoding is not supported for this view controller because the playback
 * controller cannot be encoded.
 */
- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE NS_SWIFT_UNAVAILABLE("Use init(playbackController:options:controlsView:) instead");

/**
 * Initializes a BCOVPUIPlayerViewController using default options with the given
 * BCOVPlaybackController.
 *
 * @param playbackController The playback controller used by the player view. This
 * must not be nil.
 *
 * @return Fully initialized player view controller.
 */
- (nonnull instancetype)initWithPlaybackController:(id<BCOVPlaybackController>)playbackController;

/**
 * Initializes a BCOVPUIPlayerViewController using the provided BCOVPUIPlayerViewOptions
 * and BCOVPlaybackController.
 *
 * Note: If options.presentingViewController is set, it will be overridden to use
 * this view controller as the presenting view controller.
 *
 * @param playbackController The playback controller used by the player view. This
 * must not be nil.
 * @param options The options for the player view. If nil, default options will be used.
 *
 * @return Fully initialized player view controller.
 */
- (nonnull instancetype)initWithPlaybackController:(id<BCOVPlaybackController>)playbackController
                                   options:(nullable BCOVPUIPlayerViewOptions *)options;

/**
 * Initializes a BCOVPUIPlayerViewController using the provided BCOVPUIPlayerViewOptions,
 * BCOVPlaybackController and customized BCOVPUIBasicControlView.
 *
 * Note: If options.presentingViewController is set, it will be overridden to use
 * this view controller as the presenting view controller.
 *
 * @param playbackController The playback controller used by the player view. This
 * must not be nil.
 * @param options The options for the player view. If nil, default options will be used.
 * @param controlsView The controls view to use in the player view. If nil, default
 * controls view will be used.
 *
 * @return Fully initialized player view controller.
 */
- (nonnull instancetype)initWithPlaybackController:(id<BCOVPlaybackController>)playbackController
                                   options:(nullable BCOVPUIPlayerViewOptions *)options
                              controlsView:(nullable BCOVPUIBasicControlView *)controlsView NS_DESIGNATED_INITIALIZER;

@end
