//
// BCOVOfflineVideoManagerConstants.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

/**
 * Error domain for the Offline Video Manager.
 */
extern NSString * const kBCOVOfflineVideoManagerErrorDomain;

/**
 * An invalid parameter was passed to a method.
 */
extern const NSInteger kBCOVOfflineVideoManagerErrorCodeInvalidParameter;

/**
 * This method/feature is not available on this device/system.
 */
extern const NSInteger kBCOVOfflineVideoManagerErrorCodeUnsupported;

/**
 * An error occurred while trying to download a video.
 * See the error description for more details.
 */
extern const NSInteger kBCOVOfflineVideoManagerErrorCodeDownloadFailure;

/**
 * The FairPlay license has expired.
 * See the error description for more details.
 */
extern const NSInteger kBCOVOfflineVideoManagerErrorCodeExpiredLicense;

/**
 * The FairPlay license is invalid or missing.
 * See the error description for more details.
 */
extern const NSInteger kBCOVOfflineVideoManagerErrorCodeInvalidLicense;


/**
 * NSNotification name for a warning sent when analytics files related to
 * offline playback have reached 500 MiB. This can happen if a user
 * plays lots of offline video (over 1000 hours) but has not been online
 * in a long time.
 * Analytics will not continue to grow beyond this point, but in order for
 * you to collect accurate data about your app usage, you may want to encourage
 * the user to go back online so that analytics data can be transferred.
 * If analytics storage remains full, older, less-important events (like
 * engagement events) will be dropped to make room for video view events.
 * Register for this warning using the NSNotificationCenter.defaultCenter.
 */
extern NSString * const kBCOVOfflineVideoManagerAnalyticsStorageFullWarningNotification;

/**
 * kBCOVOfflineVideoManagerAllowsCellularDownloadKey
 * NSDictionary key used to set an option passed to
 * `-[initializeOfflineVideoManagerWithDelegate:options:]`.
 * If set to @(YES), connections will be allowed over cellular networks.
 * If @(NO), cellular connections will not be allowed.
 * Default value is @(NO).
 * Corresponds directly to NSURLSessionConfiguration's allowCellularAccess property.
 * Changing this value will not have an effect on active downloads; only downloads
 * initialized after the value has been changed will be affected.
 */
extern NSString * const kBCOVOfflineVideoManagerAllowsCellularDownloadKey;

/**
 * kBCOVOfflineVideoManagerAllowsCellularPlaybackKey
 * NSDictionary key used to set an option passed to
 * `-[initializeOfflineVideoManagerWithDelegate:options:]`.
 * If set to @(YES), playback of offline content is allowed to access the internet
 * over a cellular connection.
 * If @(NO), cellular connections will not be allowed during playback.
 * Network activity can be triggered if you request a media option that has not
 * been downloaded.
 * Corresponds directly to AVURLAsset option's AVURLAssetAllowsCellularAccessKey property.
 */
extern NSString * const kBCOVOfflineVideoManagerAllowsCellularPlaybackKey;

/**
 * kBCOVOfflineVideoManagerAllowsCellularAnalyticsKey
 * NSDictionary key used to set an option passed to
 * `-[initializeOfflineVideoManagerWithDelegate:options:]`.
 * If set to @(YES), analytics data related to playback of offline content
 * will be transmitted over cellular networks.
 * If @(NO), cellular connections will not be used for transmission of
 * analytics data.
 * The default value is @(YES).
 */
extern NSString * const kBCOVOfflineVideoManagerAllowsCellularAnalyticsKey;

/**
 * kBCOVOfflineVideoManagerAnalyticsStorageLimitKey
 * NSDictionary key used to set an option passed to
 * `-[initializeOfflineVideoManagerWithDelegate:options:]`.
 * You can pass an NSNumber with this key to set the maximum storage space
 * allowed for holding offline analytics data.
 * If a user doesn't come online for a while, analytics data will collect
 * until this limit is reached. Once reached, only video_view events will
 * be stored, and other events will start being dropped.
 * The default value is 524288000 (500 MiB).
 * The minimum settable value is 1.0 MiB.
 */
