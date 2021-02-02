//
// BCOVGlobalConfiguration.h
// BrightcovePlayerSDK
//
// Copyright (c) 2021 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The Global Configuration contains properties which are utilized throughout
 * the Native Player SDK. If your app requires custom configuration,
 * set the necessary properties of the Global Configuration BEFORE using any
 * of the services of the Native Player SDK.
 */
@interface BCOVGlobalConfiguration : NSObject

/**
 * BCOVGlobalConfiguration is a global singleton object. Reference it using:
 *
 *   BCOVGlobalConfiguration *config = [BCOVGlobalConfiguration sharedConfig];
 */
+ (BCOVGlobalConfiguration *)new NS_UNAVAILABLE;
- (BCOVGlobalConfiguration *)init NS_UNAVAILABLE;

/**
 * Returns the shared Global Configuration singleton.
 */
+ (BCOVGlobalConfiguration *)sharedConfig;

#pragma mark - China Delivery

/**
 * Sets a custom, fully qualified domain name (FQDN) for Catalog API, Metrics and
 * Analytics collection services. This method is to be used specifically for
 * reliable content delivery in China and requires particular account arrangements.
 * Setting this property in any other situation will result in unknown behavior.
 */
@property (nonatomic, nullable) NSString *chinaProxyDomain;

@end

NS_ASSUME_NONNULL_END
