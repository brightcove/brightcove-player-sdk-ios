//
// BCOVOfflineVideoManager.h
// BrightcovePlayerSDK
//
// Copyright (c) 2017 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVAdvertising.h>

@class BCOVVideo;
@protocol BCOVFPSAuthorizationProxy;

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
 * BCOVOfflineVideoToken
 * This is a unique string that is used to identify a downloaded file,
 * including downloads in process, or downloads that failed with an error.
 * Offline video tokens are persistent and can be stored and used across
 * application launches.
 * You can convert an offline video token into a BCOVVideo object at any time
 * using -[videoObjectFromOfflineVideoToken:]. You can play this video object
 * like any other BCOVVideo using -[BCOVPlaybackController setVideos:], or
 * use it to examine all the video properties.
 */
typedef NSString *BCOVOfflineVideoToken;

/**
 * kBCOVOfflineVideoManagerAllowsCellularDownloadKey
 * NSDictionary key used to set an option passed to
 * `-[initializeOfflineVideoManagerWithDelegate:options:]`.
 * If set to @(YES), connections will be allowed over cellular networks.
 * If @(NO), cellular connections will not be allowed.
 * Default value is @(NO).
 * Corresponds directly to NSURLSessionConfiguration's allowCellularAccess property.
 */
extern NSString * const kBCOVOfflineVideoManagerAllowsCellularDownloadKey;

/**
 * kBCOVOfflineVideoManagerAllowsCellularPlaybackKey
 * NSDictionary key used to set an option passed to
 * `-[initializeOfflineVideoManagerWithDelegate:options:]`.
 * If set to @(YES), playback of offline content is allowed to access the internet.
 * If @(NO), cellular connections will not be allowed during playback.
 * Network activity can be triggered if you request a media option that has not
 * been downloaded.
 * Corresponds directly to AVURLAsset option's AVURLAssetAllowsCellularAccessKey property.
 */
extern NSString * const kBCOVOfflineVideoManagerAllowsCellularPlaybackKey;

/**
 * The following keys are used to specify values in the parameters dictionary
 * passed to `-BCOVOfflineVideoManager requestVideoDownload:parameters:completion:`
 */

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
 * The following keys are used to access values in the the
 * BCOVVideo's properties dictionary
 */

/**
 * kBCOVOfflineVideoTokenPropertyKey
 * Offline video token properties dictionary key
 */
extern NSString * const kBCOVOfflineVideoTokenPropertyKey;

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
 * of the downloaded FairPlay video bundle in device storage, as an NSString.
 * This path is used to generate the full path of the file at runtime.
 */
extern NSString * const kBCOVOfflineVideoRelativeFilePathPropertyKey;

/**
 * kBCOVOfflineVideoFilePathPropertyKey
 * BCOVVideo properties key that stores the full path to the
 * downloaded FairPlay video bundle in device storage, as an NSString.
 * Due to app sandboxing, this path will likely change each time
 * the app is launched, so you should not store the full path.
 */
extern NSString * const kBCOVOfflineVideoFilePathPropertyKey;


/**
 * Conform to this protocol to receive information about each video download.
 */
@protocol BCOVOfflineVideoManagerDelegate<NSObject>

#if !TARGET_OS_TV

@optional

/**
 * Receive progress notification about a download in progress.
 * You can use the AVAssetDownloadTask to retrieve more information about the download,
 * like the specific segments that are loaded.
 * If you want to pause/resume/cancel the task, you should use the methods available
 * in the BCOVOfflineVideoManager to perform those actions.
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the downloaded video.
 *  @param downloadtask
 *                  The AVAssetDownloadTask for this video
 *  @param progressPercent
 *                  How far along the download has progressed, expressed as a percentage.
*/
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
             downloadTask:(AVAssetDownloadTask *)downloadtask
            didProgressTo:(NSTimeInterval)progressPercent;

/**
 * This method is called when a download is complete.
 * If any errors occurred during the download, error will be non-nil.
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the downloaded video.
 *  @param error    NSError encountered during the download process.
 *                  nil if no error.
 */
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
didFinishDownloadWithError:(NSError *)error;

/**
 * This method is called when the static images (thumbnail and poster) associated
 * with a video are downloaded to storage.
 * File URLs for the downloaded images are stored as properties on a BCOVVideo
 * created from the offline video token using -[videoObjectFromOfflineVideoToken:]
 * The properties are retrieved using the kBCOVOfflineVideoThumbnailFilePath and
 * kBCOVOfflineVideoPosterFilePath keys.
 * This method will be called even if no images could be retrieved, so be sure to
 * check the UIImage you create from the poster and thumbnail paths. The file
 * paths will be present, but there may be no images stored at those locations.
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the downloaded video.
 */
- (void)didDownloadStaticImagesWithOfflineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken;


