# Using the TV Player UI With The Brightcove Player SDK for tvOS, version 6.3.11.455

## Overview
The Brightcove Native Player SDK provides a full set of controls for playback in tvOS on Apple TV known as the TV Player. The TV Player provides playback controls for both regular video content, and video content with Brightcove Server-Side Ad Insertion (SSAI) enabled.

TV Player controls are manipulated through gestures and button presses on the Apple Siri Remote. Controls and gestures are similar to those found in the AVKit interface so they will be familiar to current Apple TV users.

In addition to this reference, it's important to read the documentation for all the methods in each of the TV Player's header files, located in the SDK framework for tvOS. The SDK framework for tvOS can be found alongside the iOS framework in the [Brightcove Player SDK][bcovsdk] repository.

## Quick Start

The following Objective-C code shows how to set up and use the TV Player controls in your own tvOS app.

1 - In your view controller, add a property to hold a reference to the TV Player view. The TV player view is a subclass of UIView that contains both the video player layer where the video is displayed, and the controls overlays.

```
    @property (nonatomic) BCOVTVPlayerView *playerView;

```
2 - In your UI setup code, create the default TV Player view options. You can configure various properties here, such as animation durations, the controls hiding delay, jump interval, and the presenting view controller. The presenting view controller is used to present additional view controllers, such as the view controller created when the Info tab view's description text is too long and has to be displayed in a new view.

```
    BCOVTVPlayerViewOptions *options = [[BCOVTVPlayerViewOptions alloc] init];
    options.presentingViewController = self;
```

3 - Create the TV Player View object, and size it to its container's bounds (videoContainer is your own view). Then add it to the container as a subview.

```
    self.playerView = [[BCOVTVPlayerView alloc] initWithOptions:options];
    self.playerView.frame = self.videoContainer.bounds;
	
    [self.videoContainer addSubview:self.playerView];
```
Apple TV views typically aren't resized, so we don't worry about adding any size constraints.

4 - Create your playback controller, configure it, and assign it to the TV Player view.

```
    id<BCOVPlaybackController> playbackController = [BCOVPlayerSDKManager.sharedManager createPlaybackController];

    playbackController.autoPlay = YES;
    playbackController.delegate = self;

    self.playerView.playbackController = playbackController;
```

Assigning the playbackController links the playback controller to the TV Player view. You can re-use the TV Player view by creating new playback controllers and assigning them to the TV Player view's playbackController property at any time.

## Architecture
The TV Player view class `BCOVTVPlayerView` is a `UIView` subclass that creates a hierarchy of subviews when instantiated. Each of its important subviews is referenced as a property inside the TV Player view.

At the top level, there is the video **content container view**, `contentContainerView`. This view contains the AVPlayerLayer that displays the actual video.

In front of the video content container is the **controls container view**, `controlsContainerView`. This view holds all of the control views, whether or not they are interactive.

In front of the controls container view is the **overlay view**, `overlayView`. This view can be used to present any other overlays over the video and controls.

The controls container view contains two immediate subviews to organize its content. One subview is the **controls static view**, `controlsStaticView`. This view is never hidden automatically. Any control items in this view are either moved off-screen, or manually hidden by setting alpha to zero when not needed.

The other view is the **controls fading view**, `controlsFadingView`. This view is shown on-demand and hidden after a set period by a timer.

The **settings view**, `settingsView`, type `BCOVTVSettingsView`, is a subview of the controls static view. The settings view contains the top tab bar view, which is moved on/off screen as needed. The top tab bar item manages tab bar item views (`BCOVTVTabBarItemView`) which are also added to this view. These are the views that present the **Info**, **Subtitles**, and **Sound** panels.

The **controls view**, `controlsView`, type `BCOVTVControlsView`, is a subview of the controls fading view. The controls view contains the progress view and its related labels. All of these controls are shown and hidden together, and generally remain in the same location.

## Siri Remote and Gestures
The Apple Siri Remote is the primary means for controlling video playback on the Apple TV. The Brightcove Native Player SDK uses button presses and gestures on the Siri Remote to manipulate the user interface as described here.

Keep in mind that a "tap" is a touch on the Siri Remote trackpad, while a "click" is when the trackpad is fully depressed.

