//
// BCOVFPSBrightcoveAuthProxy.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import "BCOVFPSComponent.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The key system used by a FairPlay source, if retrieved through Brightcove Player API.
 * BCOVSource.properties:
 *  ...
 *  key_systems: {
 *                "com.apple.fps.1_0": {
 *                                      "key_request_url": "https://fps.brightcove.com/v1/fairplay_session_"
 *                                     }
 *               }
 */
extern NSString * const kBCOVSourceKeySystemFairPlayV1;

/**
 * The key for the key request URL used by a FairPlay source, if retrieved through Brightcove Player API.
 */
extern NSString * const kBCOVSourceKeySystemFairPlayKeyRequestURLKey;

/**
 * Error domain for FairPlay Auth Proxy related errors.
 */
extern NSString * const kBCOVFPSAuthProxyErrorDomain;

/*
 * Request for Application Certificate failed.
 */
extern const NSInteger kBCOVFPSAuthProxyErrorCodeApplicationCertificateRequestFailed;

/*
 * Request for Key failed.
 */
extern const NSInteger kBCOVFPSAuthProxyErrorCodeContentKeyRequestFailed;

/*
 * Key request generation failed.
 */
extern const NSInteger kBCOVFPSAuthProxyErrorCodeContentKeyGenerationFailed;


/**
 * Class responsible for interacting with Brightcove FairPlay services.
 */
@interface BCOVFPSBrightcoveAuthProxy : NSObject <BCOVFPSAuthorizationProxy>

/**
 * The base url for FairPlay related license requests. The default URL points to
 * fps.brightcove.com.
 * If set to nil, the default NSURL pointing at fps.brightcove.com will be re-created.
 */
@property (nonatomic, strong, null_resettable) NSURL *fpsBaseURL;

/**
 * The key request URL for FairPlay related key requests.
 * Normally set to nil, in which case the key request URL
 * will be retrieved from the Video Cloud Playback API response.
 */
@property (nonatomic, strong, nullable) NSURL *keyRequestURL;

/**
 * NSURLSession shared across all network calls to the BCOVFPSBrightcoveAuthProxy.
 * This object is created when the Playback Service is initialized.
 * If you wish to use your own NSURLSession you can set it here.
 * If set to nil, the default NSURLSession will be re-created.
 */
@property (nonatomic, strong, null_resettable) NSURLSession *sharedURLSession;

/**
 * Creates a BCOVFPSAuthorizationProxy to interacts with fps.brightcove.com.
 *
 * @param pubId The publisher id. Must not be nil.
 * @param appId The application id registered with fps.brightcove.com. May be nil
 *              if not using fps.brightcove.com.
 *
 * @return An initialized proxy.
 */
- (nullable instancetype)initWithPublisherId:(nullable NSString *)pubId
                               applicationId:(nullable NSString *)appId
    NS_DESIGNATED_INITIALIZER;

/**
 * Retrieves the Application Certificate. This should be done as soon as possible
 * and should be cached for no longer than 6 hours.
 *
 * @param completionHandler Executed when the request is completed. If applicationCetificate
 *                          is nil, the error will be populated. The block
 *                          will be executed on the main thread.
 */
- (void)retrieveApplicationCertificate:(void (^)(NSData * __nullable applicationCetificate,
                                                 NSError * __nullable error))completionHandler;

@end


@interface BCOVFPSBrightcoveAuthProxy (Unavailable)

- (nullable instancetype)init
    __attribute__((unavailable("Use `-[BCOVFPSBrightcoveAuthProxy initWithApplicationId:publisherId:]` instead.")));

@end


@interface BCOVFPSBrightcoveAuthProxy (Deprecated)

- (nullable instancetype)initWithApplicationId:(NSString *)appId
                                   publisherId:(NSString *)pubId
    __attribute__((deprecated("Use -BCOVFPSBrightcoveAuthProxy initWithPublisherId:applicationId: instead")));

@end

NS_ASSUME_NONNULL_END
