//
// BCOVTVTabBarItemView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import "BCOVPlaybackController.h"

@class BCOVTVPlayerView;
@protocol BCOVPlaybackSession;


@interface BCOVTVTabBarItemView : UIView <BCOVPlaybackSessionConsumer>

/**
 * When the enabled property is NO, the tab bar item view is not installed into the top tab bar.
 * Use the BCOVTVSettingsView method `- (void)enable:(BOOL)enable tabBarItemView:(BCOVTVTabBarItemView *)tabBarItemView`
 * to simultaneously toggle the `enabled` property and update the top tab bar's list of UITabBarItems.
 */
@property (nonatomic) BOOL enabled;

/**
 * This property is used to set the name of the corresponding UITabBarItem in the top tab bar.
 * The title should be set before installing the tab bar item views into
 * the Settings view's `topTabBarItemViews` property.
 */
@property (nonatomic) NSString *title;

/**
 * This property stores a reference to the TV Player view passed
 * to the `-initWithFrame:playerView:` method.
 */
@property (nonatomic, readonly, weak) BCOVTVPlayerView *playerView;


/**
 * Initialize the BCOVTVTabBarItemView.

 * @param size Size of the new BCOVTVTabBarItemView. The view will be horizontally centered in the tab bar item container view.
 * @param playerView The TV Player view that will contain your new view.
 * @return The newly created BCOVTVTabBarItemView.
 */
- (instancetype)initWithSize:(CGSize)size
                  playerView:(BCOVTVPlayerView *)playerView;

/**
 * Method called when a new session is delivered from the playback controller.
 * Override this method to retrieve information about your video
 * and populate your user interface.
 */
- (void)tabBarItemViewDidAdvanceToPlaybackSession:(id<BCOVPlaybackSession>)session;

/**
 * Notifies the view that it is about to be added to a view hierarchy.
 */
- (void)tabBarItemViewWillAppear:(BOOL)animated;

/**
 * Notifies the view that it was added to a view hierarchy.
 */
- (void)tabBarItemViewDidAppear:(BOOL)animated;

/**
 * Notifies the view that it is about to be removed from a view hierarchy.
 */
- (void)tabBarItemViewWillDisappear:(BOOL)animated;

/**
 * Notifies the view that it was removed from a view hierarchy.
 */
- (void)tabBarItemViewDidDisappear:(BOOL)animated;

/**
 * Called when the trait collection changes which might have changed
 * the system Appearance or Theme setting.
 */
- (void)updateForDarkMode:(BOOL)usingDarkMode;

@end


/**
 * BCOVTVInfoTabBarItemView
 * Class for the "Info" tab bar panel
 * The default view displays basic information taken from the
 * Playback API response. You can override this information
 * manually by setting the text labels and image view when
 * `tabBarItemViewDidAdvanceToPlaybackSession:` is called.
 */
@interface BCOVTVInfoTabBarItemView : BCOVTVTabBarItemView

/**
 * Displays the poster view referenced in the Playback API response.
 */
@property (nonatomic) UIImageView *posterImageView;

/**
 * `titleLabel` displays the "name" property from the Playback API response.
 */
@property (nonatomic) UILabel *titleLabel;

/**
 * `infoLabel` displays the "duration" property from the Playback API response.
 */
@property (nonatomic) UILabel *infoLabel;

/**
 * `descriptionLabel` displays the "long_description" property from the Playback API response.
 */
@property (nonatomic) UILabel *descriptionLabel;

/**
 * `moreButton` appears if the `descriptionLabel` text is too big to fit in the view.
 * When triggered it presents the text as a scrolling UITextView in a new UIViewController
 * using BCOVTVPlayerView.options.presentingViewController as the presenting view controller.
 */
@property (nonatomic) UIButton *moreButton;

/**
 * Returns a new instance of the BCOVTVInfoTabBarItemView class.
 * @param playerView The TV Player View that will contain this tab bar item view.
 */
+ (instancetype)viewWithPlayerView:(BCOVTVPlayerView *)playerView;

@end


/**
 * BCOVTVSubtitlesTabBarItemView
 * Class for the "Subtitles" tab bar panel
 */
@interface BCOVTVSubtitlesTabBarItemView : BCOVTVTabBarItemView

/**
 * Returns YES if the current session contains subtitle tracks.
 */
+ (BOOL)sessionHasSubtitles:(id<BCOVPlaybackSession>)session;

/**
 * Returns a new instance of the BCOVTVSubtitlesTabBarItemView class.
 * @param playerView The TV Player View that will contain this tab bar item view.
 */
+ (instancetype)viewWithPlayerView:(BCOVTVPlayerView *)playerView;

@end


/**
 * BCOVTVAudioTabBarItemView
 * Class for the "Audio" tab bar panel
 */
@interface BCOVTVAudioTabBarItemView : BCOVTVTabBarItemView

/**
 * Returns YES if the current session contains additional audio tracks.
 */
+ (BOOL)sessionHasAdditionalAudioTracks:(id<BCOVPlaybackSession>)session;

/**
 * Returns a new instance of the BCOVTVAudioTabBarItemView class.
 * @param playerView The TV Player View that will contain this tab bar item view.
 */
+ (instancetype)viewWithPlayerView:(BCOVTVPlayerView *)playerView;

@end
