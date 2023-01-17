//
// BCOVOfflineVideoManager.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVAdvertising.h>
#import <BrightcovePlayerSDK/BCOVOfflineVideoManagerTypes.h>
#import <BrightcovePlayerSDK/BCOVOfflineVideoManagerConstants.h>
#import <BrightcovePlayerSDK/BCOVOfflineVideoManagerDelegate.h>
#import <BrightcovePlayerSDK/BCOVOfflineVideoStatus.h>

@class BCOVVideo;

@protocol BCOVFPSAuthorizationProxy;

/**
 * BCOVOfflineVideoManager
 * This singleton class handles most aspects of video file downloading
 */
@interface BCOVOfflineVideoManager : NSObject

/**
 * @brief Proxy object that handles specific subtasks of FairPlay key exchange
 *  as defined by the BCOVFPSAuthorizationProxy protocol.
 */
@property (nonatomic, strong) id<BCOVFPSAuthorizationProxy> authProxy;

/**
 * @brief Delegate for this BCOVOfflineVideoManager.
 */
@property (nonatomic, assign) id<BCOVOfflineVideoManagerDelegate> delegate;

/**
 * @abstract Returns an array of all the offline video tokens.
 *
 * @discussion Each token refers to a video download in device storage,
 *  including videos that are currently being downloaded,
 *  and videos that were cancelled, paused, or failed.
 */
@property (nonatomic, readonly) NSArray<BCOVOfflineVideoToken> *offlineVideoTokens;

/**
 * @brief The shared instance used to access the singleton BCOVOfflineVideoManager object.
 */
+ (BCOVOfflineVideoManager *)sharedManager;

/**
 * @abstract Initialize the Offline Video Manager.
 *
 * @discussion This should be the first call to the Offline Video Manager.
 *  You can call this method again to update the delegate and options.
 *
 * @param delegate The delegate object conforming to the BCOVOfflineVideoManagerDelegate protocol.
 *
 * @param options An NSDictionary of options.  The only valid dictionary entries are
 *  kBCOVOfflineVideoManagerAllowsCellularDownloadKey,
 *  kBCOVOfflineVideoManagerAllowsCellularPlaybackKey,
 *  kBCOVOfflineVideoManagerAllowsCellularAnalyticsKey, and
 *  kBCOVOfflineVideoManagerAnalyticsStorageLimitKey.
 */
+ (void)initializeOfflineVideoManagerWithDelegate:(id<BCOVOfflineVideoManagerDelegate>)delegate
                                          options:(NSDictionary *)options;

/**
 * @abstract Initiate a request for a video download.
 *
 * @discussion If you are using FairPlay videos with Video Cloud Dynamic Delivery, FairPlay
 *  application certificates will be downloaded automatically and used as needed.
 *  If you are using legacy Video Cloud FairPlay videos, you should add any
 *  needed application certificates to the BCOVOfflineVideoManger before
 *  initiating a download, using -[addFairPlayApplicationCertificate:identifier:].
 *
 *  @param mediaSelections An array of AVMediaSelections to be downloaded, in addition
 *  to the main video. The available AVMediaSelections for a BCOVVideo can be retrieved by calling
 *  -urlAssetForVideo:error: followed by -[AVAsset preferredMediaSelection] or -[AVAsset allMediaSelections].
 *  Passing nil for mediaSelections will cause the preferred AVMediaSelections to be fetched. Note
 *  that with iOS 13+, all video assets must be downloaded using a single call to
 *  requestVideoDownload:mediaSelections:parameters:completion:.
 *  Additional tracks cannot be downloaded later.
 *
 * @param video BCOVVideo to be downloaded. The video should have an HLS
 *  source with an HTTPS scheme, and may use FairPlay encryption.
 *
 * @param parameters NSDictionary of parameters used in this download request.
 *  May be nil if the license was preloaded using the `preloadFairPlayLicense:parameters:completion` method.
 *  Valid parameters are:
 *  kBCOVOfflineVideoManagerRequestedBitrateKey, kBCOVFairPlayLicensePurchaseKey,
 *  kBCOVFairPlayLicenseRentalDurationKey.
 *
 * @param completionHandler A block that receives the new offlineVideoToken after the request
 *  is successfully made. If there is an error, offlineVideoToken will
 *  be nil, and error will report any NSError.
 */
- (void)requestVideoDownload:(BCOVVideo *)video
             mediaSelections:(NSArray<AVMediaSelection *> *)mediaSelections
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;

