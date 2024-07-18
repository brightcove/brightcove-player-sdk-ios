//
// BCOVInteractivityControl.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <BrightcovePlayerSDK/BCOVInteractivityAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BCOVInteractivityControl : UIControl

// The annotation associatd with this control
@property (nonatomic, weak) BCOVInteractivityAnnotation *annotation;

// The UIImageView used for image annotations
@property (nonatomic, strong, nullable) UIImageView *imageView;

// The UILabel used for text annotations
@property (nonatomic, strong, nullable) UILabel *textLabel;

@end

NS_ASSUME_NONNULL_END
