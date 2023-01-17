//
// BCOVVideo.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>
#import <BrightcovePlayerSDK/BCOVVideoErrorCodes.h>

@class BCOVCuePointCollection;
@class BCOVSource;
@protocol BCOVMutableVideo;

// Economics field values
typedef NS_ENUM(NSInteger, BCOVEconomics)
{
    // Supported economics values
    BCOVEconomicsAdSupported = 0,
    BCOVEconomicsFree,
    
    // Currently unused
    BCOVEconomicsPublisherPays,
    BCOVEconomicsPayMedia
};

NS_ASSUME_NONNULL_BEGIN

/**
 * The properties dictionary on a BCOVVideo object can contain
 * any of the following keys. These can be used when
 * manually initializing a BCOVVideo, like initWithSource:cuePoints:properties
 */
extern NSString * const kBCOVVideoPropertyKeyAccountId;
extern NSString * const kBCOVVideoPropertyKeyDescription;
extern NSString * const kBCOVVideoPropertyKeyDuration;
extern NSString * const kBCOVVideoPropertyKeyEconomics;
extern NSString * const kBCOVVideoPropertyKeyId;
extern NSString * const kBCOVVideoPropertyKeyLongDescription;
extern NSString * const kBCOVVideoPropertyKeyName;
extern NSString * const kBCOVVideoPropertyKeyPoster;
extern NSString * const kBCOVVideoPropertyKeyPosterSources;
extern NSString * const kBCOVVideoPropertyKeyProjection;
extern NSString * const kBCOVVideoPropertyKeyReferenceId;
extern NSString * const kBCOVVideoPropertyKeyTags;
extern NSString * const kBCOVVideoPropertyKeyTextTracks;
extern NSString * const kBCOVVideoPropertyKeyThumbnail;
extern NSString * const kBCOVVideoPropertyKeyThumbnailSources;
extern NSString * const kBCOVVideoPropertyKeyVariants;
extern NSString * const kBCOVVideoPropertyKeyManifestURLTTL;
extern NSString * const kBCOVVideoPropertyKeyPolicyKey;
extern NSString * const kBCOVVideoPropertyKeyCatalogResponseTime;

/**
 * Pass nil to get the video name for the device locale or
 * the preferred description if the device locale is not available.
 */
extern NSString * _Nullable localizedNameForLocale(BCOVVideo * _Nullable video, NSLocale * _Nullable locale);

/**
 * Pass nil to get the short description for the device locale or
 * the preferred description if the device locale is not available.
 */
extern NSString * _Nullable localizedShortDescriptionForLocale(BCOVVideo * _Nullable video, NSLocale * _Nullable locale);

/**
 * Pass nil to get the long description for the device locale or
 * the preferred description if the device locale is not available.
 */
extern NSString * _Nullable localizedLongDescriptionForLocale(BCOVVideo * _Nullable video, NSLocale * _Nullable locale);


/**
 * A video in the Brightcove Player SDK ecosystem. Brightcove organizes content
 * into entities called videos, which may have zero or more sources containing
 * information specific to accessing the content. The video provides a container
 * for referencing these sources in the aggregate, and a place for metadata
 * about the video or the collection of sources in the form of properties. Also,
 * a video may have a cue point collection, which is a set of cue points that
 * describe specific locations in the video's content timeline.
 */
@protocol BCOVVideo <NSObject>

/**
 * The cue points associated to this video. These cue points apply equally to
 * the content at each of this video's sources.
 */
@property (nonatomic, readonly, copy) BCOVCuePointCollection *cuePoints;

/**
 * Metadata or properties related to this video or its sources in the aggregate.
 * You can find constants for the keys that this SDK uses with this dictionary
 * near the top of this header file.
 */
@property (nonatomic, readonly, copy) NSDictionary *properties;

/**
 * The economics field that comes from Video Cloud.
 * kBCOVEconomicsAdSupported is the default, and means that the ads should be displayed.
 * kBCOVEconomicsFree means that no ads should be shown during video playback.
 */
