//
// BCOVCatalogService.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//


#import <Foundation/Foundation.h>

#import "BCOVCuePoint.h"
#import "BCOVPlaylist.h"
#import "BCOVSource.h"
#import "BCOVVideo.h"


@class RACSignal;

@class BCOVMediaRequestFactory;


/**
 * The BCCatalog class provides asynchronous methods for retrieving information
 * about videos and playlists from Brightcove’s Media API services.
 */
@interface BCOVCatalogService : NSObject

/**
 * The factory used to construct media API requests
 */
@property (nonatomic, strong, readonly) BCOVMediaRequestFactory *requestFactory;

/**
 * Designated initializer, returns an instance initialized with the
 * specified token. The request factory is created using the token provided.
 *
 * To prevent unauthorized access to the metadata in your account, Video Cloud
 * protects access to the API with tokens that you pass as parameters when
 * making API calls. Like other web-based APIs, tokens are generated for you by
 * Video Cloud and must be protected by you.
 *
 * @param token string containing your Video Cloud Media API token.
 * @return an initialized BCOVCatalogService
 */
- (id)initWithToken:(NSString *)token;

/**
 * Returns an initialized instance using the reqest factory provided.
 *
 * To prevent unauthorized access to the metadata in your account, Video Cloud
 * protects access to the API with tokens that you pass as parameters when
 * making API calls. Like other web-based APIs, tokens are generated for you by
 * Video Cloud and must be protected by you.
 *
 * @param requestFactory Request factory used to create requests
 * @return an initialized BCOVCatalogService
 */
- (id)initWithMediaRequestFactory:(BCOVMediaRequestFactory *)requestFactory;

/**
 * Retrieves a playlist from the Media API service by its playlist ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param playlistID string containing the ID of the playlist to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a BCOVPlaylist as its only value, then
 * completes.
 */
- (RACSignal *)findPlaylistWithPlaylistID:(NSString *)playlistID parameters:(NSDictionary *)parameters;

/**
 * Retrieves playlist data from the Media API service by its playlist ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param playlistID string containing the ID of the playlist to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a JSON dictionary as its only value,
 * then completes. */
- (RACSignal *)findPlaylistDictionaryWithPlaylistID:(NSString *)playlistID parameters:(NSDictionary *)parameters;

/**
 * Retrieves a playlist from the Media API service by its reference ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param referenceID string containing the reference ID of the playlist to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a BCOVPlaylist as its only value, then
 * completes.
 */
- (RACSignal *)findPlaylistWithReferenceID:(NSString *)referenceID parameters:(NSDictionary *)parameters;

/**
 * Retrieves playlist data from the Media API service by its reference ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param referenceID string containing the reference ID of the playlist to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a JSON dictionary as its only value,
 * then completes.
 */
- (RACSignal *)findPlaylistDictionaryWithReferenceID:(NSString *)referenceID parameters:(NSDictionary *)parameters;

/**
 * Retrieves a video from the Media API service by its video ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param videoID string containing the ID of the video to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a BCOVVideo as its only value, then
 * completes.
 */
- (RACSignal *)findVideoWithVideoID:(NSString *)videoID parameters:(NSDictionary *)parameters;

/**
 * Retrieves video data from the Media API service by its video ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param videoID string containing the ID of the video to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a JSON dictionary as its only value,
 * then completes.
 */
- (RACSignal *)findVideoDictionaryWithVideoID:(NSString *)videoID parameters:(NSDictionary *)parameters;

/**
 * Retrieves a video from the Media API service by its reference ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param referenceID string containing the reference ID of the video to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a BCOVVideo as its only value, then
 * completes.
 */
- (RACSignal *)findVideoWithReferenceID:(NSString *)referenceID parameters:(NSDictionary *)parameters;

/**
 * Retrieves video data from the Media API service by its reference ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the delivered error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * delivered error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * The returned signal does not guarantee that it will deliver its values on
 * the main thread scheduler, so if this is a requirement then use -[RACSignal deliverOn:]
 * to deliver the values on the main thread.
 *
 * @param referenceID string containing the reference ID of the video to find.
 * @param parameters Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @return  Returns a signal that sends a JSON dictionary as its only value,
 * then completes.
 */
- (RACSignal *)findVideoDictionaryWithReferenceID:(NSString *)referenceID parameters:(NSDictionary *)parameters;

@end


