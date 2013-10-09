//
// NSDictionary+BCOVURLSupport.h
// BCOVPlayerSDK
//
// Copyright (c) 2013 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>


@interface NSDictionary (BCOVURLSupport)

/**
 * Constructs a string of key/value pairs that have been UTF-8 encoded for a
 * URL.
 *
 * @return The URL encoded string form of this dictionary.
 */
- (NSString *)bcov_UTF8EncodedRequestParameterString;

@end

