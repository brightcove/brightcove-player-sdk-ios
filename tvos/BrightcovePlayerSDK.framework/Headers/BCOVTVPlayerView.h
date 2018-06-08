//
// BCOVTVPlayerView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVPlaybackController.h>

@class BCOVAd;
@class BCOVTVControlsView;
@class BCOVTVPlayerView;
@class BCOVTVSettingsView;


/**
 * Enumeration type used when showing or hiding certain control categories
 */
typedef NS_ENUM(NSUInteger, BCOVTVShowViewType) {

    /**
     * None: hide both the controls and settings views
     */
    BCOVTVShowViewTypeNone,

    /**
     * Controls: used when hiding the settings view
     * and showing the controls view.
     * This displays the progress view and its related labels,
     * and hides the top tab bar view.
     */
    BCOVTVShowViewTypeControls,

    /**
     * Settings: used when hiding the controls view
     * and showing the settings view.
     * This displays the top tab bar and its related views,
     * and hides the progress view and related labels.
     */
    BCOVTVShowViewTypeSettings
};

/**
 * Enumeration type used to set the type of video playback
 * in the player view.
 */
typedef NS_ENUM(NSUInteger, BCOVTVPlayerType) {
    
    /**
     * Controls and gestures for video-on-demand.
     * This includes advertising controls.
     */
    BCOVTVPlayerTypeVOD,
    
    /**
     * Controls and gestures for live video playback.
     */
    BCOVTVPlayerTypeLive,
    
    /**
     * Controls and gestures for live DVR video playback.
     */
    BCOVTVPlayerTypeLiveDVR
};

/**
 * Conform to this protocol to receive information about the BCOVTVPlayerView.
 */
@protocol BCOVTVPlayerViewDelegate <NSObject>

@optional

/**
 * Called just before the playerView controls fade out.
 *
 * @param playerView The player view that manages the controls.
 * @param controlsFadingView The controls fading view that will fade out.
 */
- (void)playerView:(BCOVTVPlayerView *)playerView controlsFadingViewWillFadeOut:(UIView *)controlsFadingView;

/**
 * Called just before the playerView controls fade in.
*
 * @param playerView The player view that manages the controls.
 * @param controlsFadingView The controls fading view that will fade in.
 */
- (void)playerView:(BCOVTVPlayerView *)playerView controlsFadingViewWillFadeIn:(UIView *)controlsFadingView;

/**
 * Called when the playerView controls have faded out.
 *
 * @param playerView The player view that manages the controls.
 * @param controlsFadingView The controls fading view that faded out.
 */
- (void)playerView:(BCOVTVPlayerView *)playerView controlsFadingViewDidFadeOut:(UIView *)controlsFadingView;

/**
 * Called when the playerView controls have faded in.
 *
 * @param playerView The player view that manages the controls.
 * @param controlsFadingView The controls fading view that faded in.
 */
- (void)playerView:(BCOVTVPlayerView *)playerView controlsFadingViewDidFadeIn:(UIView *)controlsFadingView;

@end


/**
 * Optional configuration for a player view.
 */
@interface BCOVTVPlayerViewOptions : NSObject

/**
 * This view controller will be used for features that require a presenting view
 * controller, like the full-screen controller used to display video description text
 * in the Info settings panel that it too big to fit in the default label.
 */
@property (nonatomic, weak) UIViewController *presentingViewController;

/**
 * The time in seconds to jump back or ahead when the jump backward/forward gesture is invoked.
 * The jump gesture is invoked by double clicking on the left or right edge of the Siri remote trackpad.
 * Defaults to 10 seconds.
 */
@property (nonatomic, assign) NSTimeInterval jumpInterval;

/**
 * The time in seconds since the last touch before fading the controls.
 * Defaults to 3 seconds.
 * See `-resetHideControlsIntervalTimer` for related usage.
 */
@property (nonatomic, assign) NSTimeInterval hideControlsInterval;

/**
 * The time in seconds for animating the hiding of controls.
 * Defaults to 0.5 seconds.
 */
@property (nonatomic, assign) NSTimeInterval hideControlsAnimationDuration;

