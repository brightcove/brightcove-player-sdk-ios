//
// BCOVVideoErrorCodes.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

/*
 *
 */
static NSString * const kBCOVVideoErrorCodeBadRequest = @"BAD_REQUEST";

/*
* The same parameter name was provided more than once in the request.
*/
static NSString * const kBCOVVideoErrorCodeDuplicateParameters = @"DUPLICATE_PARAMETERS";

/*
*
*/
static NSString * const kBCOVVideoErrorCodeAccessDenied = @"ACCESS_DENIED";

/*
* A JWT is required by the Playback Rights but was not provided.
*/
static NSString * const kBCOVVideoErrorCodeTokenRequired = @"TOKEN_REQUIRED";

/*
* The JWT provided did not pass validation.
*/
static NSString * const kBCOVVideoErrorCodeTokenValidation = @"TOKEN_VALIDATION";

/*
*
*/
static NSString * const kBCOVVideoErrorCodeForbidden = @"FORBIDDEN";

/*
* The account id in the policy key does not match the account in the api request.
*/
static NSString * const kBCOVVideoErrorCodeAccountID = @"ACCOUNT_ID";

/*
* The video is restricted from playing in the current geo region; the message will contain additional information about the specific issue.
*/
static NSString * const kBCOVVideoErrorCodeClientGeo = @"CLIENT_GEO";

/*
* The video is restricted at the current IP address.
*/
static NSString * const kBCOVVideoErrorCodeClientIP = @"CLIENT_IP";

/*
* The video is restricted from playing on the current domain.
*/
static NSString * const kBCOVVideoErrorCodeDomain = @"DOMAIN";

/*
* The JWT does not allow for playback based on offers available in the video.
*/
static NSString * const kBCOVVideoErrorCodeOffers = @"OFFERS";

/*
* The JWT does not allow for playback based on tags available in the video.
*/
static NSString * const kBCOVVideoErrorCodeTags = @"TAGS";

/*
* For a single video request, the video exists, but is not allowed to be played now.
*/
static NSString * const kBCOVVideoErrorCodeVideoNotPlayable = @"VIDEO_NOT_PLAYABLE";

/*
*
*/
static NSString * const kBCOVVideoErrorCodeNotFound = @"NOT_FOUND";

/*
* The requested video is not available.
*/
static NSString * const kBCOVVideoErrorCodeVideoNotFound = @"VIDEO_NOT_FOUND";

/*
* The requested playlist is not available.
*/
static NSString * const kBCOVVideoErrorCodePlaylistNotFound = @"PLAYLIST_NOT_FOUND";

/*
* Only GET, HEAD and OPTIONS are allowed for this api.
*/
static NSString * const kBCOVVideoErrorCodeMethodNotAllowed = @"METHOD_NOT_ALLOWED";

/*
* Internal server error.
*/
static NSString * const kBCOVVideoErrorCodeServerError = @"SERVER_ERROR";

/*
* Got a bad response from a backend server.
*/
static NSString * const kBCOVVideoErrorCodeAccountRetrieveFailure = @"ACCOUNT_RETRIEVE_FAILURE";

/*
*
*/
static NSString * const kBCOVVideoErrorCodeVideoRetieveFailure = @"VIDEO_RETRIEVE_FAILURE";

/*
*
*/
static NSString * const kBCOVVideoErrorCodeVideoUrlsRetrieveFailure = @"VIDEO_URLS_RETRIEVE_FAILURE";

/*
*
*/
static NSString * const kBCOVVideoErrorCodePlaylistRetrieveFailure = @"PLAYLIST_RETRIEVE_FAILURE";

/*
* Cannot retrive playback right from cloudfront
*/
static NSString * const kBCOVVideoErrorCodePlaybackRightRetrieveFailure = @"PLAYBACK_RIGHT_RETRIEVE_FAILURE";

/*
*
*/
static NSString * const kBCOVVideoErrorCodePlaylistVideosRetrieveFailure = @"PLAYLIST_VIDEOS_RETRIEVE_FAILURE";

/*
* Failed to get license from Fabric License Server for this video.
*/
static NSString * const kBCOVVideoErrorCodeLicenseRetreiveFailure = @"LICENSE_RETRIEVE_FAILURE";

/*
* Failed to get offers from Adamas API for this video.
*/
static NSString * const kBCOVVideoErrorCodeOffersRetreiveFailure = @"OFFERS_RETRIEVE_FAILURE";

/*
* Failed to retrieve Playback Rights for this video.
*/
static NSString * const kBCOVVideoErrorCodeRightsRetrieveFailure = @"RIGHTS_RETRIEVE_FAILURE";

/*
* Returned this response from a backend server.
*/
static NSString * const kBCOVVideoErrorCodeServiceUnavailable = @"SERVICE_UNAVAILABLE";

/*
* Either a backend server or one of the servers they rely on timed out.
*/
static NSString * const kBCOVVideoErrorCodeServerTimeout = @"SERVER_TIMEOUT";
