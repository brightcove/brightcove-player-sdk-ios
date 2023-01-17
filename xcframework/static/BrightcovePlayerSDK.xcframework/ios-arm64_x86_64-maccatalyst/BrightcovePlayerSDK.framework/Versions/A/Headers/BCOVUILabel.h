//
// BCOVUILabel.h
// BrightcovePlayerSDK
//
// Copyright (c) 2023 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * BCOVUILabel
 * The BCOVUILabel is a subclass of UILabel which has
 * an extra NSString property that will be read by VoiceOver
 * as a prefix to the labels value. For example the duration
 * label can be read by VO as "Duration 03:47" and still only
 * visibly read as "03:47"
 */
@interface BCOVUILabel : UILabel

/**
 * accessibilityLabelPrefix is the string that will be
 * read by VoiceOver before the text value of the label itself
 */
@property (nonatomic, strong) NSString *accessibilityLabelPrefix;

@end

NS_ASSUME_NONNULL_END