| Gesture / Button  | Action  | Description |
|:------------- |:---------------:| :-------------|
| Single Tap| Show/hide controls |Toggles the visibility of the TV Player view's  progress view and related controls. When the controls are visible, another single tap will switch to display the current time under the progress indicator, and the video end time in place of the video time remaining.|
| Double Tap| Change video gravity        | Cycle through the three standard video gravity modes: AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill, and AVLayerVideoGravityResize. |
| Single Click |Pause/resume playback|If video is playing, pause video and show controls. If video is paused, resume playback and hide controls.|
| Swipe Down |Show top tab bar|Show the top tab bar and hide the progress view.|
| Swipe Up | Hide top tab bar | If the top tab bar is visible, and focus is on the tab bar button, swiping up will hide the top tab bar. |
| Pan | Timeline scrubbing while paused | If the video is paused and the top tab bar is not showing, panning left and right will seek backward or forward in the video. Resuming playback will play at that new point. If the panning speed is high, then panning will snap back to the starting point when going over it. Slow panning will not snap back, allowing for greater accuracy in setting a precise time. |
| Play/Pause Button | Play/pause video | If the video is playing, this will pause the video and show the progress view. If the top tab bar was visible and the video was playing, it will resume playback and continue to show the top tab bar. If the video was paused, resume playback. Hide the progress view if it was visible. If the top tab bar was visible, continue to show it. |
| Menu Button | Hide top tab bar, or perform default Menu button behavior |If the top tab bar is visible, hide the top tab bar. If the top tab bar is not visible, perform the default Menu button action (return to home screen if not otherwise overridden).|
| Click and Hold + Pan | Fast forward/reverse | Click and hold, then pan left/right to fast forward and reverse. The longer you click, the faster you can move, up to a limit. The video will seek to the current scrubbing location every 3 seconds to provide a preview of the video at the new time. Previews are only shown while scrubbing if there are no ads. |
| Double Click | Jump forward/backward | Double click on the left quarter of the Siri remote track pad to go back 10 seconds. Double click on the right quarter of the Siri remote track pad to go forward 10 seconds. Jump forward/backward only works while the video is playing. |

## Tab Bar Item Views
By default, the TV Player view contains a top tab bar with three default tab bar items:

- **Info**
- **Subtitles**
-  **Audio**

Each tab bar item view is a subclass of `BCOVTVTabBarItemView`. For example, the Info view is of type `BCOVTVInfoTabBarItemView`, and contains various properties for its labels and image view.

You can modify the text labels in the Info view to better describe your video. You can also resize the Info view and add your own items along the bottom of the view (such as chapter markers) using standard UIKit methods.

### Creating Your Own Tab Bar Item Views

In most cases, it is probably best to create your own subclass of `BCOVTVTabBarItemView` that contains exactly the controls, images, and views that you need. To do, this create a subclass of `BCOVTVTabBarItemView` that implements the following methods:

```
- (instancetype)initWithFrame:(CGRect)frame
                   playerView:(BCOVTVPlayerView *)playerView;
```
The `initWithFrame:playerView:` initializer is a good place to set up your views and perform initial allocations. Although it can be set at any time, this is a good place to set the `title` property that determines how your view will be displayed in the top tab bar.

```
- (void)tabBarItemViewDidAdvanceToPlaybackSession:(id<BCOVPlaybackSession>)session;
```
`tabBarItemViewDidAdvanceToPlaybackSession:` is called when a `BCOVPlaybackSession` is ready to begin playing a video. This is the best place to populate your view with data from the new session.

The following four methods are similar to the methods called on a UIViewController when a UIView is about to be shown in a UIViewController. Unlike with UIKit, you do **not** need to call the corresponding `super` method inside each one.

```
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
```

You can implement these calls to modify your UI as necessary at those specific times.

In your user interface, you can create controls and assign your subclass instance as the receiver of the action when the control is triggered. Focus will be moved to your controls through user action, similar to any other tvOS user interface.

If you need to close the top tab bar after an action has occurred, you can do the following:

```
    // Don't hide the tab bar in the middle of handling a button tap
    dispatch_async(dispatch_get_main_queue(), ^{

        [self.playerView showView:BCOVShowHandlerViewTypeNone];

    });
```

As shown here, if you are in the middle of receiving an action, it's best to defer hiding the top tab bar until you have left the call stack of the current code by dispatching asynchronously to the main thread.