@property (nonatomic) BCOVEconomics economics;

/**
 * The sources which comprise the actual destinations at which this video's
 * content can be accessed.
 */
@property (nonatomic, readonly, copy) NSArray<BCOVSource *> *sources;

/**
 * The URL at which this video's VTT thumbnails source is available.
 * This value overrides any thumbnails VTT track that the SDK uses
 * from a PAPI response.
 *
 * The value will be `nil` if you have not set a value.
 */
@property (nonatomic, readonly, copy, nullable) NSURL *thumbnailVTTURL;

/**
 * Returns a modified version of this source. Because BCOVVideo objects
 * are immutable, an entirely new BCOVVideo must be created even if only
 * a single change is needed. Therefore, this method provides a convenient way
 * to obtain a temporary mutable copy of this instance and modify it (within
 * `updateBlock`).
 *
 * Do not attempt to save a reference to the mutable video passed to
 * `updateBlock`, as the behavior of doing this is undefined. Instead, make
 * whatever modifications are necessary in the block and then capture the video
 * object returned from this method.
 *
 * @param updateBlock A block which is passed a mutable copy of this video.
 * @return The copy of this video modified by `updateBlock`.
 */
- (instancetype)update:(void (^)(id<BCOVMutableVideo> mutableVideo))updateBlock;

@end


/**
 * Sub-protocol of BCOVVideo, used only in its `-update` method.
 */
@protocol BCOVMutableVideo <BCOVVideo>

@property (nonatomic, readwrite, copy, nullable) BCOVCuePointCollection *cuePoints;

/**
 * You can find constants for the keys that this SDK uses with this dictionary
 * near the top of this header file.
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary *properties;
@property (nonatomic, readwrite, copy, nullable) NSArray *sources;
@property (nonatomic, readwrite, copy, nullable) NSURL *thumbnailVTTURL;

@end


/**
 * Implementation of the BCOVVideo protocol.
 */
@interface BCOVVideo : NSObject <BCOVVideo, NSCopying>

/**
 * Returns YES if this video object can be downloaded for offline playback
 */
@property (nonatomic, readonly) BOOL canBeDownloaded;

/**
 * Returns YES if this video object has a source using FairPlay encryption
 * This applies to videos retrieved from Dynamic Delivery accounts only.
 */
@property (nonatomic, readonly) BOOL usesFairPlay;

/**
 * Returns YES if this instance refers to an offline video.
 * Use the `playableOffline` property to determine if the
 * video is playable offline.
 */
@property (nonatomic, readonly) BOOL offline;

/**
 * @abstract Determines if a complete rendition of an AVAsset is available to
 *  be played without a network connection.
 *
 * @discussion Query this property before presenting or attempting
 *  to play an offline asset to determine if it’s available for use. A return
 *  value of true indicates a complete rendition of this asset is available for
 *  offline playback.
 *
 *  Reading this property is equivalent to reading the playableOffline property
 *  of the AVAssetCache of an AVAsset.
 *
 *  @return Returns YES if this instance refers to an offline video
 *  playable from the device's local storage without a network connection.
 *
 *  Returns NO if the video has not completed downloading,
 *  or if the video has been purged and needs to be re-downloaded.
 *  This happens automatically if iOS needs to reclaim storage space
 *  for proper functioning of the device.
 *
 *  On some versions of iOS `playableOffline` may return NO if the offline video is already
 *  loaded up in an instance of AVPlayer. Calling `removeAllItems`
 *  on the current instance of `AVQueuePlayer` prior to checking
 *  should result in the expected value of TRUE being returned.
 */
@property (nonatomic, readonly) BOOL playableOffline;

/**
 * A string representation of an error code for an unplayable video
 */
@property (nonatomic, copy, nullable) NSString *errorCode;

/**
 * A string representation of an error sub code for an unplayable video
 */
@property (nonatomic, copy, nullable) NSString *errorSubCode;

/**
 * A error emssage string for an unplayable video
*/
@property (nonatomic, copy, nullable) NSString *errorMessage;

