//
// BCOVSSComponent.h
// BrightcovePlayerSDK
//
// Copyright (c) 2018 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

#import <BrightcovePlayerSDK/BrightcovePlayerSDK.h>

@class BCOVSSSessionProviderOption;


/**
 * @constant kBCOVSSVideoPropertiesKeyTextTracks
 * @abstract The key for an NSArray of text track NSDictionarys.
 * @discussion If videos are retreieved through the BCOVPlaybackService and those
 * videos have text tracks assosiated with them, the plugin will handle those
 * automatically.
 *
 * If you are generating your BCOVVideos manually, you will need to construct
 * a text track dictionary that should includes the following key value
 * pair kBCOVSSTextTracksKeySource, kBCOVSSTextTracksKeySourceLanguage,
 * kBCOVSSTextTracksKeyLabel, kBCOVSSTextTracksKeyDuration,
 * kBCOVSSTextTracksKeyKind, kBCOVSSTextTracksKeyDefault,
 * kBCOVSSTextTracksKeyMIMEType.
 *
 * Example:
 * @code
 *  kBCOVSSVideoPropertiesKeyTextTracks: @[
 *      @{
 *          kBCOVSSTextTracksKeySource: ..., // required
 *          kBCOVSSTextTracksKeySourceLanguage: ..., // required
 *          kBCOVSSTextTracksKeyLabel: ..., // required
 *          kBCOVSSTextTracksKeyDuration: ..., // required/optional
 *          kBCOVSSTextTracksKeyKind: kBCOVSSTextTracksKindSubtitles or kBCOVSSTextTracksKindCaptions, // required
 *          kBCOVSSTextTracksKeyDefault: ..., // optional
 *          kBCOVSSTextTracksKeyMIMEType: ..., // optional
 *      }
 *      @{...}, // second text track dictionary
 *      @{...}, // third text track dictionary
 *      ...
 * ]
 */
extern NSString * const kBCOVSSVideoPropertiesKeyTextTracks;

/**
 * @constant kBCOVSSTextTracksKeySource
 * @abstract The key for the NSString URL to the text track.
 * @discussion This key is required. Text track source can be either an M3U8
 * subtitle playlist or a WebVTT file. WebVTT URLs should have a ".vtt"
 * extension, and M3U8 playlist files should have an "m3u8" extension.
 * If your URL cannot follow this convention, you need to specify the
 * format of the file referenced by your URL with the 
 * kBCOVSSTextTracksKeySourceType key.
 */
extern NSString * const kBCOVSSTextTracksKeySource;

/**
 * @constant kBCOVSSTextTracksKeySourceLanguage
 * @abstract The key for the NSString language of the text track.
 * @discussion This key is required.
 */
extern NSString * const kBCOVSSTextTracksKeySourceLanguage;

/**
 * @constant kBCOVSSTextTracksKeyLabel
 * @abstract The key for the NSString name of the text track.
 * @discussion This key is required.
 */
extern NSString * const kBCOVSSTextTracksKeyLabel;

/**
 * @constant kBCOVSSTextTracksKeyDuration
 * @abstract The key for the NSNumber of Integer value for duration of the text_track.
 * @discussion If the text track source is a .vtt file, the duration of the .vtt file
 * is required in order for subtitles to be displayed. If the video and
 * .vtt file were retrieved through BCOVPlaybackService, the plugin will
 * the attempt to use the video properties value keyed by "duration" to satisfy
 * this requirement. If building videos manually, this key is required. If text
 * track is .m3u8, this key will be ignored.
 */
extern NSString * const kBCOVSSTextTracksKeyDuration;

/**
 * @constant kBCOVSSTextTracksKeyDefault
 * @abstract The key for the NSNumber of BOOL that indicates if the text track
 * is the default.
 * @discussion This key is optional.
 */
extern NSString * const kBCOVSSTextTracksKeyDefault;

/**
 * @constant kBCOVSSTextTracksKeyMIMEType
 * @abstract The key for the NSString mime type of the text track.
 * @discussion This key is optional.
 */