1. To help the Focus Engine find your controls, the `BCOVTVTabBarItemView`'s superview has a focus guide running along its entire bottom edge. This focus guide moves focus to the `BCOVTVTabBarItemView`. This is particularly helpful if the top tab bar's button item is not directly above your `BCOVTVTabBarItemView`. You may still need focus guides within your own view if items are placed irregularly, and can't be reached with normal focus navigation.

Since the `BCOVTVTabBarItemView`'s superview has a focus guide along the bottom edge, moving down from the last focusable control in your view will cause focus to move back to your default focusable item. If you want to prevent this, you can implement this `UIFocusEnvironment` protocol method in your subclass:

```
- (BOOL)shouldUpdateFocusInContext:(UIFocusUpdateContext *)context
```

You can compare `context.previouslyFocusedItem` and `context.nextFocusedItem` to the items in your view, returning `NO` if they result in wrapping from the bottom to the top of your view.

### Using Your Own Tab Bar Item Views

Once you have created your own `BCOVTVTabBarItemView` subclass instance, you can install it either by adding it to the current list of tab bar item views, or by replacing one of the existing views.

The following Objective-C code shows how you might add a new subclass instance to the top tab bar. The list of tab bar item views is a simple array, so you can manipulate it as you would any other array.

```
    // Create new instance of your subclass
    MyTabBarItemView *myTabBarItemView = [[MyTabBarItemView alloc] initWithFrame:CGRectMake(0, 0, 600, 480) playerView:self.playerView];

    // Get copy of current tab bar item views
    NSMutableArray *tabBarItemViews = self.playerView.settingsView.topTabBarItemViews.mutableCopy;

    // Add your view to the end of the list of tab bar item views
    [tabBarItemViews addObject:myTabBarItemView];

    // Set the new arras in the TV Player View
    self.playerView.settingsView.topTabBarItemViews = tabBarItemViews;
```

As an alternate approach, after creating your subclass instance, you can create new instances of the other standard tab bar item views, and pick the ones you want to appear in the top tab bar. One way to replace the default Info tab bar item view is shown here:


```
    // Create new instance of your subclass
    MyTabBarItemView *myTabBarItemView = [[MyTabBarItemView alloc] initWithFrame:CGRectMake(0, 0, 600, 480) playerView:self.playerView];

    // Create the standard "Subtitles" and "Audio" tab bar item views
    BCOVTVTabBarItemView *subtitlesTabBarItemView = [BCOVTVSubtitlesTabBarItemView viewWithPlayerView:self];
    BCOVTVTabBarItemView *audioTabBarItemView = [BCOVTVAudioTabBarItemView viewWithPlayerView:self];

    // Create an array of tab bar item views, with your custom view
    // in place of the normal "Info" tab bar item view
    NSArray<BCOVTVTabBarItemView *> *topTabBarItemViews = @[ myTabBarItemView, subtitlesTabBarItemView, audioTabBarItemView ];

    // Set the new array in the TV Player View
    self.playerView.settingsView.topTabBarItemViews = topTabBarItemViews;
```

Once the array is installed, the new tab bar item views will automatically be presented, and the focus engine will send focus to your view according to user input.

### Sample Projects


Please check out our sample apps to see the TV Player View in action, including modification of the default Info view, and the creation of a custom `BCOVTVTabBarItemView` subclass. Sample apps can be found in github at <https://github.com/BrightcoveOS/ios-player-samples>

Brightcove Server-Side Ad Insertion (SSAI)
----------------
Videos enabled with Brightcove Server-Side Ad Insertion can be presented with the TV Player UI. Ad markers are set in the progress view for each set of midroll ads to let users know when ads will be played.

When an ad is played, the top tab bar is hidden and disabled. The progress view is displayed, and shows the ad count, and time remaining for each ad in the ad pod. The user can pause and play the ad, but otherwise no other gestures are available for controlling the video.

For more information about setting up and using SSAI, see our online guide: [Video Cloud SSAI with the Native Player SDKs][ssai].

Support
----------------
If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at <https://groups.google.com/forum/#!forum/brightcove-native-player-sdks>.

[ssai]: https://support.brightcove.com/video-cloud-ssai-native-player-sdks
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

