//
// BCOVOfflineVideoManagerTypes.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

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
    BCOVOfflineVideoDownloadStateError = 5,
    
    /* License has been preloaded, but the video download has not yet been requested */
    BCOVOfflineVideoDownloadLicensePreloaded = 6,
    
    /* Deprecated: Use BCOVOfflineVideoDownloadStateRequested instead.  */
    BCOVOfflineVideoDownloadStateTracksRequested __attribute__((deprecated)) = 7,
    
    /*  Deprecated: Use BCOVOfflineVideoDownloadStateDownloading instead. */
    BCOVOfflineVideoDownloadStateTracksDownloading __attribute__((deprecated)) = 8,
    
    /*  Deprecated: Use BCOVOfflineVideoDownloadStateSuspended instead. */
    BCOVOfflineVideoDownloadStateTracksSuspended __attribute__((deprecated)) = 9,
    
    /*  Deprecated: Use BCOVOfflineVideoDownloadStateCancelled instead. */
    BCOVOfflineVideoDownloadStateTracksCancelled __attribute__((deprecated)) = 10,
    
    /*  Deprecated: Use BCOVOfflineVideoDownloadStateCompleted instead. */
    BCOVOfflineVideoDownloadStateTracksCompleted __attribute__((deprecated)) = 11,
    
    /*  Deprecated: Use BCOVOfflineVideoDownloadStateError instead. */
    BCOVOfflineVideoDownloadStateTracksError __attribute__((deprecated)) = 12
};

typedef void (^BCOVOfflineVideoLicenseCompletionCallback)(BCOVOfflineVideoToken, NSError *);
