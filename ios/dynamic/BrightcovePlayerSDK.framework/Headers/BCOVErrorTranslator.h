//
// BCOVErrorTranslator.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BCOVErrorTranslator : NSObject

/**
 * Returns a human readable error code from an `NSError`
 *
 * @discussion The Brightcove iOS SDK has a number `NSError` objects that are created
 * in various instances, each one within a specific error domain with a specific error code.
 * This class can be used to translate one of these `NSError` object's error code into a
 * human readable string.
 *
 * @param error The NSError object to translate.
 * @return A readable error code. May be `nil` if the `NSError` is not an internal Brightcove error.
 */
+ (NSString * _Nullable)readableErrorCodeForError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
