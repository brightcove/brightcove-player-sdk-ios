//
// BCOVPlayerSDKManager.h
// BCOVPlayerSDK
//
// Copyright (c) 2013 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@protocol BCOVPlaybackController;
@protocol BCOVPlaybackFacade;
@protocol BCOVPlaybackQueue;

@class RACSignal;


/**
 * The Player SDK Manager is a singleton instance that acts as a factory,
 * central registry, and diagnostics center in the Brightcove Player SDK for
 * iOS. After obtaining an instance of the Manager, use it to obtain instances
 * of other objects from the Player SDK ecosystem.
 */
@interface BCOVPlayerSDKManager : NSObject

/**
 * Creates and returns a new playback controller with the specified playback
 * sessions and view frame. When the signal delivers a new playback session,
 * it becomes the controller's "active playback session". The frame parameter is
 * used to set the initial frame of the playback controller's view.
 *
 * @param playbackSessions A signal of playback sessions which is used to
 * update the playback controller's current session.
 * @param frame The initial frame of the returned playback controller's view.
 * @return A new playback controller with the specified playback sessions.
 */
- (id<BCOVPlaybackController>)newPlaybackControllerWithSessions:(RACSignal *)playbackSessions frame:(CGRect)frame;

/**
 * Creates and returns a new fully-configured playback facade object, whose
 * view has the specified frame.
 *
 * @param frame The frame desired for the facade's video view.
 * @return A new playback facade instance whose view has the specified frame.
 */
- (id<BCOVPlaybackFacade>)newPlaybackFacadeWithFrame:(CGRect)frame;

/**
 * Creates and returns a new playback queue.
 *
 * Return A new playback queue.
 */
- (id<BCOVPlaybackQueue>)newPlaybackQueue;

/**
 * Returns the Player SDK Manager singleton.
 *
 * @return The Player SDK Manager singleton.
 */
+ (BCOVPlayerSDKManager *)sharedManager;

@end

