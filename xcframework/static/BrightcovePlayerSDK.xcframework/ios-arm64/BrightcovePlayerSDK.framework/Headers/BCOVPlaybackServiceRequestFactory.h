//
// BCOVPlaybackServiceRequestFactory.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

extern NSString * const kBCOVEdgePlaybackAuthServiceBaseURL;

/**
 * The BCOVPlaybackServiceRequestFactory class provides methods for creating
 * requests for videos from Brightcove’s Playback API.
 */
@interface BCOVPlaybackServiceRequestFactory : NSObject

/**
 * Videocloud Account Id.
 */
@property (nonatomic, copy, readonly) NSString *accountId;

/**
 * Videocloud Policy Key
 */
@property (nonatomic, copy, readonly) NSString *policyKey;

/*
 * Auth Token for EPA/PAS
 */
@property (nonatomic, copy, readonly) NSString *authToken;

/*
 * Base URL for Generic Stream Concurrency
 */
@property (nonatomic, copy, readonly) NSString *gscBaseURLStr;

/**
 * NSDictionary of additional HTTP request headers set on each NSURLRequest.
 * The dictionary key defines the header field name.
 * Header field names are case-insensitive.
 * Both keys and values should be NSStrings.
 * Defaults to nil.
 */
@property (nonatomic, copy, readwrite) NSDictionary *additionalHTTPRequestHeaders;

/**
 * Returns an initialized instance with the specified policy. The base URL
 * string used by the returned instance is https://edge.api.brightcove.com/playback/v1 .
 *
 * If using the Edge Playback Service, the policyKey value should be nil
 *
 * @param accountId A Video Cloud account. Must not be nil.
 * @param policyKey A Video Cloud CMS policy. Must not be nil.
 * @return The initialized BCOVPlaybackServiceRequestFactory.
 */
- (instancetype)initWithAccountId:(NSString *)accountId policyKey:(NSString *)policyKey;

/**
 * Returns an initialized instance with the specified token, account, and base URL string.
 *
 * If using the Edge Playback Service, the policyKey value should be nil
 *
 * @param accountId A Video Cloud account.
 * @param policyKey A Video Cloud CMS policy.
 * @param baseURLStr A string URL to the API.
 * @return The initialized BCOVPlaybackServiceRequestFactory.
 */
- (instancetype)initWithAccountId:(NSString *)accountId policyKey:(NSString *)policyKey  baseURLStr:(NSString *)baseURLStr;

/**
 * Returns an initialized instance with the specified token, account, and base URL string.
 *
 * If using the Edge Playback Service, the policyKey value should be nil
 *
 * @param accountId A Video Cloud account.
 * @param policyKey A Video Cloud CMS policy.
 * @param baseURLStr A string URL to the API.
 * @param authBaseURLStr A string URL to the API that will be used for EPA/PAS requests.
 * @return The initialized BCOVPlaybackServiceRequestFactory.
 */
- (instancetype)initWithAccountId:(NSString *)accountId policyKey:(NSString *)policyKey baseURLStr:(NSString *)baseURLStr  authBaseURLStr:(NSString *)authBaseURLStr;

/**
 * Returns an initialized instance with the specified token, account, and base URL string.
 *
 * If using the Edge Playback Service, the policyKey value should be nil
 *
 * @param accountId A Video Cloud account.
 * @param policyKey A Video Cloud CMS policy.
 * @param baseURLStr A string URL to the API.
 * @param authBaseURLStr A string URL to the API that will be used for EPA/PAS requests.
 * @param gscBaseURLStr A String URL to the API that will be used for Generic Stream Concurrency requests.
 * @return The initialized BCOVPlaybackServiceRequestFactory.
 */
- (instancetype)initWithAccountId:(NSString *)accountId policyKey:(NSString *)policyKey baseURLStr:(NSString *)baseURLStr  authBaseURLStr:(NSString *)authBaseURLStr gscBaseURLStr:(NSString *)gscBaseURLStr NS_DESIGNATED_INITIALIZER;

/**
 * Constructs a request for a playlist by the playlist id.
 *
 * @param playlistId Id of the playlist to request.
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the playlist.
 */
- (NSURLRequest *)requestForPlaylistWithPlaylistID:(NSString *)playlistId parameters:(NSDictionary *)parameters;

/**
 * Constructs a request for a playlist by the playlist id.
 *
 * @param playlistId Id of the playlist to request.
 * @param authToken The authorization token with which to validate the video's license
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the playlist.
 */
- (NSURLRequest *)requestForPlaylistWithPlaylistID:(NSString *)playlistId authToken:(NSString *)authToken parameters:(NSDictionary *)parameters;

/**
 * Constructs a request for a playlist by the reference id.
 *
 * @param referenceId Reference id of the playlist to request.
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the playlist.
 */
- (NSURLRequest *)requestForPlaylistWithReferenceID:(NSString *)referenceId parameters:(NSDictionary *)parameters;

/**
 * Constructs a request for a playlist by the reference id.
 *
 * @param referenceId Reference id of the playlist to request.
 * @param authToken The authorization token with which to validate the video's license
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the playlist.
 */
- (NSURLRequest *)requestForPlaylistWithReferenceID:(NSString *)referenceId authToken:(NSString *)authToken parameters:(NSDictionary *)parameters;

/**
 * Constructs a request for a video by the video id.
 *
 * @param videoId Id of the video to request.
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the video.
 */
- (NSURLRequest *)requestForVideoWithVideoID:(NSString *)videoId parameters:(NSDictionary *)parameters;

/**
 * Constructs a request for a video by the video id.
 *
 * @param videoId Id of the video to request.
 * @param authToken The authorization token with which to validate the video's license
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the video.
 */
- (NSURLRequest *)requestForVideoWithVideoID:(NSString *)videoId authToken:(NSString *)authToken parameters:(NSDictionary *)parameters;

/**
 * Constructs a request for a video by the reference id.
 *
 * @param referenceId Reference id of the video to request.
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the video.
 */
- (NSURLRequest *)requestForVideoWithReferenceID:(NSString *)referenceId parameters:(NSDictionary *)parameters;

/**
 * Constructs a request for a video by the reference id.
 *
 * @param referenceId Reference id of the video to request.
 * @param authToken The authorization token with which to validate the video's license
 * @param parameters parameters that will be added as URL parameters to the request.
 * These parameters will override any default parameters that had been set.
 * @return Built NSURLRequest that can be used to fetch the video.
 */
- (NSURLRequest *)requestForVideoWithReferenceID:(NSString *)referenceId authToken:(NSString *)authToken parameters:(NSDictionary *)parameters;

@end