/**
 * @abstract Initiate a request for a video download.
 *
 * @discussion If you are using FairPlay videos with Video Cloud Dynamic Delivery, FairPlay
 *  application certificates will be downloaded automatically and used as needed.
 *  If you are using legacy Video Cloud FairPlay videos, you should add any
 *  needed application certificates to the BCOVOfflineVideoManger before
 *  initiating a download, using -[addFairPlayApplicationCertificate:identifier:].
 *
 *  @param downloadConfiguration Blah blah.
 *
 * @param video BCOVVideo to be downloaded. The video should have an HLS
 *  source with an HTTPS scheme, and may use FairPlay encryption.
 *
 * @param parameters NSDictionary of parameters used in this download request.
 *  May be nil. Valid parameters are:
 *  kBCOVOfflineVideoManagerRequestedBitrateKey, kBCOVFairPlayLicensePurchaseKey,
 *  kBCOVFairPlayLicenseRentalDurationKey.
 *
 * @param completionHandler A block that receives the new offlineVideoToken after the request
 *  is successfully made. If there is an error, offlineVideoToken will
 *  be nil, and error will report any NSError.
 */
- (void)requestVideoDownload:(BCOVVideo *)video
             downloadConfiguration:(AVAssetDownloadConfiguration *)downloadConfiguration
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler API_AVAILABLE(ios(15.0));

/**
 * @abstract Returns an array of the status of all video downloads,
 *  including videos that are currently being downloaded,
 *  and videos that were cancelled, paused, or failed.
 *
 * @discussion All objects in the array are copies, so although you can modify an object,
 *  it will have no effect on the download manager.
 *
 *  This method provides information about each download, like the download status,
 *  start time, progress percent, underlying AVAssetDownloadTask,
 *  and error (if any when complete).
 */
- (NSArray <BCOVOfflineVideoStatus *> *)offlineVideoStatus;

/**
 * @abstract Returns a copy of the BCOVOfflineVideoStatus object for a specific video download.
 *
 * @discussion BCOVOfflineVideoStatus provides information about the download, like the download status,
 *  start time, progress percent, underlying AVAggregateAssetDownloadTask, and error (if any when complete).
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 */
- (BCOVOfflineVideoStatus *)offlineVideoStatusForToken:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Pause a current video download task.
 *
 * @param offlineVideoToken Offline video token used to identify the download task.
 */
- (void)pauseVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Resume a suspended video download task
 *
 * @param offlineVideoToken Offline video token used to identify the download task.
 */
- (void)resumeVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Cancel a video download task
 *
 * @param offlineVideoToken Offline video token used to identify the download task.
 */
- (void)cancelVideoDownload:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Delete all files in local storage related to this offline video token.
 *
 * @discussion offlineVideoToken will be considered invalid after this call.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 */
- (void)deleteOfflineVideo:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Stop all download tasks in progress.
 *
 * @discussion This method forces all download tasks to terminate with an error
 *  by deleting their underlying download folder.
 *  Downloads that have already completed are not affected.
 *
 *  WARNING:
 *  This method should only be used in very specific cases.
 *  iOS 11.0.x and iOS 11.1.x have an issue where a download task will resume to
 *  completion if it was paused and then cancelled.
 *  In that case, you cannot cancel or delete the runaway task, so your best
 *  option is to delete all download tasks.
 *
 *  This method is not guaranteed to stop all download tasks.
 *
 *  In iOS 11.2 and later, you should cancel download tasks individually using -cancelVideoDownload:
 */
- (void)forceStopAllDownloadTasks;

/**
 * @abstract Estimate the size of a video download in megabytes.
 *
 * @discussion This method calls the completion handler with an estimate of the video size
 *  of the largest rendition in the HLS manifest, in megabytes.
 *  If there are any problems retrieving the value, `error` will be set,
 *  and `size` will be zero.
 *
 * @param video The BCOVVideo object from Video Cloud. The video object should
 *  contain a valid HLS source.
 *
 * @param options NSDictionary of options used in this request. Use the
 *  kBCOVOfflineVideoManagerRequestedBitrateKey to specify the bitrate you plan to download.
 *
 * @param completionHandler A block that receives the estimated size of the video after
 *  the request is successfully made. If there is an error,
 *  `megabytes` will be set to zero, and `error` will report any NSError.
 *
 *  The completion handler is not called on any specific thread.
 *  You should switch to the main thread if you need to perform
 *  any UI work. It may be called synchronously or asynchronously.
 */