extern NSString * const kBCOVOfflineVideoManagerAnalyticsStorageLimitKey;

/**
 * The following keys are used to specify values in the parameters dictionary
 * passed to `-BCOVOfflineVideoManager requestVideoDownload:mediaSelections:parameters:completion:`
 */

/**
 * kBCOVOfflineVideoManagerRequestedBitrateKey
 * When this NSNumber is set, the Offline Video Manager will download a rendition
 * with the largest bitrate less than or equal to this value.
 * If no rendition can be found with a bitrate that is smaller than or equal to
 * this bitrate, the lowest rendition will be downloaded.
 * If this value is zero or not specified, the lowest rendition with video will be downloaded.
 */
extern NSString * const kBCOVOfflineVideoManagerRequestedBitrateKey;

/**
 * kBCOVOfflineVideoManagerDisplayNameKey
 * This is an NSString that determines the name of the video
 * displayed in the "Downloaded Videos" section of the
 * iOS Settings/iPad+iPhone Storage/Downloaded Videos view
 * seen in iOS 11+.
 * If this option is not set, the `name` properties
 * on the video will be used instead.
 */
extern NSString * const kBCOVOfflineVideoManagerDisplayNameKey;

/**
 * kBCOVFairPlayLicensePurchaseKey
 * A Boolean boxed in an NSValue.
 * If YES, the downloaded FairPlay content will be assigned
 * a license that does not expire.
 * If absent or NO, the kBCOVFairPlayLicenseRentalDurationKey must be set.
 */
extern NSString * const kBCOVFairPlayLicensePurchaseKey;

/**
 * kBCOVFairPlayLicenseRentalDurationKey
 * Specifies the rental duration of the FairPlay license, in seconds.
 * The number should be a positive integer greater than zero.
 * The rental period begins as soon as the download request is made.
 */
extern NSString * const kBCOVFairPlayLicenseRentalDurationKey;

/**
 * kBCOVFairPlayLicensePlayDurationKey
 * Specifies the duration of the FairPlay License, in seconds,
 * after playback has started.
 * The number should be a positive integer greater than zero.
 */
extern NSString * const kBCOVFairPlayLicensePlayDurationKey;

/**
 * The following keys are used to access values in the the
 * BCOVVideo's properties dictionary
 */

/**
 * kBCOVOfflineVideoTokenPropertyKey
 * Offline video token properties dictionary key
 */
extern NSString * const kBCOVOfflineVideoTokenPropertyKey;

/**
 * kBCOVOfflineVideoLicenseRequestTimePropertyKey
 * BCOVVideo properties key that stores the time that the offline
 * video FairPlay license was requested.
 * This time is stored as the floating point number of seconds since the
 * standard NSDate reference date.
 * You can generate an NSDate object from this as follows:
 *   [NSDate dateWithTimeIntervalSinceReferenceDate:number]
 */
extern NSString * const kBCOVOfflineVideoLicenseRequestTimePropertyKey;

/**
 * kBCOVOfflineVideoLicenseAbsoluteExpirationTimePropertyKey
 * BCOVVideo properties key that stores the time that the offline
 * video FairPlay license will expire. After this time, you can no longer
 * begin playback on the associated video.
 * This time is stored as the floating point number of seconds since the
 * standard NSDate reference date.
 * You can generate an NSDate object from this as follows:
 *   [NSDate dateWithTimeIntervalSinceReferenceDate:number]
 */
extern NSString * const kBCOVOfflineVideoLicenseAbsoluteExpirationTimePropertyKey;

/**
 * kBCOVOfflineVideoInitialPlaybackTimeKey
 * BCOVVideo properties key that stores the time that the video
 * first started playback. If a playDuration value was used for the
 * video's license then you can use this value in addition to the
 * value from kBCOVFairPlayLicensePlayDurationKey to determine
 * when the dual-expiry license will expire.
 * This time is stored as the floating point number of seconds since the
 * standard NSDate reference date.
 * You can generate an NSDate object from this as follows:
 *   [NSDate dateWithTimeIntervalSinceReferenceDate:number]
 */
