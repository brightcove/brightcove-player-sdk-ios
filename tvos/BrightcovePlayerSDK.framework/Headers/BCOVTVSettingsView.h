//
// BCOVTVSettingsView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

@class BCOVTVTabBarItemView;

/**
 * BCOVTVSettingsView
 * View that holds the top tab bar view, and its related top tab bar item views.
 * This view sits inside the BCOVTVPlayerView's controlsStaticView, a static overlay view.
 */
@interface BCOVTVSettingsView : UIView

/**
 Amount by which the controls will be inset from the edge of the TV Player View.
 Defaults values are (top, left, bottom, right) = (60, 90, 60, 90).
 The top tab bar is always pinned to the top edge, but its height will change
 based on the top inset.
 */
@property (nonatomic) UIEdgeInsets insets;

/**
 * This is the primary top tab bar used to select various settings panel views.
 * The default panels (BCOVTVTabBarItemViews) are "Info", "Subtitles", and "Audio".
 * You can add or remove your own BCOVTVTabBarItemView instances in this tab bar
 * by modifying the topTabBarItemViews array.
 */
@property (nonatomic, weak, readonly) UITabBar *topTabBar;

/**
 * This view spans the width of the screen and provides the background to both
 * the top tab bar and the top tab bar item container view.
 * This view gives the "blur effect" background to the top tab bar and
 * all of its related views.
 */
@property (nonatomic, weak, readonly) UIVisualEffectView *topTabBarBackgroundView;

/**
 * This view spans the width of the screen and contains each
 * tab bar item view. Its height automatically resizes to accommodate
 * the height of the currently selected tab bar item view.
 */
@property (nonatomic, weak, readonly) UIView *topTabBarItemContainerView;

/**
 *  This view contains a subview that draws the wide down arrow that
 *  reminds the user that they can swipe down to reveal the top tab bar.
 *  The subview can be replaced with your own view.
 */
@property (nonatomic, weak, readonly) UIView *topTabBarIndicatorView;

/**
 * This focus guide is installed along the bottom edge of the
 * top tab bar item container view. If a tab bar item view is not wide enough
 * to lie directly underneath an item title in the top tab bar, this focus guide
 * will redirect focus to the default focusable item in the currently selected
 * tab bar item view in the top tab bar.
 */
@property (nonatomic, weak, readonly) UIFocusGuide *topTabBarItemContainerViewFocusGuide;

/**
 * The currently selected tab bar item view.
 */
@property (nonatomic, weak, readonly) BCOVTVTabBarItemView *currentTopTabBarItemView;

/**
 * The array of tab bar item views installed in the top tab bar.
 * This array can be read, modified, and then re-assigned as needed.
 */
@property (nonatomic) NSArray<BCOVTVTabBarItemView *> *topTabBarItemViews;

/**
  * Set to YES to change the control view's UI to the advertising state.
 */
@property(nonatomic, readwrite) BOOL advertisingMode;

/**
 * Show or hide the top tab bar view.
 * Do not use this method to show or hide the top tab bar view.
 * Use [BCOVTVPlayerView showTopTabBar:] instead.
 */
- (void)showTopTabBar:(BOOL)show;

/**
 * Enable or disable a tab bar item view in the top tab bar.
 * By default all tab bar item views are enabled when they are
 * created and installed into the top tab bar.
 * Calling `[settingsView enable:NO tabBarItemView:...]` disables the tab bar item view
 * and removes it from the top tab bar, but does not remove it from
 * the array of installed top tab bar item views.
 * Calling `[settingsView enable:YES tabBarItemView:...]` re-enables the tab bar item view
 * and shows it in the top tab bar again
 * This is useful when a tab bar item view has no useful information to display
 * for the current video.
 * @param enable Pass YES to make the tab bar item view visible. NO to hide.
 * @param tabBarItemView The tab bar item view that you wish to show or hide.
 */
- (void)enable:(BOOL)enable tabBarItemView:(BCOVTVTabBarItemView *)tabBarItemView;

@end