- (void)estimateDownloadSize:(BCOVVideo *)video
                      options:(NSDictionary *)options
                   completion:(void (^)(double megabytes, NSError *error))completionHandler;

/**
 * @abstract Given a BCOVVideo, returns an AVURLAsset which represents the
 * video source that will be used for offline downloads. BCOVVideo objects can
 * contain multiple video sources with the preferred source being secure and appropriate
 * for playback on iOS. Do not use this method in the context of online playback.
 */
- (AVURLAsset *)urlAssetForVideo:(BCOVVideo *)video
                           error:(NSError **)error;

/**
 * @abstract Retrieve an array of NSDictionary objects, one for each variant stream
 * in the specified online HLS video.
 *
 * @discussion Each dictionary contains a key:value pair for each of the variant stream's
 *  attributes as specified by its corresponding EXT-X-STREAM-INF tag in the
 *  HLS manifest.
 *
 *  These attributes can be used when selecting a particular bitrate for download.
 *  If all you need are the bitrate values, use -[variantBitratesForVideo:completion:].
 *
 * @param video The BCOVVideo object from Video Cloud. The video object should
 *  contain a valid online HLS source.
 *
 * @param completionHandler Block that receives the array of variant attributes
 *  NSDictionary objects if the request is successfully made. If there is an error,
 *  `variantAttributesDictionariesArray` will be nil, and `error` will report any NSError.
 *
 *  The completion handler is not called on any specific thread. You should switch to
 *  the main thread if you need to perform any UI work. It may be called
 *  synchronously or asynchronously.
 */
- (void)variantAttributesDictionariesForVideo:(BCOVVideo *)video
                                   completion:(void (^)(NSArray<NSDictionary *> *variantAttributesDictionariesArray, NSError *error))completionHandler;

/**
 * @abstract Retrieve an array of NSDictionary objects, one for each alternative rendition
 *  in the specified online HLS video. Alternative renditions include captions,
 *  subtitles, and secondary audio tracks.
 *
 * @discussion Each dictionary contains a key:value pair for each of the rendition's
 *  attributes as specified by its corresponding EXT-X-MEDIA tag in the
 *  HLS manifest. These attributes can be used to determine what languages are
 *  available for text and audio tracks, so that these languages can be presented to
 *  the end user, or selected for download yourself based on the locale or some other
 *  criteria.
 *
 * @param video The BCOVVideo object from Video Cloud. The video object should contain
 *  a valid online HLS source.
 *
 * @param completionHandler A block that receives the array of rendition attributes NSDictionary
 *  objects if the request is successfully made. If there is an error,
 *  `alternativeRenditionAttributesDictionariesArray` will be nil, and `error`
 *  will report any NSError.
 *
 *  The completion handler is not called on any specific
 *  thread. You should switch to the main thread if you need to perform
 *  any UI work. It may be called synchronously or asynchronously.
 */
- (void)alternativeRenditionAttributesDictionariesForVideo:(BCOVVideo *)video
                                                completion:(void (^)(NSArray<NSDictionary *> *alternativeRenditionAttributesDictionariesArray, NSError *error))completionHandler;

/**
 * @abstract Retrieve an array of available bitrates for the specified online HLS video.
 *
 * @discussion The array will be sorted from smallest to largest bitrate.
 *
 * @param video The BCOVVideo object from Video Cloud. The video object should
 *  contain a valid online HLS source.
 *
 * @param completionHandler A block that receives the array of bitrates if the
 *  request is successfully made. If there is an error, `bitrates` will be nil,
 *  and `error` will report any NSError.
 *
 *  The completion handler is not called on any specific thread. You should switch
 *  to the main thread if you need to perform any UI work. It may be called
 *  synchronously or asynchronously.
 */
- (void)variantBitratesForVideo:(BCOVVideo *)video
                     completion:(void (^)(NSArray<NSNumber *> *bitrates, NSError *error))completionHandler;