/**
 * This method is called when cleaning up stranded downloads.
 * Downloads can be stranded if you force-quit an app during a download,
 * or reboot while the app is suspended.
 * You do not need to implement this method unless you are starting your own
 * video downloads outside the Brightcove SDK and don't want your videos deleted.
 * This method is called when a video package is flagged for deletion, meaning
 * this is no record of it in the Brightcove SDK.
 * If this is a file you recognize, you should return NO.
 * Otherwise, returning YES will cause the video package to be deleted.
 * If you do not implement this method, stranded downloads will
 * be deleted by default.
 *
 *  @param videoPackagePath
 *                  Path to video package directory that is flagged as stranded.
 */
- (BOOL)shouldDeleteVideoPackage:(NSString *)videoPackagePath;

#endif

@end

/**
 * BCOVOfflineVideoDownloadState
 * The various possible states of a video download
 */
typedef NS_ENUM(NSInteger, BCOVOfflineVideoDownloadState) {
    
    /* Download requested but not yet reporting progress */
    BCOVOfflineVideoDownloadStateRequested = 0,

    /* Download is progressing normally */
    BCOVOfflineVideoDownloadStateDownloading = 1,

    /* Download was paused */
    BCOVOfflineVideoDownloadStateSuspended = 2,

    /* Download was cancelled */
    BCOVOfflineVideoDownloadStateCancelled = 3,

    /* Download completed normally */
    BCOVOfflineVideoDownloadStateCompleted = 4,

    /* Download terminated with an error */
    BCOVOfflineVideoDownloadStateError = 5
    
};

/**
 * BCOVOfflineVideoStatus
 * This object keeps track of various pieces of information related
 * to video downloads.
 */
@interface BCOVOfflineVideoStatus : NSObject <NSCopying>

/**
 * Offline video token used to identify the downloaded video
 */
@property (nonatomic) BCOVOfflineVideoToken offlineVideoToken;

/**
 * The state of the current download
 */
@property (nonatomic) BCOVOfflineVideoDownloadState downloadState;

/**
 * The NSDate that this download was requested (not when it started)
 */
@property (nonatomic) NSDate *downloadStartTime;

/**
 * The NSDate that this download finished (successfully, cancelled, or with an error)
 */
@property (nonatomic) NSDate *downloadEndTime;

/**
 * The progress of the download, expressed as a percentage
 */
@property (nonatomic) CGFloat downloadPercent;

#if !TARGET_OS_TV
/**
 * The AVAssetDownloadTask associated with this download.
 * Will be set to nil once the download has completed.
 */
@property (nonatomic) AVAssetDownloadTask *downloadTask;
#else
@property (nonatomic) id downloadTask;

#endif

/**
 * The NSError associated with this download if a failure occurs.
 */
@property (nonatomic) NSError *error;

@end


/**
 * BCOVOfflineVideoManager
 * This singleton class handles most aspects of video file downloading
 */
@interface BCOVOfflineVideoManager : NSObject

/**
 * Proxy object that handles specific subtasks of FairPlay key exchange
 * as defined by the BCOVFPSAuthorizationProxy protocol.
 */
@property (nonatomic, strong) id<BCOVFPSAuthorizationProxy> authProxy;

/**
 * Delegate for this BCOVOfflineVideoManager.
 */
@property (nonatomic, assign) id<BCOVOfflineVideoManagerDelegate> delegate;

/**
 * Returns an array of all the offline video tokens.
 * Each token refers to a video download in device storage,
 * including videos that are currently being downloaded,
 * and videos that were cancelled, paused, or failed.
 */
@property (nonatomic, readonly) NSArray<BCOVOfflineVideoToken> *offlineVideoTokens;

/**
 * The shared instance used to access
 * the singleton BCOVOfflineVideoManager object.
 */
+ (BCOVOfflineVideoManager *)sharedManager;

/**
 * Initialize the Offline Video Manager
 * This should be the first call to the Offline Video Manager. It can be called
 * repeatedly, but only the first call will have any effect.
 *
 *  @param delegate The delegate object conforming to the BCOVOfflineVideoManagerDelegate protocol.
 *                  The only valid dictionary entries are
 *                  kBCOVOfflineVideoManagerAllowsCellularDownloadKey and
 *                  kBCOVOfflineVideoManagerAllowsCellularPlaybackKey.
 */
+ (void)initializeOfflineVideoManagerWithDelegate:(id<BCOVOfflineVideoManagerDelegate>)delegate
                                          options:(NSDictionary *)options;

