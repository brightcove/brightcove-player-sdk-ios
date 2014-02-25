//
// BCOVPlaybackController.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>

#import "ReactiveCocoa.h"


@class BCOVPlaybackSessionLifecycleEvent;
@class BCOVPlaylist;
@class BCOVSource;
@class BCOVVideo;

@protocol BCOVPlaybackController;
@protocol BCOVPlaybackControllerDelegate;
@protocol BCOVPlaybackSession;
@protocol BCOVPlaybackSessionConsumer;


/**
 * Typedef for a view strategy given to a playback controller to construct its
 * `view` property.
 *
 * A view strategy is simply a block that takes two parameters, a UIView and a
 * BCOVPlaybackController, and returns a UIView. It is used to
 * compose UIView objects to create a view hierarchy that will ultimately be
 * accessible from a BCOVPlaybackController's `view` property. To construct
 * your own view strategy, simply implement a block conforming to this signature
 * and within the block, assemble the view hierarchy as you require. For
 * example, you might want to insert custom controls into the view strategy
 * you use when creating a playback controller:
 *
 *   BCOVPlaybackControllerViewStrategy vs = ^ UIView * (UIView *videoView, id<BCOVPlaybackController> playbackController) {
 *
 *     videoView.frame = myFrame;
 *
 *     MyControlsView *controls = [[MyControlsView alloc] initWithVideoView:videoView];
 *     [playbackController addSessionConsumer:controls];
 *
 *     return controls;
 *
 *   };
 *
 * This example view strategy, when given to a playback controller, will
 * instruct the controller to return the MyControlsView instead of whatever
 * view it would otherwise have returned from its `view` property (that view
 * is the `videoView` parameter to the block). Note how this code adds the
 * MyControlsView object as a session consumer to the session consumer container
 * that is also passed into the block. Not every object will need to be added
 * as a session consumer, but for controls or other views that care about the
 * current playback session, it probably makes sense to conform to the
 * BCOVPlaybackSessionConsumer protocol and pass it in, so as to be able to take
 * action when a new session is delivered.
 *
 * @param view The "original" view that is to be composed by the view this
 * block will return. This will typically be or contain a video playback view.
 * @param playbackController A playback controller for any session consumers that
 * are created within the block and need to be added, so as to receive
 * notification of new playback sessions.
 * @return The UIView which the playback controller should use as its `view`.
 */
typedef UIView *(^BCOVPlaybackControllerViewStrategy)(UIView *view, id<BCOVPlaybackController> playbackController);


/**
 * Protocol adopted by objects that provide playback functionality.
 *
 * Implementations of this formal protocol must support its standard playback
 * operations, but may extend the API to perform additional functions specific
 * to their feature set.
 */
@protocol BCOVPlaybackController <NSObject>

/**
 * Delegate for this BCOVPlaybackController.
 */
@property (nonatomic, assign) id<BCOVPlaybackControllerDelegate> delegate;

/**
 * Whether to advance to the next playback session when its previous playback
 * session sends kBCOVPlaybackSessionLifecycleEventEnd. If this event is sent
 * more than once by a playback session, the subsequent sends are ignored.
 *
 * Defaults to NO.
 *
 * @return True if this queue should send the next session when the previous
 * session sends kBCOVPlaybackSessionLifecycleEventEnd.
 */
@property (nonatomic, assign, getter = isAutoAdvance) BOOL autoAdvance;

/**
 * Whether to begin playing a new playback session as soon as it is received.
 *
 * Defaults to NO.
 *
 * @return Whether to begin playback as soon as a new session is received.
 */
@property (nonatomic, assign, getter = isAutoPlay) BOOL autoPlay;

/**
 * Returns a UIView to present playback in a view hierarchy. The view is reused
 * across all playback sessions sent to this controller.
 *
 * @return A UIView to present playback in a view hierarchy.
 */
@property (nonatomic, readonly, strong) UIView *view;