extern NSString * const kBCOVSSTextTracksKeyMIMEType;

/**
 * @constant kBCOVSSTextTracksKeyKind
 * @abstract The key for the NSString kind of the text track.
 * @discussion This key is required. The value of this key should be either
 * kBCOVSSTextTracksKindSubtitles or kBCOVSSTextTrackKindCaptions.
 */
extern NSString * const kBCOVSSTextTracksKeyKind;


/**
 * @constant kBCOVSSTextTracksKindSubtitles
 * @abstract A text track kind value that indicates that a text track kind is
 * subtitles.
 * @discussion Also see kBCOVSSTextTracksKeyKind and kBCOVSSTextTracksKindCaptions.
 */
extern NSString * const kBCOVSSTextTracksKindSubtitles;

/**
 * @constant kBCOVSSTextTrackKindCaptions
 * @abstract A text track kind value that indicates that a text track kind is
 * closed captions.
 * @discussion Also see kBCOVSSTextTracksKeyKind and kBCOVSSTextTracksKindSubtitles.
 */
extern NSString * const kBCOVSSTextTracksKindCaptions;

/**
 * @constant kBCOVSSTextTracksKeySourceType
 * @abstract An NSDictionary key used to specify the type of file
 * referred to by the kBCOVSSTextTracksKeySource URL.
 * @discussion This NSDictionary key can take one of two values:
 * kBCOVSSTextTracksKeySourceTypeWebVTTURL to indicate that the
 * kBCOVSSTextTracksKeySourceType URL refers to a WebVTT file, or
 * kBCOVSSTextTracksKeySourceTypeM3U8URL to indicate that the
 * kBCOVSSTextTracksKeySourceType URL refers to an M3U8 file.
 * This key/value pair is only necessary if the source URL does not
 * use a ".vtt" or ".m3u8" extension.
 */
extern NSString * const kBCOVSSTextTracksKeySourceType;

/**
 * @constant kBCOVSSTextTracksKeySourceTypeWebVTTURL
 * @abstract An NSDictionary value used to indicate that the
 * source URL refers to a WebVTT file.
 * @discussion This key/value pair is only necessary if the
 * source URL refers to a WebVTT file, but does not use
 * a ".vtt" extension.
 */
extern NSString * const kBCOVSSTextTracksKeySourceTypeWebVTTURL;

/**
 * @constant kBCOVSSTextTracksKeySourceTypeM3U8URL
 * @abstract An NSDictionary value used to indicate that the
 * source URL refers to an M3U8 file.
 * @discussion This key/value pair is only necessary if the
 * source URL refers to an M3U8 file, but does not use
 * an ".m3u8" extension.
 */
extern NSString * const kBCOVSSTextTracksKeySourceTypeM3U8URL;


@interface BCOVPlayerSDKManager (BCOVSSAdditions)

/**
 * Creates and returns a new playback controller configured for sidecar subtitles
 * with the specified view strategy.
 *
 * @param viewStrategy A view strategy that determines the view for the returned
 * playback controller.
 * @return A new playback controller configured for sidecar subtitles playback 
 * sessions.
 */
- (id<BCOVPlaybackController>)createSidecarSubtitlesPlaybackControllerWithViewStrategy:(BCOVPlaybackControllerViewStrategy)viewStrategy;

/**
 * Creates and returns a new sidecar subtitle session provider with the
 * specified parameters.
 *
 * @param provider Optional upstream session provider.
 * @return A new session provider with the specified parameters.
 */
- (id<BCOVPlaybackSessionProvider>)createSidecarSubtitlesSessionProviderWithUpstreamSessionProvider:(id<BCOVPlaybackSessionProvider>)provider;

@end


@interface BCOVPlayerSDKManager (BCOVSSAdditionsDepricated)

- (id<BCOVPlaybackSessionProvider>)createSidecarSubtitlesSessionProviderWithOptions:(BCOVSSSessionProviderOption *)options __attribute__((deprecated("Use -[BCOVPlayerSDKManager createSidecarSubtitlesSessionWithUpstreamSessionProvider:] with a nil upstream session provider instead.")));

@end

