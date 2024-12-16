//
// BrightcovePlayerSDK.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// Open Source Software attributions
#import <BrightcovePlayerSDK/BCOVAttributions.h>

// Playback
#import <BrightcovePlayerSDK/BCOVBasicSessionProvider.h>
#import <BrightcovePlayerSDK/BCOVCuePointProgressPolicy.h>
#import <BrightcovePlayerSDK/BCOVPlaybackController.h>
#import <BrightcovePlayerSDK/BCOVPlaybackSession.h>
#import <BrightcovePlayerSDK/BCOVPlaybackSessionProvider.h>

// Values
#import <BrightcovePlayerSDK/BCOVCuePoint.h>
#import <BrightcovePlayerSDK/BCOVCuePointCollection.h>

// Player UI
#if !TARGET_OS_TV
#import <BrightcovePlayerSDK/BCOVPUIAdControlView.h>
#import <BrightcovePlayerSDK/BCOVPUIBasicControlView.h>
#import <BrightcovePlayerSDK/BCOVPUIButton.h>
#import <BrightcovePlayerSDK/BCOVPUICommon.h>
#import <BrightcovePlayerSDK/BCOVPUILayoutView.h>
#import <BrightcovePlayerSDK/BCOVPUIPlayerView.h>
#import <BrightcovePlayerSDK/BCOVPUISlider.h>

// Offline Video Management
#import <BrightcovePlayerSDK/BCOVOfflineVideoManager.h>
#endif

// TV UI
#if TARGET_OS_TV
#import <BrightcovePlayerSDK/BCOVTVCommon.h>
#import <BrightcovePlayerSDK/BCOVTVControlsView.h>
#import <BrightcovePlayerSDK/BCOVTVPlayerView.h>
#import <BrightcovePlayerSDK/BCOVTVProgressView.h>
#endif

// Interactivity
#import <BrightcovePlayerSDK/BCOVInteractivityHandler.h>
#import <BrightcovePlayerSDK/BCOVInteractivityProject.h>

