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

// Playback API
#import <BrightcovePlayerSDK/BCOVPlaybackService.h>
#import <BrightcovePlayerSDK/BCOVPlaybackServiceRequestFactory.h>
#import <BrightcovePlayerSDK/NSDictionary-BCOVURLSupport.h>

// Management
#import <BrightcovePlayerSDK/BCOVGlobalConfiguration.h>
#import <BrightcovePlayerSDK/BCOVPlayerSDKManager.h>

// Playback
#import <BrightcovePlayerSDK/BCOVBasicSessionProvider.h>
#import <BrightcovePlayerSDK/BCOVCuePointProgressPolicy.h>
#import <BrightcovePlayerSDK/BCOVPlaybackController.h>
#import <BrightcovePlayerSDK/BCOVPlaybackSession.h>
#import <BrightcovePlayerSDK/BCOVPlaybackSessionProvider.h>

// FairPlay
#import <BrightcovePlayerSDK/BCOVFPSAuthorizationProxy.h>
#import <BrightcovePlayerSDK/BCOVFPSBrightcoveAuthProxy.h>
#import <BrightcovePlayerSDK/BCOVFPSComponent.h>
#import <BrightcovePlayerSDK/BCOVFairPlayManager.h>

// Sidecar Subtitles
#import <BrightcovePlayerSDK/BCOVSSComponent.h>

// Values
#import <BrightcovePlayerSDK/BCOVCuePoint.h>
#import <BrightcovePlayerSDK/BCOVCuePointCollection.h>
#import <BrightcovePlayerSDK/BCOVPlaylist.h>
#import <BrightcovePlayerSDK/BCOVSource.h>
#import <BrightcovePlayerSDK/BCOVVideo.h>

// Ads
#import <BrightcovePlayerSDK/BCOVAdvertising.h>

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

// Accessibility
#import <BrightcovePlayerSDK/BCOVUILabel.h>