/**
 * @abstract Convert an offline video token into a playable BCOVVideo object.
 *
 * @discussion The returned BCOVVideo also contains all the new properties listed above,
 *  such as the downloaded thumbnail and poster image file paths, FairPlay
 *  license expiration date, download start and end times, and more.
 *
 *  If the downloadState of the video is `BCOVOfflineVideoDownloadStateCompleted` then
 *  the video associated with the token will be cached. If you need to clear the cache for
 *  any reason you can call `clearOfflineVideoCache` on `BCOVOfflineVideoManager`.
 *
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 */
- (BCOVVideo *)videoObjectFromOfflineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Clears cache of offline BCOVVideo objects
 *
 * @discussion When `videoObjectFromOfflineVideoToken:` is used with a video
 * which has a downloadState of `BCOVOfflineVideoDownloadStateCompleted`then
 * BCOVOfflienVideoManager will cache that object to increase performance. This method
 * will clean out the cache so that the next time `videoObjectFromOfflineVideoToken:` is called
 * a brand new BCOVVideo object will be created.
 */
- (void)clearOfflineVideoCache;

#pragma mark - FairPlay DRM

/**
 * @abstract Preload the FairPlay license before a video download begins.
 *
 * @discussion This will return an error if the video does not have a FairPlay source.
 *  When downloading multiple FairPlay-protected videos, you should call this
 *  method for each video to acquire a license for each one before beginning
 *  any of the downloads. This ensures that videos can be properly stored even
 *  when the downloads are initiated in the background.
 *
 * @param video BCOVVideo to be downloaded. The video should have a source
 *  that uses FairPlay encryption and the HTTPS scheme.
 *
 * @param parameters NSDictionary of parameters used in this download request.
 *  Valid parameters are:
 *  kBCOVFairPlayLicensePurchaseKey, kBCOVFairPlayLicenseRentalDurationKey.
 *
 * @param completionHandler Block that receives the new offlineVideoToken after the request
 *  is successfully made. If there is an error, offlineVideoToken will
 *  be nil, and error will report any NSError.
 */
- (void)preloadFairPlayLicense:(BCOVVideo *)video
                    parameters:(NSDictionary *)parameters
                    completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;

/**
 * @abstract Initiate a request for a new FairPlay license.
 *
 * @discussion You can request a new FairPlay license any time after the initial license has been acquired.
 *
 *  In the parameters you can specify a new rental duration, or you can convert a rental license
 *  to a purchase license.
 *
 *  The video does not need to be re-downloaded to use a new FairPlay license, but you do need
 *  to retrieve a new video object from the Playback API (either directly or through
 *  the BCOVPlaybackService class). If the referenced video is no longer available through the Playback API,
 *  you can use a substantially similar video, meaning the video should be from the same account,
 *  and also have the same FairPlay configuration.
 *
 *  You should not specify a bitrate in the parameters. To change the bitrate you need to delete
 *  the current download, and then initiate a completely new download at the new bitrate.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video for which to acquire a new license.
 *
 * @param video BCOVVideo object for an online video object retrieved through the Playback API
 *  or the BCOVPlaybackService class. This video must not have been created by '-videoObjectFromOfflineVideoToken:'.
 *
 * @param parameters NSDictionary of parameters used in this license renewal request.
 *  May be nil. Valid parameters are: kBCOVFairPlayLicensePurchaseKey,
 *  kBCOVFairPlayLicenseRentalDurationKey.
 *
 * @param completionHandler A block that is called after the license renewal request has completed.
 *  If the request resulted in an error, it will be returned here as an NSError.
 *  The offlineVideoToken parameter will be the same offline video token that was
 *  passed in as the first parameter.
 */
- (void)renewFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken
                       video:(BCOVVideo *)video
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;

/**
 * @abstract Initiate a request for a new FairPlay license.
 *
 * @discussion You can request a new FairPlay license any time after the initial license has been acquired.
 *
 *  In the parameters you can specify a new rental duration, or you can convert a rental license
 *  to a purchase license.
 *
 *  The video does not need to be re-downloaded to use a new FairPlay license, but you do need
 *  to retrieve a new video object from the Playback API (either directly or through
 *  the BCOVPlaybackService class). If the referenced video is no longer available through the Playback API,
 *  you can use a substantially similar video, meaning the video should be from the same account,
 *  and also have the same FairPlay configuration.
 *
 *  You should not specify a bitrate in the parameters. To change the bitrate you need to delete
 *  the current download, and then initiate a completely new download at the new bitrate.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video for which to acquire a new license.
 *
 * @param video BCOVVideo object for an online video object retrieved through the Playback API
 *  or the BCOVPlaybackService class. This video must not have been created by '-videoObjectFromOfflineVideoToken:'.
 *
 * @param authToken The authentication token with which to validate the video's license
 *
 * @param parameters NSDictionary of parameters used in this license renewal request.
 *  May be nil. Valid parameters are: kBCOVFairPlayLicensePurchaseKey,
 *  kBCOVFairPlayLicenseRentalDurationKey.
 *
 * @param completionHandler A block that is called after the license renewal request has completed.
 *  If the request resulted in an error, it will be returned here as an NSError.
 *  The offlineVideoToken parameter will be the same offline video token that was
 *  passed in as the first parameter.
 */
