//
// BCOVFPSComponent.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <BrightcovePlayerSDK/BCOVPlayerSDKManager.h>
#import <BrightcovePlayerSDK/BCOVFPSAuthorizationProxy.h>

/**
 * Adds methods to BCOVPlayerSDKManager to create FairPlay players and session providers.
 */
@interface BCOVPlayerSDKManager (BCOVFPSAdditions)

/**
 *  Creates and returns a FairPlay enabled playback controller.
 *  If you are using Video Cloud Dynamic Delivery, a Fairplay application certificate will
 *  automatically be retrieved from the BCOVVideo when you play a playlist.
 *  You can still supply an application certificate separately by calling
 *  `BCOVBasicPlaybackController addApplicationCertificate:identifier:`.
 *
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *
 *  @return A playback controller.
 */
- (nonnull id<BCOVPlaybackController>)createFairPlayPlaybackControllerWithAuthorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy;

/**
 *  Creates and returns a FairPlay session provider with the specified parameters.
 *  If you are using Video Cloud Dynamic Delivery, a Fairplay application certificate will
 *  automatically be retrieved from the BCOVVideo when you play a playlist.
 *  You can still supply an application certificate separately by calling
 *  `BCOVBasicPlaybackController addApplicationCertificate:identifier:`.
 *
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *  @param provider And upstream session provider to link to. If nil, a BCOVBasicSessionProvider
 *                  will be used.
 *
 *  @return A session provider.
 */
- (nonnull id<BCOVPlaybackSessionProvider>)createFairPlaySessionProviderWithAuthorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy
                                                                       upstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider;

/**
 *  Creates and returns a FairPlay enabled playback controller.
 *
 *  @param appCert  The Fairplay Application Certificate for this session provider.
 *                  If using Brightcove FPS Server, this can retrieved by
 *                  BCOVFPSBrightcoveAuthProxy. Can be nil.
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *  @param viewStrategy The view strategy to use.
 *
 *  @return A playback controller.
 */
- (nonnull id<BCOVPlaybackController>)createFairPlayPlaybackControllerWithApplicationCertificate:(nullable NSData *)appCert
                                                                              authorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy
                                                                                    viewStrategy:(nullable BCOVPlaybackControllerViewStrategy)viewStrategy;

/**
 *  Creates and returns a FairPlay session provider with the specified parameters.
 *
 *  @param appCert  The FairPlay Application Certificate for this session provider.
 *                  If using Brightcove FPS Server, this can retrieved by
 *                  BCOVFPSBrightcoveAuthProxy. Can be nil.
 *  @param proxy    The BCOVFPSAuthorizationProxy to use for this session provider.
 *                  Must not be nil.
 *  @param provider And upstream session provider to link to. If nil, a BCOVBasicSessionProvider
 *                  will be used.
 *
 *  @return A session provider.
 */
- (nonnull id<BCOVPlaybackSessionProvider>)createFairPlaySessionProviderWithApplicationCertificate:(nullable NSData *)appCert
                                                                                authorizationProxy:(nonnull id<BCOVFPSAuthorizationProxy>)proxy
                                                                           upstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider;

@end