/**
 * The functionality of the finder methods added in these category methods is
 * similar to the core finder methods in BCOVCatalogService, except that rather
 * than return a signal that delivers the results (or an error), these methods
 * return void but take a block which is called with the results (or an error).
 * If you are comfortable using ReactiveCocoa's signal API, the signal methods
 * offered by BCOVCatalogService offer better flexibility. These category
 * methods are intended for clients who do not wish to use signals directly.
 */
@interface BCOVCatalogService (BCOVImperativeCallbacks)

/**
 * Retrieves a BCOVPlaylist from the Media API service by its playlist ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the callback's error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * callback's error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * @param playlistID The ID of the playlist to find.
 * @param parameters Additional NSString query parameters to add to the Media
 * API requests. These values will override the default values if they conflict.
 * @param completionHandler block which will be invoked when the request
 * finishes. Execution of the completionHandler will occur on the main thread.
 */
- (void)findPlaylistWithPlaylistID:(NSString *)playlistID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

/**
 * Retrieves a BCOVPlaylist from the Media API service by its reference ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the callback's error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * callback's error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * @param referenceID The reference ID of the playlist to find.
 * @param parameters Additional NSString query parameters to add to the Media
 * API requests. These values will override the default values if they conflict.
 * @param completionHandler block which will be invoked when the request
 * finishes. Execution of the completionHandler will occur on the main thread.
 */
- (void)findPlaylistWithReferenceID:(NSString *)referenceID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVPlaylist *playlist, NSDictionary *jsonResponse, NSError *error))completionHandler;

/**
 * Retrieves a BCOVVideo from the Media API service by its video ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the callback's error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * callback's error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * @param videoID The ID of the video to find.
 * @param parameters Additional NSString query parameters to add to the Media
 * API requests. These values will override the default values if they conflict.
 * @param completionHandler block which will be invoked when the request
 * finishes. Execution of the completionHandler will occur on the main thread.
 */
- (void)findVideoWithVideoID:(NSString *)videoID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;

/**
 * Retrieves a BCOVVideo from the Media API service by its reference ID.
 *
 * If the Media API returns a standard JSON-formatted error response, the
 * deserialized response will be the callback's error's `userInfo`.
 *
 * If a JSON parse error occurs, the raw NSData response will be included in the
 * callback's error's `userInfo`, keyed by kBCOVCatalogJSONDeserializationErrorRawDataKey.
 *
 * @param referenceID The reference ID of the video to find.
 * @param parameters Additional NSString query parameters to add to the Media
 * API requests. These values will override the default values if they conflict.
 * @param completionHandler block which will be invoked when the request
 * finishes. Execution of the completionHandler will occur on the main thread.
 */
- (void)findVideoWithReferenceID:(NSString *)referenceID parameters:(NSDictionary *)parameters completion:(void (^)(BCOVVideo *video, NSDictionary *jsonResponse, NSError *error))completionHandler;

@end


@interface BCOVCuePoint (BCOVCatalogService)

/**
 * Initializes a cue point from the JSON dictionary. Properties that don't
 * map to first class properties on cue point are added to the properties
 * dictionary.
 *
 * @param json Dictionary representing the deserialized cuepoint.
 * @return The initialized cue point.
 */
+ (instancetype)cuePointFromJSONDictionary:(NSDictionary *)json;

@end


@interface BCOVPlaylist (BCOVCatalogService)

/**
 * Initializes a playlist from the JSON dictionary. Properties that don't
 * map to first class properties on playlist are added to the properties
 * dictionary.
 *
 * @param json Dictionary representing the deserialized playlist.
 * @return The initialized playlist.
 */
+ (instancetype)playlistFromJSONDictionary:(NSDictionary *)json;

@end


@interface BCOVSource (BCOVCatalogService)

/**
 * Initializes a source from the JSON dictionary. Properties that don't map to
 * first class properties on the source are added to the properties dictionary.
 *
 * @param json Dictionary representing the deserialized source.
 * @return The initialized source.
 */
+ (instancetype)sourceFromJSONDictionary:(NSDictionary *)json;

@end


@interface BCOVVideo (BCOVCatalogService)

/**
 * Initializes a video from the JSON dictionary. Properties that don't
 * map to first class properties on video are added to the properties
 * dictionary.
 *
 * @param json Dictionary representing the deserialized video.
 * @return The initialized video.
 */
+ (instancetype)videoFromJSONDictionary:(NSDictionary *)json;

@end

