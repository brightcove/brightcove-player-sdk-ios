//
// BCOVTVPlayerView.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVPlaybackController.h>

@class BCOVAd;
@class BCOVTVControlsView;
@class BCOVTVPlayerView;
@class BCOVTVSettingsView;
@protocol BCOVTVAccessibilityDelegate;


/**
 * Enumeration type used when showing or hiding certain control categories
 */
typedef NS_ENUM(NSUInteger, BCOVTVShowViewType) {

    /**
     * None: hide both the controls and settings views
     */
    BCOVTVShowViewTypeNone,
    
    /**
     * VoiceOverEnabledAndPaused:
     */
    BCOVTVShowViewTypeVoiceOverEnabledAndPaused,

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
 * Enumeration type used to determine icon type
 * for certain UI behaviors.
 */
typedef NS_ENUM(NSUInteger, BCOVTVIconType)
{
    /**
     * Icon shown as icon for jump-back
     * Default size is 36x40
     */
    BCOVTVIconTypeJumpBack,
    
    /**
     * Icon shown as icon for jump-foward
     * Default size is 36x40
    */
    BCOVTVIconTypeJumpFoward,
    
    /**
     * Icon shown when rewinding
     * Default size is 32x32
    */
    BCOVTVIconTypeRewind,
    
    /**
     * Icon shown when fast-forwarding
     * Default size is 32x32
    */
    BCOVTVIconTypeFastForward
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

/**
 * Called when the user is attempting to seek or skip over video content. Return
 * YES to prevent seeking and skipping. Return NO to permit seeking and skipping.
 * The default behavior is to allow seeking. Analogous to the requireLinearPlayback
 * property of AVPlayerViewController.
 */
- (BOOL)playerViewShouldRequireLinearPlayback:(BCOVTVPlayerView *)playerView;

/**
 * Called just before the thumbnail preview is set up.
 *
 * You can implement this to customize the thumbnail preview size.
 *
 * If this delegate method is not implemented the size of the thumbnail preview
 * will be 1/5 the size of the playerView.
 *
 * @param playerView The player view that will display the thumbnail preview.
 *
 * @return The width and height the thumbnail should be displayed.
 */
- (CGSize)playerViewShouldDisplayThumbnailPreviewWithSize:(BCOVTVPlayerView *)playerView;

/**
 * Called when a progressView panning gesture (seek) begins.
 *
 * @param progressValue The progress value represented by the pan gesture, passed
 * as a parameter because the progress property of the BCOVTVProgressView does not update
 * until playback resumes.
 *
 * This method is called on the main thread and should not be blocked.
 */
- (void)progressViewPanGestureStateBegan:(NSTimeInterval)progressValue;

/**
 * Called when a progressView panning gesture (seek) changes state (playhead position).
 *
 * @param progressValue The progress value represented by the pan gesture, passed
 * as a parameter because the progress property of the BCOVTVProgressView does not update
 * until playback resumes.
 *
 * This method is called on the main thread and should not be blocked.
 */
- (void)progressViewPanGestureStateChanged:(NSTimeInterval)progressValue;

/**
 * Called when a panning gesture (seek) ends.
 *
 * @param progressValue The progress value represented by the pan gesture, passed
 * as a parameter because the progress property of the BCOVTVProgressView does not update
 * until playback resumes.
 *
 * This method is called on the main thread and should not be blocked.
 */
- (void)progressViewPanGestureStateEnded:(NSTimeInterval)progressValue;

/**
 * Called when fast-forwarding on the player begins.
 */
- (void)playerDidBeginFastForward;

/**
 * Called when fast-forwarding on the player ends.
*/
- (void)playerDidEndFastForward;

/**
 * Called when fast-rewinding on the player begins.
*/
- (void)playerDidBeginFastRewind;

/**
 * Called when fast-rewinding on the player ends.
*/
- (void)playerDidEndFastRewind;

/**
 * Called during video playback.
 *
 * Use this optional delegate method to provide a custom view to indicate to users wether a video is at
 * the live edge or not. If this method is not implemented by your delegate, a default behavior of showing
 * "Live" at the top left of the BCOVTVPlayerView will be displayed, with the "L" tinted green if the video
 * is at the live edge.
 *
 * The view will be added to as a subview inside BCOVTVPlayerView and will be relative to it. A frame with
 * an x, y value of 0 will be positioned at the top left of the view as expected. You may position the view
 * however you like.
 *
 * @param playing Wether or not the video is currently playing
 * @param atLiveEdge Wether or not the video is at the live edge
 *
 * This method is called on the main thread and should not be blocked.
 */
- (UIView *)liveIndicatorViewForIsPlaying:(BOOL)playing atLiveEdge:(BOOL)atLiveEdge;

/**
 * Called prior to displaying an icon for certain UI behaviors.
 *
 * These currently include icons for 'jump-back', 'jump-forward', 'fast-forward' and 'rewind'.
 *
 * You can set your own icon image using this delegate method. You will also need to set the frame of the image
 * and note that its superview is 40x40. You can position the imageView however you'd like inside of the superview
 * while keeping a maximum height and width of 40.
 * Return `YES` if you are overriding the icon, ottherwise return `NO`
 *
 * @param iconType The type of icon tha should be displayed
 * @param imageView The image view that the icon will be displayed in
 *
 * @return A boolean indicating if the default icon should be overriden.
 */
- (BOOL)willDisplayIconType:(BCOVTVIconType)iconType withImageView:(UIImageView *)imageView;

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
 * The jump gesture is invoked by clicking on the left or right edge of the Siri remote trackpad.
 * Defaults to 10 seconds.
 */
@property (nonatomic, assign) NSTimeInterval jumpInterval;

/**
 * The rate at which the AVPlayer will use when fast-forwarding or rewinding is activated by
 * long-pressing on the left or right edge of the Siri remote trackpad.
 * Defaults to 24.
 */
@property (nonatomic, assign) CGFloat fastForwardAndRewindRate;

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

/**
 * Whether to use a language variant, if available, for the
 * video info tab.
 *
 * Defaults to YES
 */
@property (nonatomic, assign) BOOL useLocalizedVariantForVideoInfo;

/**
 * Will automatically select an appropriate BCOVPUIBasicControlView
 * for the current video.
 */
@property (nonatomic, assign) BOOL automaticControlTypeSelection;

@property (nonatomic, weak) id<BCOVTVAccessibilityDelegate> accessibilityDelegate;

/**
 * When enabled, this property will show the bumper controls during playback.
 * Defaults to `YES`.
 */
@property (nonatomic, assign) BOOL showBumperControls;

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
 * settingsControlFocusGuide a UIFocusGuide that allows VoiceOver users
 * to navigate between the settings view to the controls view
 */
@property (nonatomic, strong) UIFocusGuide *settingsControlFocusGuide;


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
