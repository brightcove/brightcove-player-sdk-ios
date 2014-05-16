# Brightcove Player SDK for iOS, version 4.1.7.520

Quick Start
===========
Playing video with the Brightcove Player SDK for iOS, in less than 20 lines of code:

    NSString *token;      // (Brightcove Media API token with URL access)
    NSString *playlistID; // (ID of the playlist you wish to use)
    
    BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    id<BCOVPlaybackController> controller = [manager createPlaybackControllerWithViewStrategy:nil];
    [self.view addSubview:controller.view];  
     
    BCOVCatalogService *catalog = [[BCOVCatalogService alloc] initWithToken:token];
    [catalog findPlaylistWithPlaylistID:playlistID
                             parameters:nil
                             completion:^(BCOVPlaylist *playlist,
                                          NSDictionary *jsonResponse,
                                          NSError      *error) {
     
        [controller setVideos:playlist];
        [controller play];
     
    }];

If you're using ARC, you need to keep the controller from being automatically released at the end of the method. A common way to do this is to store a pointer to the controller in an instance variable.

Architectural Overview for v4.1
===============================
![Architectural Overview 1](architecture01.png)

The entry point to the Brightcove Player SDK for iOS is the [`BCOVPlayerSDKManager`][manager] singleton object. This Manager handles registration of plugin components and some other housekeeping tasks, but it primarily serves as an object factory. Your app's view controller obtains a reference to the Manager, and uses it to create a [`BCOVPlaybackController`][controller]. The playback controller's `view` property exposes a UIView containing the AVPlayerLayer object that ultimately presents your video content on the screen. The playback controller also accepts a [`BCOVPlaybackControllerDelegate`][delegate], which you can implement to respond to various video playback events.

The playback controller offers methods and properties to affect playback of the current video. However, internally, the playback controller delegates to a [`BCOVPlaybackSession`][session] object. Playback sessions do the actual work of preparing and playing video content, and contain the video's metadata and AVPlayer. The playback controller has mechanisms to advance from the current playback session to the next playback session, either automatically at the end of a video, or manually with a method call. Once the playback controller has advanced to a new session, the previous session is discarded and cannot be used again.

There are two other elements of the playback controller: a [`BCOVPlaybackSessionProvider`][provider], and a list of [`BCOVPlaybackSessionConsumer`][consumer]s. As the name would suggest, the playback session provider is responsible for creating playback sessions and delivering them to the playback controller. The playback controller then delivers the session to each of the playback session consumers in the list. Both the session provider and session consumer APIs are designed for use by plugin developers, and are not detailed in this document.

In addition to the playback functionality provided by the classes described above, there are a handful of value classes. These are used to hold data specific to the Player SDK for iOS. There are also [`BCOVCatalogService`][catalog] and [`BCOVMediaRequestFactory`][requestfactory], which offer functionality for querying content remotely stored in your Brightcove Video Cloud account. Each of these is described in more detail in its own section below.

[manager]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVPlayerSDKManager.h
[controller]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVPlaybackController.h
[delegate]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVPlaybackController.h#L210-L220
[session]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVPlaybackSession.h
[provider]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVPlaybackSessionProvider.h
[consumer]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVPlaybackController.h#L194-L198
[catalog]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVCatalogService.h
[requestfactory]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/Headers/BCOVMediaRequestFactory.h

What happened to BCOVPlaybackFacade?
-----
Thanks to helpful feedback from our users, we made some changes to streamline the API in the Player SDK. The most obvious change is the deprecation of the `BCOVPlaybackFacade` and `BCOVPlaybackQueue` protocols.

In our original design, we wanted to offer a high-level interface for basic playback functionality without requiring users to have to learn a lot of minutiae about the interaction between components such as BCOVPlaybackQueue. To address this, in v4.0 we had a BCOVPlaybackFacade class. But in developing v4.1, we decided to consolidate methods and state affecting playback sessions to a single point of access, `BCOVPlaybackController`. The playback controller now does everything that was handled by the playback facade in the previous version of the SDK.

