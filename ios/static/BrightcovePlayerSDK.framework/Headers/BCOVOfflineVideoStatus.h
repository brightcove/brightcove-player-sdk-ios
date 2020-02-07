//
// BCOVOfflineVideoStatus.h
// BrightcovePlayerSDK
//
// Copyright (c) 2020 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

#import <BrightcovePlayerSDK/BCOVOfflineVideoManagerTypes.h>

@class AVAssetDownloadTask, AVAggregateAssetDownloadTask;

/**
 * BCOVOfflineVideoStatus
 * This object keeps track of various pieces of information related
 * to video downloads.
 */
@interface BCOVOfflineVideoStatus : NSObject <NSCopying>

/**
 * Offline video token used to identify the downloaded video
 */
@property (nonatomic, readonly) BCOVOfflineVideoToken offlineVideoToken;

/**
 * The state of the current download
 */
@property (nonatomic, readonly) BCOVOfflineVideoDownloadState downloadState;

/**
 * The NSDate that this download was requested (not when it started)
 */
@property (nonatomic, readonly) NSDate *downloadStartTime;

/**
 * The NSDate that this download finished (successfully, cancelled, or with an error)
 */
@property (nonatomic, readonly) NSDate *downloadEndTime;

/**
 * The progress of the download, expressed as a percentage
 */
@property (nonatomic, readonly) CGFloat downloadPercent;

#if !TARGET_OS_TV
/**
 * The AVAssetDownloadTask associated with this download.
 * Will be set to nil once the download has completed.
 */
@property (nonatomic, readonly) AVAssetDownloadTask *downloadTask;

/**
 * The AVAggregateAssetDownloadTask associated with this tracks download.
 * Will be set to nil once the download has completed.
 *
 * **Available in iOS 11.0+**
 */
@property (nonatomic, readonly) AVAggregateAssetDownloadTask *aggregateDownloadTask __attribute__((availability(ios,introduced=11.0)));

#else

@property (nonatomic, readonly) id downloadTask;
@property (nonatomic, readonly) id aggregateDownloadTask;

#endif

/**
 * The NSError associated with this download if a failure occurs.
 */
@property (nonatomic, readonly) NSError *error;

@end