- (void)renewFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken
                       video:(BCOVVideo *)video
                   authToken:(NSString *)authToken
                  parameters:(NSDictionary *)parameters
                  completion:(void (^)(BCOVOfflineVideoToken offlineVideoToken, NSError *error))completionHandler;

/**
 * @abstract This method is used to add a FairPlay application certificate to the
 *  Offline Video Manager's list of available FairPlay application certificates.
 *
 * @discussion Certificates will be retained for the life of the application.
 *  To remove a certificate, add the same identifier with a nil as the
 *  certificate data.
 *
 *  If you are using Dynamic Delivery, application certificates are retrieved
 *  automatically by the FairPlay plugin, so this method is not needed.
 *  You can, however, use this method to pre-load your application certificate
 *  to speed up playback of the first FairPlay-encrypted video.
 *
 *  Certificates are stored and re-used for subsequent videos.
 *
 * @param applicationCertificateData The FairPlay application certificate in an NSData object.
 *  If set to nil, any existing application certificate for the
 *  given identifier will be removed.
 *
 * @param identifier A string used to locate the application certificate.
 *
 *  This string may not be nil.
 *
 *  For Dynamic Delivery, the identifier must be the URL that was used to
 *  retrieve this certificate.
 *
 *  For legacy Video Cloud accounts, this should be set to kBCOVDefaultFairPlayApplicationCertificateIdentifier
 *  to apply to all accounts.
 *
 *  If you are using multiple legacy Video Cloud accounts, set this param to the acount ID.
 */
- (void)addFairPlayApplicationCertificate:(NSData *)applicationCertificateData
                               identifier:(NSString *)identifier;

/**
 * @abstract Invalidate the FairPlay license for the specified offline video token.
 *
 * @discussion This method deletes the FairPlay license for the video associated with the
 *  offline video token, if there is one.
 *
 *  Attempts to play back a FairPlay-protected video without a license will result
 *  in a kBCOVOfflineVideoManagerErrorCodeInvalidLicense error.
 *
 *  If needed you can request a new FairPlay license for the video after it has been deleted.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded
 *  video whose license will be invalidated.
 */
- (void)invalidateFairPlayLicense:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Returns an NSDate representing the expiration of the FairPlay license for the video
 * associated with the offline video token.
 *
 * @discussion Returns NSDate.distantFuture for "purchase" licenses.
 *
 *  Returns NSDate.distantFuture if the video is not encrypted with FairPlay.
 *
 *  Returns nil if the video has no FairPlay license.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 *
 * @return NSDate representing the expiration of the FairPlay license, NSDate.distantFuture
 *  for purchase licenses or clear (no FairPlay) videos, or nil if there is no license.
 */
- (NSDate *)fairPlayLicenseExpiration:(BCOVOfflineVideoToken)offlineVideoToken;

#pragma mark - Secondary track downloading support

/**
 * @abstract Returns the media selection group for a downloaded video specified
 * by the offline video token.
 *
 * @discussion The downloaded video must be complete, or this method will return nil.
 *
 * @param mediaCharacteristic The media characteristic that you are interested in.
 *  Supported values are AVMediaCharacteristicAudible and AVMediaCharacteristicLegible.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 *  Must not refer to a download in progress.
 */
- (AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(NSString *)mediaCharacteristic
                                                   offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract Returns the downloaded media selection options for a downloaded video specified
 *  by the offline video token, as reported by the AVMediaCache for the
 *  underlying AVURLAsset. May return nil.
 *
 * @param mediaCharacteristic The media characteristic that you are interested in.
 *  Supported values are AVMediaCharacteristicAudible and AVMediaCharacteristicLegible.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 */
- (NSArray<AVMediaSelectionOption *> *)downloadedMediaSelectionOptionsForMediaCharacteristic:(NSString *)mediaCharacteristic
                                                                           offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken;

@end