/**
 * The time in seconds for animating the showing of controls.
 * Defaults to 0.2 seconds.
 */
@property (nonatomic, assign) NSTimeInterval showControlsAnimationDuration;

@end


/**
 * Primary view for displaying video and controls.
 */
@interface BCOVTVPlayerView : UIView

/**
 * The playback controller associated with this player view.
 */
@property (nonatomic, weak) id<BCOVPlaybackController> playbackController;

/**
 * A delegate that conforms to BCOVTVPlayerViewDelegate.
 */
@property (nonatomic, weak) id<BCOVTVPlayerViewDelegate> delegate;

/**
 * The options that were used when creating this BCOVTVPlayerView.
 */
@property (nonatomic, copy, readonly) BCOVTVPlayerViewOptions *options;

/**
 * The video playback configuration: VOD, live, or live DVR.
 * Default value is BCOVTVPlayerTypeVOD.
 */
@property (nonatomic) BCOVTVPlayerType playerType;

/**
 * View that holds the video content.
 */
@property (nonatomic, weak, readonly) UIView *contentContainerView;

/**
 * View intended to contain views that overlay the video content.
 */
@property (nonatomic, weak, readonly) UIView *contentOverlayView;

/**
 * View that contains all controls, static or fading.
 * Set this view's alpha to zero to hide all controls.
 */
@property (nonatomic, weak, readonly) UIView *controlsContainerView;

/**
 * View intended to contain UI elements that should not be
 * faded out/in.
 */
@property (nonatomic, weak, readonly) UIView *controlsStaticView;

/**
 * View intended to contain UI elements that should be
 * faded out/in.
 */
@property (nonatomic, weak, readonly) UIView *controlsFadingView;

/**
 * The visible state of the controlsFadingView.
 * Can be set manually to temporarily show or hide the controls.
 */
@property (nonatomic) BOOL controlsFadingViewVisible;

/**
 * View intended to contain views that should overlay all other views.
 */
@property (nonatomic, weak, readonly) UIView *overlayView;

/**
 * settingsView holds the Info, Audio, and Subtitles settings views
 * in the top tab bar, and is a subview of the controlsStaticView view.
 */
@property (nonatomic, readonly) BCOVTVSettingsView *settingsView;

/**
 * controlsView holds the playback progress controls, and is a subview of the
 * controlsFadingView view.
 */
@property (nonatomic, readonly) BCOVTVControlsView *controlsView;


/**
 * Initialize a new BCOVTVPlayerView object
 *
 * @param options Options passed to create the TV Player View. Can be nil.
 */
- (instancetype)initWithOptions:(BCOVTVPlayerViewOptions *)options
NS_DESIGNATED_INITIALIZER;

/**
 * Manually dim the video view.
 * This method is called automatically whenever the video is paused
 * to make the UI controls more visible.
 *
 * @param dim Pass YES to dim the video view and make controls more visible.
 */
- (void)dimVideoView:(BOOL)dim;

/**
 * Display a specific set of views in the TV Player UI.
 *
 * @param viewType Pass BCOVTVShowViewTypeNone to hide all control views. Pass BCOVTVShowViewTypeControls to display the progress view and its related controls. Pass BCOVTVShowViewTypeSettings to display the top tab bar and its related views.
 */
- (void)showView:(BCOVTVShowViewType)viewType;

/**
 * Manually show or hide the controls fading view.
 * If the view is made visible, it will be hidden automatically after a certain amount of playback time.
 *
 * @param show Pass YES to make the controls fading view visible.
 * @param completion Completion routine called when the fading animation has completed.
 */
- (void)showControlsFadingView:(BOOL)show completion:(void (^)(void))completion;

/**
 * Set the visibility of the top tab bar.
 *
 * @param showTopTabBar Set to YES to make the top tab bar visible.
 */
- (void)showTopTabBar:(BOOL)showTopTabBar;

/**
 * Resets the timer used to keep track of when to hide the controls.
 * If you implement your own controls, you can call this after the user
 * taps on them to prevent the controls from hiding too soon.
 */
- (void)resetHideControlsIntervalTimer;

@end
