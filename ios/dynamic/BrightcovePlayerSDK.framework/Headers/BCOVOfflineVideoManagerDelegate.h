//
// BCOVOfflineVideoManagerDelegate.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <BrightcovePlayerSDK/BCOVOfflineVideoManagerTypes.h>

@class AVAssetDownloadTask, BCOVPlaybackService, BCOVVideo;

/**
 * Conform to this protocol to receive information about each video and
 * video track download.
 */
@protocol BCOVOfflineVideoManagerDelegate<NSObject>

#if !TARGET_OS_TV

@optional

/**
 * @abstract This method is called after the background NSURLSessionConfiguration object
 * is created, and before it's used to create the shared AVAssetDownloadURLSession
 * object that's used to download videos.
 *
 * @discussion You can use this configuration object to set various options specified for the
 * NSURLSessionConfiguration in NSURLSession.h, such as the `discretionary` flag, or
 * the `HTTPMaximumConnectionsPerHost` setting.
 *
 * You should *not* set the `allowsCellularAccess` property; that is set in the individual
 * download tasks.
 */
- (void)didCreateSharedBackgroundSesssionConfiguration:(NSURLSessionConfiguration *)backgroundSessionConfiguration;

/**
 * @abstract Receive progress notification about track downloads in progress for a downloaded video.
 *
 * @discussion If you want to pause/resume/cancel the task, you should use the methods available
 *  in the BCOVOfflineVideoManager to perform those actions.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 *
 * @param aggregateDownloadTask The AVAggregateAssetDownloadTask for this set of video track downloads
 *
 * @param progressPercent How far along the download has progressed, expressed as a percentage,
 *  for this individual AVMediaSelection.
 *
 * @param mediaSelection The AVMediaSelection for which this progress is reported.
 */
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
    aggregateDownloadTask:(AVAggregateAssetDownloadTask *)aggregateDownloadTask
            didProgressTo:(NSTimeInterval)progressPercent
        forMediaSelection:(AVMediaSelection *)mediaSelection;

/**
 * @abstract Receive progress notification about track downloads in progress for a downloaded video.
 *
 * @discussion If you want to pause/resume/cancel the task, you should use the methods available
 *  in the BCOVOfflineVideoManager to perform those actions. This delegate method will called when
 *  downloading with an AVAssetDownloadConfiguration.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 *
 * @param assetDownloadTask The AVAssetDownloadTask for this set of video track downloads
 *
 * @param progressPercent How far along the download has progressed, expressed as a percentage,
 *  for this individual AVMediaSelection.
 */
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
        assetDownloadTask:(AVAssetDownloadTask *)assetDownloadTask
            didProgressTo:(NSTimeInterval)progressPercent API_AVAILABLE(ios(15.0));
/**
 * @abstract Receive confirmation of which AVAssetVariants will be downloaded.
 *
 * @discussion This delegate method will called when downloading with an AVAssetDownloadConfiguration.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 *
 * @param assetDownloadTask The AVAssetDownloadTask for this set of video track downloads
 *
 * @param variants An array of AVAssetVariant objects that will be downloaded.
 */
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
        assetDownloadTask:(AVAssetDownloadTask *)assetDownloadTask
     willDownloadVariants:(NSArray<AVAssetVariant *> *)variants API_AVAILABLE(ios(15.0));

/**
 * @abstract This method is called when an individual track download is complete.
 *
 * @param offlineVideoToken Offline video token used to identify the offline video
 *  for which tracks are being downloaded.
 *
 * @param mediaSelection The AVMediaSelection that has finished downloading.
 */
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
didFinishMediaSelectionDownload:(AVMediaSelection *)mediaSelection;

/**
 * @abstract This method is called when a download is complete.
 *
 * @discussion If an error occurred during the download, error will be non-nil.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 *
 * @param error NSError encountered during the download process. nil if no error.
 */
- (void)offlineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken
didFinishDownloadWithError:(NSError *)error;

/**
 * @abstract This method is called when the static images (thumbnail and poster) associated
 * with a video are downloaded to storage.
 *
 * @discussion File URLs for the downloaded images are stored as properties on a BCOVVideo
 * created from the offline video token using -[videoObjectFromOfflineVideoToken:]
 * The properties are retrieved using the kBCOVOfflineVideoThumbnailFilePath and
 * kBCOVOfflineVideoPosterFilePath keys.
 *
 * This method will be called even if no images could be retrieved, so be sure to
 * check the UIImage you create from the poster and thumbnail paths. The file
 * paths will be present, but there may be no images stored at those locations.
 *
 * @param offlineVideoToken Offline video token used to identify the downloaded video.
 */
- (void)didDownloadStaticImagesWithOfflineVideoToken:(BCOVOfflineVideoToken)offlineVideoToken;

/**
 * @abstract This method is called when cleaning up stranded downloads.
 *
 * @discussion Downloads can be stranded if you force-quit an app during a download,
 * or reboot while the app is suspended.
 * You do not need to implement this method unless you are starting your own
 * video downloads outside the Brightcove SDK and don't want your videos deleted.
 * This method is called when a video package is flagged for deletion, meaning
 * there is no record of it in the Brightcove SDK.
 *
 * If the file is one you recognize, you should return NO.
 * Otherwise, returning YES will cause the video package to be deleted.
 * If you do not implement this method, stranded downloads will
 * be deleted by default.
 *
 * @param videoPackagePath Path to video package directory that is flagged as stranded.
 */
- (BOOL)shouldDeleteVideoPackage:(NSString *)videoPackagePath;

/**
 * @abstract This method is called when the app is activated and offline video
 * storage changed while the app was not running or was in the background, for
 * example when the user deletes downloaded videos via the device Storage settings
 * in the General settings of the Settings app.
 *
 * @discussion When called, you should update your UI to reflect the changes in
 * offline storage.
 *
 * Detecting changes to offline video storage occurs whenever the app becomes active.
 *
 * This method is called on the main thread.
 */
- (void)offlineVideoStorageDidChange;

/**
 * Called when the TTL token for the current source's manifest has expired and needs to be refreshed.
 * You will want to implement this delegate method if you are using a BCOVPlaybackService with
 * a custom URL.
 *
 * If you are using the default initilaizer for BCOVPlaybackService, `initWithAccountId:policyKey:`
 * you do not need to implement this delegate method.
 *
 * If you return `nil`, or do not implement this method, an instance of BCOVPlaybackService will be
 * created internally with the `initWithAccountId:policyKey:` initializer.
 *
 * @param video The video that requires a TTL token refresh.
 *
 * @return An instance of BCOVPlaybackService that will be used to update the manifest TTL token.
 */
- (BCOVPlaybackService *)playbackServiceForManifestURLTTLUpdateForVideo:(BCOVVideo *)video;

#endif

@end