/**
 * Returns NO if `errorCode`, `errorSubCode` and `errorMessage` are all nil
 * otherwise if any of those properties have a vaile will return YES
 */
@property (nonatomic, readonly) BOOL hasError;

/**
 * @abstract Constructs a new video with the specified sources, cue points, and
 * properties.
 *
 * @discussion When using this initializer you can take advantage of the
 * kBCOVVideoPropertyKey constants to create the properties dictionary. You can find
 * constants for the keys that this SDK uses with this dictionary near the top of this header file.
 *
 * @param sources The sources of this video.
 * @param cuePoints The cue points associated to this video.
 * @param properties The metadata or properties associated to this video.
 * @return A new video with the specified sources, cue points, and properties.
 */
- (instancetype)initWithSources:(nullable NSArray<BCOVSource *> *)sources cuePoints:(nullable BCOVCuePointCollection *)cuePoints properties:(nullable NSDictionary *)properties;

/**
 * Constructs a new video with a single specified source, the specified cue
 * points, and the specified properties.
 *
 * @discussion When using this initializer you can take advantage of the
 * kBCOVVideoPropertyKey constants to create the properties dictionary. You can find
 * constants for the keys that this SDK uses with this dictionary near the top of this header file.
 *
 * @param source The sole source of this video.
 * @param cuePoints The cue points associated to this video.
 * @param properties The metadata or properties associated to this video.
 * @return A new video with a single source, as well as the specified cue points
 * and properties.
 */
- (instancetype)initWithSource:(nullable BCOVSource *)source cuePoints:(nullable BCOVCuePointCollection *)cuePoints properties:(nullable NSDictionary *)properties;

/**
 * Constructs a new video with with error information.
 *
 * @discussion When attempting to retreive a video the server may an
 * error. The error may be caused due to various restrictions  other reasons.
 * The information is stored on the BCOVideo object for informative purposes.
 *
 * @param errorCode The error code
 * @param errorSubCode The error sub-code
 * @param errorMessage The error message
 * @param properties The metadata or properties associated to this video.
 * @return A new video with error information attributes
 */
- (instancetype)initWithErrorCode:(nullable NSString *)errorCode errorSubCode:(nullable NSString *)errorSubCode errorMessage:(nullable NSString *)errorMessage properties:(nullable NSDictionary *)properties;

/**
 * Returns YES if `video` is equivalent to this instance.
 *
 * @param video The video to test for equivalence with this instance.
 * @return Whether `video` is equivalent to this instance.
 */
- (BOOL)isEqualToVideo:(nullable BCOVVideo *)video;

/**
 * Loops through language variants on this video and attempt to match it
 * with one of the languages provided.
 *
 * The first match found will be returned.
 *
 * If no result is found a `nil` value is returned.
 *
 * @property preferredLanguages Array of preferred languages with which
 * to attempt a match. Use with `NSLocale.preferredLanguages`
 */
- (NSDictionary *)variantForPreferredLanguage:(nullable NSArray *)preferredLanguages;

/**
 * Returns a new video with a single source containing the specified URL.
 *
 * @param url The URL of the source to be created and associated to the new
 * video.
 * @return A new video with a source containing the specified URL.
 */
+ (BCOVVideo *)videoWithURL:(NSURL *)url;

/**
 * Returns a new video with a single source containing the specified URL
 * and a delivery method as kBCOVSourceDeliveryHLS.
 *
 * @param url The URL of the source to be created and associated to the new
 * video.
 * @return A new video with a source containing the specified URL.
 */
+ (BCOVVideo *)videoWithHLSSourceURL:(NSURL *)url;

/**
 * Returns a new video with a single source containing the specified URL.
 *
 * @param url The URL of the source to be created and associated to the new
 * video.
 * @param deliveryMethod The delivery method for this source. See BCOVSource for options.
 * @return A new video with a source containing the specified URL.
 */
+ (BCOVVideo *)videoWithURL:(NSURL *)url deliveryMethod:(nullable NSString *)deliveryMethod;

@end

NS_ASSUME_NONNULL_END