The BCOVPlaybackFacade protocol still exists, so most existing code should continue to function as before. However, that protocol has been deprecated, and Xcode will warn you of this (depending on your project's settings). We've moved the methods from BCOVPlaybackQueue to BCOVPlaybackController, so the controller is both for performing operations on the current playback state as well as advancing to the next video in the queue. We recommend updating your code to use playback controllers instead of playback facades, and for the most part you only have to change references from type `id<BCOVPLaybackFacade>` to `id<BCOVPlaybackController>` to make your code fully v4.1-compliant. A search and replace should do the trick. See [CHANGELOG.md][changelog] for further details about the changes in v4.1, and don't hesitate to raise questions or ask us for help on the [Brightcove Native Player SDK mailing list][mailinglist].

[changelog]: https://github.com/brightcove/brightcove-player-sdk-ios/blob/master/CHANGELOG.md
[mailinglist]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

A Word on Subclassing
---------------------
Except where explicitly documented otherwise, none of the classes in the Player SDK for iOS are designed to be subclassed. Creating a subclass of any SDK class that is not explicitly designed to be subclassed, especially any of the value classes, could result in unpredictable behavior.

Values
------
Also known as "model objects", these classes (`BCOVPlaylist`, `BCOVVideo`, `BCOVSource`, `BCOVCuePoint`, `BCOVCuePointCollection`) are used to represent data in the Player SDK for iOS. It is crucial to understand that these data types are treated as *values*, rather than *identities*. By this, we mean that if you have two instances of a value class which have the exact same data, they represent the same idea or value, even though they are technically two different objects at separate memory addresses. In other words, neither SDK code nor your client code should ever use identity comparisons ("pointer equality") with value objects. Instead, each value class implements `-isEqual:` and provides a class-specific equality method overload, either of which should be used instead.

This is bad:

    if (myVideo == session.video) // Could lead to bugs!
    
These are good (and functionally equivalent):

    if ([myVideo isEqualToVideo:session.video])
    if ([myVideo isEqual:session.video])

The internals of the Player SDK for iOS may do such things as memoize values or make defensive copies, so relying on the pointer address to check for equality will end up causing you pain.

Another quality of value classes in the Player SDK for iOS is that they are *immutable*. Once you have an instance of a value, you should not try to subvert this immutability in any way, as it may lead to unpredictable behavior. If in your code you wish to "modify" a value in some fashion, your only recourse is to create a new value. As a convenience to help clients obtain "modified" values, each of the value classes offers an `-update:` method which takes a block that allows you to operate on a mutable copy of the original value.

Here is an example of using this method to create a "modified" version of an existing video object, but with different properties:

    BCOVVideo *video1; // (properties include a key "foo" whose value is "bar")
    BCOVVideo *video2 = [video1 update:^(id<BCOVMutableVideo> mutable) {
        
        mutable.properties = @{ @"foo": @"quux" };
        
    }];
    
	NSLog(@"foo is %@", video1.properties[@"foo"]); // prints "foo is bar"
    NSLog(@"foo is %@", video2.properties[@"foo"]); // prints "foo is quux"
    
    // Both video1 and video2 are still immutable objects:
    video1.properties = otherDictionary; // causes compiler error
    video2.properties = otherDictionary; // causes compiler error


As you can see in the example, `video1` has not been changed by the `-update` method call. Instead, this method returns a copy of `video1`, except with the modifications made in the body of the block. You should never allow the mutable copy to escape the block (such as by assigning it to a `__block` variable), instead use the immutable object returned by the `-update` method after you have made your modifications.

(Thanks to [Jon Sterling][js] for publishing the Objective-C implementation of this pattern.)

[js]: http://www.jonmsterling.com/posts/2012-12-27-a-pattern-for-immutability.html

Catalog
-------
The catalog classes provide functionality for retrieving information about your Brightcove assets via the Brightcove Media API. For most purposes, `BCOVCatalogService` provides sufficient functionality to obtain value class instances from input data such as playlist or video IDs, or reference IDs.

If for some reason you need to customize the request that the catalog sends to the Brightcove Media API, you may find `BCOVMediaRequestFactory` helpful. This utility, which is used by the catalog service, generates parameterized Brightcove Media API NSURLRequest objects, which you can use in your own HTTP communication.

View Strategy
-------------
`BCOVPlaybackController` objects are constructed with a **view strategy**, which allows you, as the client of the SDK, to define the exact UIView object that is returned from the playback controller's `view` property. This is important when using plugins that affect the playback controller's view, such as an advertising plugin that overlays the video view with an ad view. Imagine trying to integrate custom controls with such a plugin: normally, custom controls are just regular UIView objects in the view hierarchy that float above the playback controller's video view. But with an advertising plugin, you generally want the ads to float over your custom controls. How to accomplish this without having in-depth knowledge of the structure of the playback controller's view hierarchy? The solution is to construct a view strategy that composes the video view, your custom controls, and the advertising view in a hierarchy of your choosing. The playback controller will call this view strategy the first time you access its `view` property. The final UIView object returned from the strategy will serve as its view permanently (until the controller is destroyed).

Many apps will have no need to create a view strategy, and can simply pass `nil` when creating a new playback controller. This will create a standard video view in the playback controller. However, for apps that do need the control offered by a view strategy, we provide a more detailed explanation here.

The `BCOVPlaybackControllerViewStrategy` typedef aliases (and documents) this more complex block signature:

    UIView *(^)(UIView *view, id<BCOVPlaybackController> playbackController);

This signature describes an Objective-C block that returns a UIView and takes two parameters: a UIView and a playback controller. The return value is easy to understand: it is the UIView object that you want the playback controller's `view` property to point to. But what about the parameters to the block; what is the UIView that is passed as the first parameter? And why is the playback controller passed as the second parameter?

The first parameter is a UIView that *would* have become the playback controller's `view` property, if your view strategy didn't exist to specify otherwise. To illustrate, you could create a pointless no-op view strategy by implementing the block to return its `view` parameter directly:

    BCOVPlaybackControllerViewStrategy viewStrategy =
            ^ UIView *(UIView *videoView, id<BCOVPlaybackController> playbackController) {

        return videoView;

    };

This has the same effect as passing a `nil` view strategy when creating the playback controller.

The second parameter is the same playback controller object to which the view strategy has been given. Why would the view strategy need to reference its playback controller? In many cases, it probably doesn't, and the second parameter can be safely ignored. But some apps might need a view strategy that adds a session consumer to the playback controller. For example, to update custom controls every time the controller advances to a new playback session, you need to be notified of new sessions. The playback controller is made available in the second parameter to the block, so that the view strategy can add any necessary session consumers.

It is very important not to retain this reference to the playback controller. That is, it is safe to use within the block if you need, but don't try to assign it to a `__block` variable or global variable so that you can access it later. The parameter is passed in only because there is no playback controller reference that can be closed-over within the block at the time the view strategy is defined.

Here's an example of a more sensible view strategy implementation:

    BCOVPlaybackControllerViewStrategy viewStrategy =
            ^(UIView *videoView, id<BCOVPlaybackController> playbackController) {

        // Create some custom controls for the video view,
        // and compose both into a container view.
        UIView<BCOVPlaybackSessionConsumer> *myControlsView = [[MyControlsView alloc] init];
        UIView *controlsAndVideo = [[UIView alloc] init];
        [controlsAndVideo addSubview:videoView];
        [controlsAndVideo addSubview:myControls];

        // Compose the container with an advertising view
        // into another container view.
        UIView<BCOVPlaybackSessionConsumer> *adView = [[SomeAdPluginView alloc] init];
        UIView *adViewAndVideo = [[UIView alloc] init];
        [adViewAndVideo addSubview:controlsAndVideoContainer];
        [adViewAndVideo addSubview:adView];

        [playbackController addSessionConsumer:myControls];
        [playbackController addSessionConsumer:adView];

        // This container view will become `playbackController.view`.
        return adViewAndVideo;

    };

Let's review what this view strategy does in detail: first, it creates a custom controls view that conforms to the `BCOVPlaybackSessionConsumer` protocol. (Note that custom views are not required to conform to this protocol; some other non-view object could have been added as a session consumer instead. This just makes the example easier to follow.) Notice how the view hierarchy is composed in this view strategy block: a container view is created to hold both the video view and the controls. These views are added in an order such that the controls will appear *over* the video view. Next, a container view is created to hold the ad view and the first container view. They are added in an order such that the ad view will appear over the container with the custom controls and video view. Finally, the custom controls and the ad view are registered as session consumers, so that when a new playback session is delivered to the playback controller, these views can subscribe to the appropriate events on the session.

Again, for most use cases it should suffice to not use a view strategy at all. Just add the playback controller's view to a view hierarchy, and compose custom controls on top of it. But for more nuanced cases such as when using certain plugins, it helps to have an opportunity to take control of the composition of the playback controller's view, and that's exactly why you can pass a view strategy to the `BCOVPlayerSDKManager` when creating a new playback controller.

There is one caveat to using a view strategy: you must not access the playback controller's `view` property from within the view strategy block. Since the block is being called *because* the playback controller's `view` property was accessed for the first time, accessing the `view` property again *within* the view strategy block could cause a rip in the fabric of space and time, and your program will crash.

Frequently Asked Questions
==========================
**My content won't load. Is there an easy way to test whether the URL points to a valid video?**

If the content is packaged as MP4, you can paste the URL directly into most web browsers, and the video should play (or download to your filesystem, where you can play it locally). If the content is packaged as HLS, you can use QuickTime Player to test it: select `File -> Open Location…` and paste in the `.m3u8` playlist URL, and the video should play.

**I can hear the audio track playing, but the video freezes for a few seconds sporadically. What's happening?**

This is a common symptom of having called a main thread-only UIKit or AVFoundation method from a non-main thread. If you are using a playback session method that returns a RACSignal, realize that most signals (including all `BCOVPlaybackSession` and `BCOVCatalogService` signals) deliver their values on a background scheduler by default, so you must explicitly deliver them onto the main thread scheduler (using `-[RACSignal deliverOn:]`). The corresponding delegate methods on `BCOVPlaybackControllerDelegate` are always called on the main thread.

**How do I customize the controls?**

The `BCOVPlayerSDKManager` provides a view strategy that creates rudimentary controls for development purposes, but they are not designed for extension or modification. To differentiate your app and ensure a unique user experience, we recommend that you create your own custom controls from scratch. For most cases, you can add the `BCOVPlaybackController.view` to a UIView behind your own custom controls, and implement the `BCOVPlaybackControllerDelegate` methods to update the controls in response to various playback events. If your needs are more complex (such as if you are integrating with an advertising plugin) then you can implement a view strategy as described in the section on view strategies, above.

**How do I retrieve data from the Brightcove Media API for which there is no `BCOVCatalogService` method?**

The catalog service offers methods for the most common Brightcove Media API operations, but there are [other operations][media] available. To leverage them, you will need to issue an HTTP request and then process the response. You can use a standard NSURLRequest to do this, or you can leverage a [3rd-party HTTP API][afnet] if you find that easier. In either case, when you receive the response, you can use a standard JSON parser (like NSJSONSerialization) to convert the response into a NSDictionary, and then construct the appropriate value classes from the data in the NSDictionary.

[media]: http://docs.brightcove.com/en/video-cloud/media/
[afnet]: http://afnetworking.com

**Why do I see a message in the log indicating that no source has been found?**

This message indicates that the default source selection policy can't figure which source to pick. The default policy selects the first source whose `deliveryMethod` is `kBCOVSourceDeliveryHLS` ("HLS"). If no HLS source is found, its fallback behavior will select the first source whose `deliveryMethod` is `kBCOVSourceDeliveryMP4` ("MP4"). If no source with a `deliveryMethod` of "HLS" or "MP4" exists on the video, the policy will select the video's first source (regardless of `deliveryMethod`). If you aren't happy with its selection, you can use `-[BCOVPlayerSDKManager createBasicSessionProviderWithOptions:]` and pass in an instance of `BCOVBasicSessionProviderOptions` with a custom `sourceSelectionPolicy` property set. When creating videos and sources manually, ensure that the sources are created with the appropriate `deliveryMethod`.
