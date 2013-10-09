Brightcove Player SDK for iOS, version 4.0.0.98

Quick Start
===========
A basic Brightcove video player for iOS in 20 lines of code:

	CGRect frame;         // (desired frame of video player view)
	NSString *token;      // (Brightcove Media API token with URL access)
	NSString *playlistID; // (ID of the playlist you wish to use)
	
	BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    id<BCOVPlaybackFacade> facade = [manager newPlaybackFacadeWithFrame:frame];
    [self.view addSubview:facade.view];  
 	
 	BCOVCatalogService *catalog = [[BCOVCatalogService alloc] initWithToken:token];
 	[catalog findPlaylistWithPlaylistID:playlistID
 	                         parameters:nil
 	                         completion:^(BCOVPlaylist *playlist,
 	                                      NSDictionary *jsonResponse,
 	                                      NSError *error) {
 	
 		[facade setVideos:playlist];
 		[facade advanceToNextAndPlay];
 	
 	}];

If you're using ARC, you will need to keep the facade from being automatically released at the end of the method. A common way to do this is to store a pointer to the facade in an instance variable.

Architectural Overview
======================
The Brightcove Player SDK for iOS is designed around the idea of data flowing in a single direction through a pipeline of interchangeable components. You put information about content you wish to play into one end of the pipe, and the information flows through the various segments (components) of the pipe until it comes out the other end. The first component will generally enqueue your content, to be held until it is time for it to begin playing, at which point information about the content is passed along to the next component. Components perform different tasks, such as handling content licensing for DRM, ad insertion, or tracking playback for reporting to analytics systems. Eventually, the content reaches the end of the pipe and is typically presented to the user for playback. Although the word "pipe" is not used as a technical term in our SDK, this is a helpful metaphor to visualize how the SDK is structured and operates.

Components are designed to be used à la carte. One client application may wish to use a playback queue and analytics component but choose not to use a playback controller, whereas another client application may only want to use the catalog service to more easily access the Brightcove Media API. The easiest way to get started is to use the standard assembly of components, provided in the form of a BCOVPlaybackFacade, described later in this document. However, many component combinations are possible.

The Player SDK for iOS is built on top of the [ReactiveCocoa 2.0 framework][RAC], abbreviated as "RAC". ReactiveCocoa is an incredibly powerful tool for managing complexity in heavily event-driven Objective-C code. Although competency with ReactiveCocoa is not required to make basic use of the Player SDK for iOS, it may be helpful to be aware that it is being used internally, and some of the more powerful APIs in the SDK are exposed with ReactiveCocoa concepts. 

[RAC]: https://github.com/ReactiveCocoa/ReactiveCocoa

A Word on Subclassing
---------------------
None of the classes in the Brightcove Player SDK for iOS are designed to be subclassed. Creating a subclass of any SDK class, especially any of the value classes, could result in unpredictable behavior. In short, do not try to subclass any of classes in the SDK at this time.

Player SDK Manager
-------------------
BCOVPlayerSDKManager is a singleton whose functionality at this time consists of vending SDK components to client code. Its use is fairly straightforward. As with most singleton implementations, the manager instance is created lazily when you first access it via the `+sharedManager` method. The manager may log helpful debugging or diagnostic information, so it may be helpful to access it early on in the lifecycle of your application, such as in `-application:didFinishLaunchingWithOptions:`, but this is not a hard requirement.

Playback Facade
---------------
BCOVPlaybackFacade is a high-level assembly of some basic components in a standard configuration. It's an easy way to get started with the Player SDK for iOS, and may meet your needs off-the-shelf. However, custom component assembly or the use of plugins may require you to wire up your own components instead.

The playback facade accepts a delegate using the standard Objective-C delegate pattern, which you can implement to handle the events that occur during playback. For example, to take action when a new playback session is dequeued, you would implement `- (void)playbackFacade:(id<BCOVPlaybackFacade>)facade didDequeuePlaybackSession:(id<BCOVPlaybackSession>)session`.

Values
------
Also known as "model objects", these classes (BCOVPlaylist, BCOVVideo, BCOVSource, BCOVCuePoint, BCOVCuePointCollection) are used to represent data in the Player SDK for iOS. It is crucial to understand that these data types are treated as *values*, rather than *identities*. By this, we mean that if you have two instances of a value class which have the exact same data, they represent the same idea or value, even though they are technically two different objects at separate memory addresses. In other words, neither SDK code nor your client code should ever use identity comparisons ("pointer equality") with value objects. Instead, each value class implements `-isEqual:` and provides a class-specific equality method overload, either of which should be used instead.

This is bad:

    if (myVideo == session.video) // Will probably lead to bugs!
    
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
The catalog classes provide functionality for retrieving information about your Brightcove assets via the Brightcove Media API. For most purposes, the catalog service provides sufficient functionality to obtain value class instances from input data such as playlist or video IDs, or reference IDs. The standard BCOVCatalogService class exposes this functionality with an API that returns ReactiveCocoa signals. If you prefer to use imperative callback blocks instead, import the `BCOVPlaybackFacade.h` file, which adds the corresponding category methods to the catalog service.

