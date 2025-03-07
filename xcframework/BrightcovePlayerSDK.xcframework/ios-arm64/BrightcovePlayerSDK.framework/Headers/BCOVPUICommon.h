//
// BCOVPUICommon.h
// BrightcovePlayerSDK
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

/**
 * Enumerations and values used throughout the PlayerUI.
 */

/**
 * Tags for buttons used by various BCOV control elements.
 */
typedef NS_ENUM(NSInteger, BCOVPUIViewTag) {

    /** Tag for unknown button. */
    BCOVPUIViewTagUnknown,

    /**  Tag for playback button. */
    BCOVPUIViewTagButtonPlayback        = 1,

    /** Tag for jump back button. */
    BCOVPUIViewTagButtonJumpBack        = 2,

    /** Tag for closed caption button. */
    BCOVPUIViewTagButtonClosedCaption   = 3,

    /** Tag for the screen mode (fullscreen) button. */
    BCOVPUIViewTagButtonScreenMode      = 4,

    /** Tag for the current (elapsed time) label. */
    BCOVPUIViewTagLabelCurrentTime      = 5,

    /** Tag for the time separator label. */
    BCOVPUIViewTagLabelTimeSeparator    = 6,

    /** Tag for the duration label. */
    BCOVPUIViewTagLabelDuration         = 7,

    /** Tag for the progress slider. */
    BCOVPUIViewTagSliderProgress        = 8,

    /** Tag for the external route (airplay) button */
    BCOVPUIViewTagViewExternalRoute     = 9,

    /** Tag for the "go to live" button. */
    BCOVPUIViewTagButtonLive            = 10,
    
    /** Tag for an empty control box. */
    BCOVPUIViewTagViewEmpty             = 11,
    
    /** Tag for the "Your video will resume..." button. */
    BCOVPUIViewTagButtonAdPodCountdown  = 12,
    
    /** Tag for the "Learn More" button. */
    BCOVPUIViewTagButtonLearnMore       = 13,
    
    /** Tag for the "Skip Ad" countdown button. */
    BCOVPUIViewTagButtonSkipAdCountdown = 14,
    
    /** Tag for the "Skip" button. */
    BCOVPUIViewTagViewButtonSkip        = 15,
    
    /** Tag for the Video 360 button. */
    BCOVPUIViewTagButtonVideo360        = 16,
    
    /** Tag for the "Preferred Bitrate" button. */
    BCOVPUIViewTagButtonPreferredBitrate    = 17,
    
    /** Tag for Picture-In-Picture button */
    BCOVPUIViewTagButtonPictureInPicture = 18,
    
    /** Tag that signifies the end of our reserved range. */
    BCOVPUIViewTagReservedEnd           = 200
};

/**
 * Distinct Icon types.
 */
typedef NS_ENUM(NSUInteger, BCOVPUIButtonIcon) {

    /** Play icon. */
    BCOVPUIButtonIconPlay,

    /** Pause icon. */
    BCOVPUIButtonIconPause,

    /** Jump back icon. */
    BCOVPUIButtonIconJumpBack,

    /** Zoom in icon. */
    BCOVPUIButtonIconZoomIn,

    /** Zoom out icon. */
    BCOVPUIButtonIconZoomOut,

    /** Closed Caption icon. */
    BCOVPUIButtonIconClosedCaption,

    /** External Route (airplay) icon */
    BCOVPUIButtonIconExternalRoute,
    
    /** Video 360 Options icon */
    BCOVPUIButtonIconVideo360,
    
    /** Preferred Bitrate icon **/
    BCOVPUIButtonIconPreferredBitrate,
    
    /** Reserved icon. */
    BCOVPUIButtonIconReserved,
};
