//
// BCOVFPSAuthorizationProxy.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

@class BCOVBasicSessionProviderOptions;
@class BCOVSource;
@class BCOVVideo;


/**
 * Error domain for FairPlay related errors.
 */
extern NSString * __nonnull const kBCOVFPSErrorDomain;

/**
 *  Error occured requesting content key.
 */
extern const NSInteger kBCOVFPSErrorCodeStreamingContentKeyRequest;

/**
 *  Error occured requesting application certificate.
 */
extern const NSInteger kBCOVFPSErrorCodeApplicationCertificateRequest;


/**
 *  Implement this protocol when interacting with a custom FPS license server.
 */
@protocol BCOVFPSAuthorizationProxy <NSObject>

@optional

/**
 *  Optional method.
 *  Implement this method to handle retrieving the content identifier from the loading request.
 *  This is called for each asset.
 *  No guarantee is made as to the thread that this is called on.
 *  You should return the content identifier corresponding to this loading request.
 *  This is typically extracted from the "skd://..." URL in loadingRequest.request.URL.
 *  The content identifier will be passed to [AVAssetResourceLoadingRequest
 *  streamingContentKeyRequestDataForApp:contentIdentifier:options:error:]
 *  to retrieve the SPC.
 *
 *  If this method is not provided, the default method will be used. The default method
 *  removes "skd://" from loadingRequest.request.URL to generate the content identifier.
 *
 *  @param loadingRequest The skd:// loading request made for the asset.
 */
- (nullable NSData *)contentIdentifierFromLoadingRequest:(nonnull AVAssetResourceLoadingRequest *)loadingRequest;

@required

/**
 *  Implement this method to handle retrieving the content key. This is called for each asset.
 *  No guarantee is made as to the thread that this is called on.
 *
 *  @param loadingRequest    The "skd://..." loading request made for the asset.
 *  @param keyRequest        The key request data returned by [AVAssetResourceLoadingRequest streamingContentKeyRequestDataForApp:contentIdentifier:options:error:].
 *  @param source            The BCOVSource used to make this request
 *  @param completionHandler The completion handler to return the content key. If returning an error, you must leave the contentkey and response parameters nil.
 */
- (void)encryptedContentKeyForLoadingRequest:(nonnull AVAssetResourceLoadingRequest *)loadingRequest
                           contentKeyRequest:(nonnull NSData *)keyRequest
                                      source:(nonnull BCOVSource *)source
                           completionHandler:(nonnull void (^)(NSURLResponse * __nullable response,
                                                               NSData * __nullable contentKey,
                                                               NSError * __nullable error))completionHandler;

@optional

/**
 *  Implement this method to handle retrieving the content key for a video that
 *  is being downloaded for offline playback. This is called for each asset.
 *  No guarantee is made as to the thread that this is called on.
 *
 *  @param contentKeyIdentifier    The "skd://..." loading request URL string made for the asset.
 *  @param keyRequest        The key request data returned by [AVAssetResourceLoadingRequest streamingContentKeyRequestDataForApp:contentIdentifier:options:error:].
 *  @param source            The BCOVSource used to make this request
 *  @param options           The parameters originally passed to `-BCOVOfflineVideoManager requestVideoDownload:parameters:completion:`
 *  @param completionHandler The completion handler to return the content key. If returning an error, you must leave the contentkey and response parameters nil.
 */
- (void)encryptedContentKeyForContentKeyIdentifier:(nonnull NSString *)contentKeyIdentifier // the "skd://..." url string
                                 contentKeyRequest:(nonnull NSData *)keyRequest
                                            source:(nonnull BCOVSource *)source
                                           options:(nullable NSDictionary *)options
                                 completionHandler:(nonnull void (^)(NSURLResponse * __nullable response,
                                                                     NSData * __nullable contentKey,
                                                                     NSError * __nullable error))completionHandler;

@end