/**
 * Registers a session consumer with a container, to be notified of new
 * sessions. Added consumers will be retained by this container. If a session
 * already existed in the container at the time of subscription, the specified
 * consumer will be sent the `-consumeSession:` message.
 *
 * @param consumer The session consumer being added to the container.
 */
- (void)addSessionConsumer:(id<BCOVPlaybackSessionConsumer>)consumer;

/**
 * Removes a session consumer from the container. The effect of this is that
 * the container releases its ownership of the consumer, and the consumer will
 * no longer be given new sessions to consume.
 *
 * @param consumer The session consumer being removed from the container.
 */
- (void)removeSessionConsumer:(id<BCOVPlaybackSessionConsumer>)consumer;

/**
 * Specifies that the current playback session's player, as well the player of
 * any subsequent sessions (until this property is set to a different value),
 * should have external playback enabled.
 *
 * @param allowsExternalPlayback Whether players should have external playback
 * enabled.
 */
- (void)setAllowsExternalPlayback:(BOOL)allowsExternalPlayback;

/**
 * Instructs this instance to advance to the next playback session. This has no
 * effect if there are no further playback sessions. Note that the next
 * playback session may be delivered asynchronously.
 */
- (void)advanceToNext;

/**
 * Instructs this instance to play the current session's content. If there is
 * no current session, this method has no effect.
 */
- (void)play;

/**
 * Instructs this instance to pause the current session's content. If the
 * content is already paused, or if no content is playing, this method has no
 * effect.
 */
- (void)pause;

/**
 * Specifies the source from which this instance will draw its upcoming videos
 * for playback. The first playback session will be sent as soon as it becomes
 * available, replacing any current playback session. Playback sessions may be
 * delivered asynchronously.
 *
 * @param videos The source of BCOVVideo objects from which this instance
 * should construct playback sessions.
 */
- (void)setVideos:(id<NSFastEnumeration>)videos;

/**
 * Instructs this instance to resume ad playback. This method has no effect when
 * an ad is already playing, or if no advertising component has been integrated
 * with this playback controller.
 */
- (void)resumeAd;

/**
 * Instructs this instance to pause ad playback. This method has no effect when
 * an ad is already paused, or if no advertising component has been integrated
 * with this playback controller.
 */
- (void)pauseAd;

@end




/**
 * This protocol defines how an object will be notified when the playback 
 * controller starts to process a new playback session.
 */
@protocol BCOVPlaybackSessionConsumer <NSObject>

/**
 * Called when a playback controller starts processing a new playback session.
 *
 * @param session New session
 */
- (void)consumeSession:(id<BCOVPlaybackSession>)session;

@end


/**
 * Methods which may be implemented by delegates of a playback controller.
 * The playback controller delegate protocol offers a simplified API
 * for responding to the various changes and events in the playback
 * sessions generated by controller. If you are comfortable using 
 * ReactiveCocoa's signal API, the signal methods offered by
 * BCOVPlaybackSession offer similar functionality, and with better
 * flexibility. This delegate is intended for clients who do not wish to use
 * signals directly.
 */
@protocol BCOVPlaybackControllerDelegate <NSObject>

@optional

/**
 * Called when the controller advances to a new playback session,
 * which happens when `-advanceToNext` is called. When a delegate is set
 * on a playback controller, this method is called with the most recently
 * advanced-to playback session (where applicable).
 *
 * @param controller The playback controller receiving the new session.
 * @param session The playback session that was advanced.
 */
- (void)playbackController:(id<BCOVPlaybackController>)controller didAdvanceToPlaybackSession:(id<BCOVPlaybackSession>)session;

/**
 * Called when a playback session's duration is updated. When a delegate is set
 * on a playback controller, this method is called with the most recently updated
 * duration for the session. A session duration can change as the media playback
 * continues to load, as it is refined with more precise information.
 *
 * @param controller The playback controller to which this instance serves as delegate.
 * @param session The playback session whose duration changed.
 * @param duration The most recently updated session duration.
 */
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didChangeDuration:(NSTimeInterval)duration;