If for some reason BCOVCatalogService does not meet your needs, but you still want to use the Brightcove Media API, you may find BCOVMediaRequestFactory helpful. This utility, which is used internally by BCOVCatalogService, generates parameterized Brightcove Media API NSURLRequest objects, which you can use in your own HTTP communication.

Playback Sessions
-----------------
A playback session is used to represent the actual content playback in the Player SDK for iOS. Unlike the value classes, playback sessions can contain mutable state, such as an AVPlayer instance or other collaborators. The primary function of a playback session is to provide event notification to clients about the state of the content playback. For example, when the content has been loaded by the AVPlayer and is ready to be presented onscreen, the playback session sends a "ready" lifecycle event; or when playback crosses over a cue point registered with the session's BCOVVideo object, the playback session sends an event with information about the cue point and the time at which the event occurred.

Playback sessions expose these event notifications in the form of ReactiveCocoa signals (using the RACSignal class). For basic events, you can assign a BCOVPlaybackFacadeDelegate to your playback facade if you are using one, instead of the signal API. However, if you are not using a playback facade, or if you need to subscribe to an event that is not exposed in the BCOVPlaybackFacadeDelegate protocol, you will need to use the signal directly. See the [ReactiveCocoa Documentation][racdocs] for coverage of how to use signals and employ best practices.

[racdocs]: https://github.com/ReactiveCocoa/ReactiveCocoa#new-to-reactivecocoa

Playback Queue
--------------
A playback queue is a holding place for content that is not yet ready for playback. The content is fed into the playback queue in the form of BCOVVideos or a BCOVPlaylist, and the queue creates a playback session for each video. When you wish to obtain the next playback session in the queue, you dequeue it with the `-advanceToNext` method. The act of advancing the playback session removes it from the queue, so this is generally done only when the video is ready to become the "current" video (such as when the previous video is finished playing, or in response to the user clicking a "Next Video" button). There are two things to note here about the behavior of advancing the playback queue:

1. The act of dequeueing a session may occur asynchronously. This means that if you wish to take action immediately after `-advanceToNext` dequeues the next session, you should subscribe to the queue's `playbackSessions` signal.
2. The playback queue may preload the session internally sometime before it is dequeued. However, even if it preloaded, you may not access the session until you dequeue it with `-advanceToNext`.

In a standard configuration of SDK components, there will be one playback queue and one playback controller. (This is effectively the configuration that is used in a playback facade.) The queue can be loaded up with any number of videos, even a very large number. When the queue is advanced, the queue will create a playback session for its first video, and then deliver the playback session to the playback controller. Note that a playback queue may preload the subsequent video in the queue while the previous video is playing, to achieve a smoother transition between videos.

You can set the queue's `autoAdvance` property to `YES`. This will automatically dequeue the next video when the *previous* video sends the `kBCOVPlaybackSessionLifecycleEventEnd` event (indicating that playback reached the end of the video). The very first video must still be manually advanced using the `-advanceToNext` method.

Playback Controller
-------------------
The playback controller is often the last component in the pipeline. This object helps with managing the *current* content, generally the playback session that was just dequeued from a playback queue. The playback controller offers methods for influencing the playback of the video (such as play, pause, and seek). It also manages the details of the session's AVPlayer and AVPlayerLayer, providing convenient access to a UIView object that you can insert directly into your client application's UIView hierarchy for presenting the video content to users.

A playback controller can only operate on one session at a time. Sending a new playback session to the playback controller will replace the session that it was previously controlling, discarding the content.

Controls
--------
A set of basic playback controls are bundled into the playback facade, but if you are not using the facade, or if they do not meet your aesthetic or functional requirements, you will want to build your own controls. To update your controls in response to video playback events, implement the appropriate delegate methods in the playback facade delegate, or subscribe to the signals on each playback session as it is dequeued.

Frequently Asked Questions
==========================
**Why build the Player SDK for iOS on ReactiveCocoa?**

ReactiveCocoa brings enormous powers to  Objective-C developers. The problem domain of video playback involves a highly stateful and complex environment with numerous asynchronous events. ReactiveCocoa helps us tame this complexity, minimize shared mutable state, and maintain clean isolation between different areas of our codebase. A thorough understanding of ReactiveCocoa is not necessary to make use of the basic functionality of the Brightcove Player SDK for iOS, but we do encourage developers to explore what the framework has to offer, and we will continue to develop more sophisticated functionality with its signals-based API and conceptual approach.

**My content won't load. Is there an easy way to test whether the URL points to a valid video?**

If the content is packaged as MP4, you can paste the URL directly into most web browsers, and the video should play (or download to your filesystem, where you can play it locally). If the content is packaged as HLS, you can use QuickTime Player to test it: select `File -> Open Location…` and paste in the `.m3u8` playlist URL, and the video should play.