/**
 * Estimate the size of a video download in megabytes.
 * This method calls the completion handler with an estimate of the video size
 * of the largest rendition in the HLS manifest, in megabytes.
 * If there are any problems retrieving the value, `error` will be set,
 * and `size` will be zero.
 *
 *  @param video    The BCOVVideo object from Video Cloud.
 *                  The video object should contain a valid HLS source.
 *  @param options  NSDictionary of options used in this request.
 *                  Should be set to nil.
 *  @param completionHandler
 *                  Block that receives the estimated size of the video after
 *                  the request is successfully made. If there is an error,
 *                  `megabytes` will be set to zero, and `error` will report any NSError.
 *                  The completion handler is not called on any specific thread.
 *                  You should switch to the main thread if you need to perform
 *                  any UI work. It may be called synchronously or asynchronously.
 */
- (void)estimateDownloadSize:(BCOVVideo *)video
                      options:(NSDictionary *)options
                   completion:(void (^)(double megabytes, NSError *error))completionHandler;

/**
 * Returns an array of the status of all video downloads,
 * including videos that are currently being downloaded,
 * and videos that were cancelled, paused, or failed.
 *
 * This provides information about each download, like the download status,
 * start time, progress percent, underlying AVAssetDownloadTask,
 * and error (if any when complete).
 */
- (NSArray <BCOVOfflineVideoStatus *> *)offlineVideoStatus;

/**
 * Returns the BCOVOfflineVideoStatus object for a specific video download.
 * This provides information about the download, like the download status,
 * start time, progress percent, underlying AVAssetDownloadTask,
 * and error (if any when complete).
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the downloaded video.
 */
- (BCOVOfflineVideoStatus *)offlineVideoStatusForToken:(BCOVOfflineVideoToken)offlineVideoToken;


/**
 * Initiate a request for a video download.
 * If you are using FairPlay videos with Video Cloud Dynamic Delivery, FairPlay
 * application certificates will be downloaded automatically and used as needed.
 * If you are using legacy Video Cloud FairPlay videos, you should add any
 * needed application certificates to the BCOVOfflineVideoManger before
 * iniitiating a download, using -[addFairPlayApplicationCertificate:identifier:].
 *
 *  @param video    BCOVVideo to be downloaded. The video should have a source
 *                  that uses FairPlay encryption and the HTTPS scheme.
 *
 *  @param parameters
 *                  NSDictionary of parameters used in this download request.
 *                  Valid parameters are:
 *                  - kBCOVFairPlayLicensePurchaseKey
 *                  - kBCOVFairPlayLicenseRentalDurationKey
 *  @param completionHandler
 *                  Block that receives the new offlineVideoToken after the request
 *                  is successfully made. If there is an error, offlienVideoToken will
 *                  be nil, and error will report any NSError.
 */
- (void)requestVideoDownload:(BCOVVideo *)video
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;

/**
 *  Pause a current video download task
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the download task.
 */
- (void)pauseVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 *  Resume a suspended video download task
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the download task.
 */
- (void)resumeVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 *  Cancel a video download task
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the download task.
 */
- (void)cancelVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken;


/**
 * Convert an offline video token into a playable BCOVVideo object.
 * The returned BCOVVideo also contains all the new properties listed above,
 * such as the downloaded thumbnail and poster image file paths, FairPlay
 * license expiration date, download start and end times, and more.
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the downloaded video.
 */
- (BCOVVideo *)videoObjectFromOfflineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * Delete all files in local storage related to this offline video token.
 * offlineVideoToken will be considered invalid after this call.
 *
 *  @param offlineVideoToken
 *                  Offline video token used to identify the downloaded video.
 */
- (void)deleteOfflineVideo:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * FairPlay DRM
 */

/**
 * This method is used to add a FairPlay application certificate to the
 * playback controller's list of available FairPlay application certificates.
 * Certificates will be retained for the life of the playback controller.
 *
 * If you are using Dynamic Delivery, application certificates are retrieved
 * automatically by the FairPlay plugin, so this method is not needed.
 * You can, however, use this method to pre-load your application certificate
 * to speed up playback of the first FairPlay-encrypted video.
 * Certificates are stored and re-used for subsequent videos.
 *
 *  @param applicationCertificateData
 *                  The FairPlay application certificate in an NSData object.
 *                  If set to nil, any existing application certificate for the
 *                  given identifier will be removed.
 *  @param identifier
 *                  A string used to locate the application certificate.
 *                  This string may not be nil.
 *                  - For Dynamic Delivery, the identifier must be the URL
 *                  that was used to retrieve this certificate.
 *                  - For legacy Video Cloud accounts, this should be set to
 *                  kBCOVDefaultFairPlayApplicationCertificateIdentifier
 *                  to apply to all accounts.
 *                  - If you are using multiple legacy Video Cloud accounts,
 *                  set this param to the acount ID.
 */
- (void)addFairPlayApplicationCertificate:(NSData *)applicationCertificateData
                               identifier:(NSString *)identifier;

@end