/**
 * Called when a playback session's external playback active status is updated.
 * When a delegate is set on a playback controller, this method is called with the
 * current external playback active status for the session.
 *
 * @param controller The playback controller to which this instance serves as delegate.
 * @param session The playback session whose external playback status changed.
 * @param externalPlaybackActive Whether external playback is active.
 */
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didChangeExternalPlaybackActive:(BOOL)externalPlaybackActive;

/**
 * Called when a session's playhead passes cue points registered with its video.
 * This will occur regardless of whether the playhead passes the cue point time
 * for standard progress (playback), or seeking (forward or backward) through
 * the media. When a delegate is set on a playback controller, this method will
 * only be called for future cue point events (any events that have already 
 * occurred will not be reported).
 *
 * If multiple cue points are registered to a time or times that fall between
 * the "previous time" and "current time" for a cue point event, all cue points
 * after the "previous time" and before or on "current time" will be included
 * in the cue point collection. Put differently, multiple cue points at the
 * same time are aggregated into a single cue point event whose collection will
 * contain all of those cue points. The most likely scenario in which this
 * would happen is when seeking across a time range that includes multiple cue
 * points (potentially at different times) -- this will result in a single cue
 * point event whose previous time is the point at which seek began, whose
 * current time is the destination of the seek, and whose cue points are all of
 * the cue points whose time fell within that range.
 *
 * The cuePointInfo dictionary will contain the following keys and values for
 * each cue point event:
 *
 *   kBCOVPlaybackSessionEventKeyPreviousTime: the progress interval immediately
 *     preceding the cue points for which this event was received.
 *   kBCOVPlaybackSessionEventKeyCurrentTime: the progress interval on or
 *     immediately after the cue points for which this event was received.
 *   kBCOVPlaybackSessionEventKeyCuePoints: the BCOVCuePointCollection of cue
 *     points for which this event was received.
 *
 * @param controller The playback controller to which this instance serves as delegate.
 * @param session The playback session whose cue points were passed.
 * @param cuePointInfo A dictionary of information about the cue point event.
 */
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didPassCuePoints:(NSDictionary *)cuePointInfo;

/**
 * Called with the playback session's playback progress. As the session's
 * media plays, this method is called periodically with the latest progress
 * interval. When a delegate is set on a playback controller, this method will
 * only be called with progress information that has not yet occurred.
 *
 * @param controller The playback controller to which this instance serves as delegate.
 * @param session The playback session making progress.
 * @param progress The time interval of the session's current playback progress.
 */
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didProgressTo:(NSTimeInterval)progress;

/**
 * Called when a playback session receives a lifecycle event. This method is 
 * called only for lifecycle events that occur after the delegate is set
 * (previous lifecycle events will not be buffered/delivered to the delegate).
 *
 * The lifecycle event types are listed along with the
 * BCOVPlaybackSessionLifecycleEvent class.
 *
 * @param controller The playback controller to which this instance serves as delegate.
 * @param session The playback session whose lifecycle events were received.
 * @param lifecycleEvent The lifecycle event received by the session.
 */
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didReceiveLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)lifecycleEvent;


// Deprecated methods in BCOVPlaybackController
- (RACSignal *)seekToTime:(CMTime)time __attribute((deprecated("Use -[AVPlayer seekToTime:completionHandler:] instead")));

@end




@protocol BCOVPlaybackFacadeDelegate;
@protocol BCOVPlaybackQueue;