extern NSString * const kBCOVOfflineVideoInitialPlaybackTimeKey;

/**
 * kBCOVOfflineVideoDownloadStartTimePropertyKey
 * BCOVVideo properties key that stores the time that the offline
 * video download was initially requested.
 * This time is stored as the floating point number of seconds since the
 * standard NSDate reference date.
 * You can generate an NSDate object from this as follows:
 *   [NSDate dateWithTimeIntervalSinceReferenceDate:number]
 * This value is useful when sorting by the time each download process started.
 */
extern NSString * const kBCOVOfflineVideoDownloadStartTimePropertyKey;

/**
 * kBCOVOfflineVideoDownloadEndTimePropertyKey
 * BCOVVideo properties key that stores the time that the offline
 * video download completed (whether normally, cancelled, or failed).
 * This time is stored as the floating point number of seconds since the
 * standard NSDate reference date.
 * You can generate an NSDate object from this as follows:
 *   [NSDate dateWithTimeIntervalSinceReferenceDate:number]
 * This value is useful when sorting by the time each download completes.
 * This value is zero until the download completes.
 */
extern NSString * const kBCOVOfflineVideoDownloadEndTimePropertyKey;

/**
 * kBCOVOfflineVideoOnlineSourceURLPropertyKey
 * BCOVVideo properties key that stores the URL of the original online video
 * that was downloaded to storage for this BCOVVideo object, as an NSString.
 * Note that this URL may have expired, so this is primarily useful as a reference.
 */
extern NSString * const kBCOVOfflineVideoOnlineSourceURLPropertyKey;

/**
 * kBCOVOfflineVideoThumbnailNamePropertyKey
 * BCOVVideo properties key that stores the name of the
 * downloaded thumbnail image file in device storage, as an NSString.
 * This name is used to generate the full path of the file at runtime.
 */
extern NSString * const kBCOVOfflineVideoThumbnailNamePropertyKey;

/**
 * kBCOVOfflineVideoThumbnailFilePathPropertyKey
 * BCOVVideo properties key that stores the full path to the
 * downloaded thumbnail image file in device storage, as an NSString.
 * Even if the path is present, the image file may not be present.
 * Due to app sandboxing, this path will likely change each time
 * the app is launched, so you should not store the full path.
 */
extern NSString * const kBCOVOfflineVideoThumbnailFilePathPropertyKey;

/**
 * kBCOVOfflineVideoPosterNamePropertyKey
 * BCOVVideo properties key that stores the name of the
 * downloaded poster image file in device storage, as an NSString.
 * This name is used to generate the full path of the file at runtime.
 */
extern NSString * const kBCOVOfflineVideoPosterNamePropertyKey;

/**
 * kBCOVOfflineVideoPosterFilePathPropertyKey
 * BCOVVideo properties key that stores the full path to the
 * downloaded poster image file in device storage, as an NSString.
 * Even if the path is present, the image file may not be present.
 * Due to app sandboxing, this path will likely change each time
 * the app is launched, so you should not store the full path.
 */
extern NSString * const kBCOVOfflineVideoPosterFilePathPropertyKey;

/**
 * kBCOVOfflineVideoRelativeFilePathPropertyKey
 * BCOVVideo properties key that stores the relative file path
 * of the downloaded HLS video bundle in device storage, as an NSString.
 * This path is used to generate the full path of the file at runtime.
 */
extern NSString * const kBCOVOfflineVideoRelativeFilePathPropertyKey;

/**
 * kBCOVOfflineVideoFilePathPropertyKey
 * BCOVVideo properties key that stores the full path to the
 * downloaded HLS video bundle in device storage, as an NSString.
 * Due to app sandboxing, this path will likely change each time
 * the app is launched, so you should not store the full path.
 */
extern NSString * const kBCOVOfflineVideoFilePathPropertyKey;

/**
 * kBCOVOfflineVideoMediaType
 * The BCOVSourceMediaType of this offline video.
 * Will either be BCOVSourceMediaTypeAudio or BCOVSourceMediaTypeAudioVideo
 * and stored as an NSNumber.
 */
extern NSString * const kBCOVOfflineVideoMediaType;

