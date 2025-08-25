//
// BrightcovePlayerSDK.h
// BrightcovePlayerSDK
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// Open Source Software attributions
#import <BrightcovePlayerSDK/BCOVAttributions.h>

// Playback
#import <BrightcovePlayerSDK/BCOVBasicSessionProvider.h>
#import <BrightcovePlayerSDK/BCOVSessionProviderExtension.h>
#import <BrightcovePlayerSDK/BCOVCuePointProgressPolicy.h>
#import <BrightcovePlayerSDK/BCOVPlaybackController.h>
#import <BrightcovePlayerSDK/BCOVPlaybackSessionProvider.h>

// Values
#import <BrightcovePlayerSDK/BCOVPlaybackSessionConstants.h>

// Player UI
#if !TARGET_OS_TV
#import <BrightcovePlayerSDK/BCOVPUIAdControlView.h>
#import <BrightcovePlayerSDK/BCOVPUIBasicControlView.h>
#import <BrightcovePlayerSDK/BCOVPUIPlayerView.h>

// Offline Video Management
#import <BrightcovePlayerSDK/BCOVOfflineVideoManagerTypes.h>
#endif

// TV UI
#if TARGET_OS_TV
#import <BrightcovePlayerSDK/BCOVTVCommon.h>
#import <BrightcovePlayerSDK/BCOVTVControlsView.h>
#import <BrightcovePlayerSDK/BCOVTVPlayerView.h>
#import <BrightcovePlayerSDK/BCOVTVProgressView.h>
#import <BrightcovePlayerSDK/BCOVTVTrackSelectionButton.h>
#endif

// Interactivity
#import <BrightcovePlayerSDK/BCOVInteractivityAnnotation.h>

