# Using the TV Player UI With The Brightcove Player SDK for tvOS, version 6.13.1.2627

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

The **controls view**, `controlsView`, type `BCOVTVControlsView`, is a subview of the controls fading view. The controls view contains the progress view and its related labels and the Subtitles and Audio buttons. The controls view is also responsible for displaying the `BCOVTVInfoViewController` view controller and the views from `customInfoViewControllers`. All of these controls are shown and hidden together, and generally remain in the same location.

## Siri Remote and Gestures

The Apple Siri Remote is the primary means for controlling video playback on the Apple TV. The Brightcove Native Player SDK uses button presses and gestures on the Siri Remote to manipulate the user interface as described here.

Keep in mind that a "tap" is a touch on the Siri Remote trackpad, while a "click" is when the trackpad is fully depressed.

### Controls and Gestures across Player Types

| Gesture / Button  | Action  | Description |
|:------------- |:---------------:| :-------------|
| Single Tap| Show/hide controls |Toggles the visibility of the TV Player view's  progress view and related controls. When the controls are visible, another single tap will switch to display the current time under the progress indicator, and the video end time in place of the video time remaining.|
| Double Tap| Change video gravity        | Cycle through the three standard video gravity modes: AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill, and AVLayerVideoGravityResize. |
| Single Click |Pause/resume playback|If video is playing, pause video and show controls. If video is paused, resume playback and hide controls.|
| Play/Pause Button | Play/pause video | If the video is playing, this will pause the video and show the progress view. If the top tab bar was visible and the video was playing, it will resume playback and continue to show the top tab bar. If the video was paused, resume playback. Hide the progress view if it was visible. If the top tab bar was visible, continue to show it. |
| Menu Button | Hide top tab bar, or perform default Menu button behavior |If the top tab bar is visible, hide the top tab bar. If the top tab bar is not visible, perform the default Menu button action (return to home screen if not otherwise overridden).|

### Additional Controls and Gestures when using BCOVTVPlayerTypeVOD

| Gesture / Button  | Action  | Description |
|:------------- |:---------------:| :-------------|
| Pan | Timeline scrubbing while paused | If the video is paused and the top tab bar is not showing, panning left and right will seek backward or forward in the video. Resuming playback will play at that new point. If the panning speed is high, then panning will snap back to the starting point when going over it. Slow panning will not snap back, allowing for greater accuracy in setting a precise time. |
| Click and Hold | Fast forward/reverse | Click and hold on the left quarter of the Siri v1 remote track pad, or the left arrow of the Siri v2 remote, to begin fast-rewinding or on the right quarter of the Siri v1 remote track pad, or the right arrow of the Siri v2 remote, to fast-forward. |
| Single Click | Jump forward/backward | Single click on the left quarter of the Siri v1 remote track pad, or the left arrow of the Siri v2 remote to go back 10 seconds. Single click on the right quarter of the Siri v1 remote track pad, or the right arrow of the Siri v2 remote to go forward 10 seconds. Jump forward/backward only works while the video is playing. |

### Additional Controls and Gestures when using BCOVTVPlayerTypeLiveDVR

| Gesture / Button  | Action  | Description |
|:------------- |:---------------:| :-------------|
| Single Click | Seek to Live Edge | Single click on the right quarter of the Siri v1 remote track pad, or the right arrow of the Siri v2 remote to seek to live edge. Seeking to live edge only works while the video is playing. |

## Custom Info View Controllers

The Brightcove Native Player SDK provides the `BCOVTVInfoViewController` class which displays information about the current `BCOVVideo` including title, duration, description and poster image. The `BCOVTVInfoViewController` also includes a "From Beginning" button that seeks to the beginning of the video.

You can provide additional Info View Controllers using the `customInfoViewControllers` property on `BCOVTVControlsView`.

For example:

```
let sample = SampleInfoViewController(playerView: _playerView)
sample.title = "Sample"
sample.preferredContentSize = CGSizeMake(0, 250)

_playerView.controlsView.customInfoViewControllers = [sample]
```

The value you set for the UIViewController's title will be used for the tab that will be used to display the UIViewController's view. You'll also need to set a value for `preferredContentSize` supplying a minimum height for your view (the width value will be ignored).

Your view controllers should adhere to the `BCOVPlaybackSessionConsumer` protocol so they can receive the associated delgate methods. You can find the `BCOVPlaybackSessionConsumer` protocol definition in `BCOVPlaybackController.h`.

### Sample Projects

Please check out our sample apps to see the TV Player View in action, including creation of a custom Info View Controller. Sample apps can be found in github at <https://github.com/BrightcoveOS/ios-player-samples>

## Migrating from BCOVTVTabBarItemView to UIViewController

Brightcove Native Player SDK 6.13.0 introduced a new UI for tvOS. As part of this UI overhaul any usages of `BCOVTVTabBarItemView` need to be converted to a `UIViewController` in order to continue functioning.

Fortunately this can be as easy as creating a new `UIViewController`, copying over any properties and custom methods to the new `UIViewController`. If your view was using the `tabBarItemViewDidAdvanceToPlaybackSession:` method you can use `didAdvanceToPlaybackSession:` instead. Any subviews being added can easily be changed from `addSubview:` to `self.view.addSubview:`.

Similarly you can change `tabBarItemViewWillAppear:`, `tabBarItemViewDidAppear:`, `tabBarItemViewWillDisappear:` and `tabBarItemViewDidDisappear:` to the common `viewWillAppear:`, `viewDidAppear:`, `viewWillDisappear:` and `viewDidDisappear:` methods.

If you did any setup in the `initWithFrame:playerView:` method you can change that to `viewDidLoad`, or if you require access to the `BCOVTVPlayerView` you can create your own `UIViewController` initializer like `init(playerView: BCOVTVPlayerView)`.

Finally by default the view for your `UIViewController`, when displayed, will have a transparent background so you may wish to add a background view or a background color.

Once your views are migrated to view controllers you can then set add them to the `customInfoViewControllers` array on `BCOVTVControlsView`.

Thus the following code:
```
private func createSampleTabBarItemView() {
    guard let playerView, var topTabBarItemViews = playerView.settingsView.topTabBarItemViews else {
        return
    }

    let sampleTabBarItemView = SampleTabBarItemView(size: CGSize.init(width: 620, height: 200), playerView: playerView)

    topTabBarItemViews.append(sampleTabBarItemView)
    playerView.settingsView.topTabBarItemViews = topTabBarItemViews
}
```

Becomes:
```
private func createSampleInfoViewControllers() {
    guard let playerView else {
        return
    }

    let sampleInfoVC = SampleInfoViewController(playerView: playerView)
    sampleInfoVC.preferredContentSize = CGSizeMake(0, 200)

    playerView.controlsView.customInfoViewControllers = [sampleInfoVC]
}
```

## Brightcove Server-Side Ad Insertion (SSAI)

Videos enabled with Brightcove Server-Side Ad Insertion can be presented with the TV Player UI. Ad markers are set in the progress view for each set of midroll ads to let users know when ads will be played.

When an ad is played, the top tab bar is hidden and disabled. The progress view is displayed, and shows the ad count, and time remaining for each ad in the ad pod. The user can pause and play the ad, but otherwise no other gestures are available for controlling the video.

For more information about setting up and using SSAI, see our online guide: [Video Cloud SSAI with the Native Player SDKs][ssai].

## Support

If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at <https://groups.google.com/forum/#!forum/brightcove-native-player-sdks>.

[ssai]: https://sdks.support.brightcove.com/features/implementing-server-side-ads-native-player-sdks.html
[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