__attribute((deprecated("Use BCOVPlaybackController instead")))
@protocol BCOVPlaybackFacade <NSObject>
@property (nonatomic, assign) id<BCOVPlaybackFacadeDelegate> delegate __attribute((deprecated("Use -[BCOVPlaybackController delegate] instead")));
@property (nonatomic, assign, getter = isControlsEnabled) BOOL controlsEnabled __attribute((unavailable("Create custom controls in a BCOVPlaybackController view strategy instead")));
@property (nonatomic, readonly, strong) UIView *view __attribute((deprecated("Use -[BCOVPlaybackController view] instead")));
- (void)advanceToNext __attribute((deprecated("Use -[BCOVPlaybackController advanceToNext] instead")));
- (void)advanceToNextAndPlay __attribute((deprecated("Use -[BCOVPlaybackController advanceToNext] instead")));
- (void)play __attribute((deprecated("Use -[BCOVPlaybackController play] instead")));
- (void)pause __attribute((deprecated("Use -[BCOVPlaybackController pause] instead")));
- (void)setVideos:(id<NSFastEnumeration>)videos __attribute((deprecated("Use -[BCOVPlaybackController setVideos:] instead")));
@property (nonatomic, readonly, strong) id<BCOVPlaybackController> controller __attribute((deprecated("Use BCOVPlaybackController directly instead")));
@property (nonatomic, readonly, strong) id<BCOVPlaybackQueue> queue __attribute((deprecated("Use BCOVPlaybackController directly instead")));
@end




__attribute((deprecated("Conform to BCOVPlaybackControllerDelegate instead")))
@protocol BCOVPlaybackFacadeDelegate <NSObject, BCOVPlaybackControllerDelegate>
@optional
- (void)playbackFacade:(id<BCOVPlaybackFacade>)facade didAdvanceToPlaybackSession:(id<BCOVPlaybackSession>)session __attribute((deprecated("Use -[BCOVPlaybackControllerDelegate playbackController:didAdvanceToPlaybackSession:] instead")));
- (void)playbackFacade:(id<BCOVPlaybackFacade>)facade playbackSession:(id<BCOVPlaybackSession>)session didChangeDuration:(NSTimeInterval)duration __attribute((deprecated("Use -[BCOVPlaybackControllerDelegate playbackController:playbackSession:didChangeDuration:] instead")));
- (void)playbackFacade:(id<BCOVPlaybackFacade>)facade playbackSession:(id<BCOVPlaybackSession>)session didChangeExternalPlaybackActive:(BOOL)externalPlaybackActive __attribute((deprecated("Use -[BCOVPlaybackControllerDelegate playbackController:playbackSession:didChangeExternalPlaybackActive:] instead")));
- (void)playbackFacade:(id<BCOVPlaybackFacade>)facade playbackSession:(id<BCOVPlaybackSession>)session didPassCuePoints:(NSDictionary *)cuePointInfo __attribute((deprecated("Use -[BCOVPlaybackControllerDelegate playbackController:playbackSession:didPassCuePoints:] instead")));
- (void)playbackFacade:(id<BCOVPlaybackFacade>)facade playbackSession:(id<BCOVPlaybackSession>)session didProgressTo:(NSTimeInterval)progress __attribute((deprecated("Use -[BCOVPlaybackControllerDelegate playbackController:playbackSession:didProgressTo:] instead")));
- (void)playbackFacade:(id<BCOVPlaybackFacade>)facade playbackSession:(id<BCOVPlaybackSession>)session didReceiveLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)lifecycleEvent __attribute((deprecated("Use -[BCOVPlaybackControllerDelegate playbackController:playbackSession:didReceiveLifecycleEvent:] instead")));
@end




__attribute((deprecated("Use BCOVPlaybackController instead")))
@protocol BCOVPlaybackQueue <NSObject>
@property (nonatomic, assign, getter = isAutoAdvance) BOOL autoAdvance __attribute((deprecated("Use -[BCOVPlaybackController autoAdvance] instead")));
- (void)advanceToNext __attribute((deprecated("Use -[BCOVPlaybackController advanceToNext] instead")));
- (void)setVideos:(id<NSFastEnumeration>)videos __attribute((deprecated("Use -[BCOVPlaybackController setVideos:] instead")));
- (RACSignal *)playbackSessions __attribute((deprecated("Use -[BCOVPlaybackSessionProvider playbackSessionsForVideos:] instead")));
@end
