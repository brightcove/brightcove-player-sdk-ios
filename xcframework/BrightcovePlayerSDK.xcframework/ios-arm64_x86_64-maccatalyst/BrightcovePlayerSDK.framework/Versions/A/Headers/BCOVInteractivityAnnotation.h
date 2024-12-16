//
// BCOVInteractivityAnnotation.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, BCOVInteractivityAnnotationType)
{
    BCOVInteractivityAnnotationTypeImage,
    BCOVInteractivityAnnotationTypeText,
    BCOVInteractivityAnnotationTypeOnTime,
    BCOVInteractivityAnnotationTypeHotLink,
    BCOVInteractivityAnnotationTypeUnsupported
};

typedef NS_ENUM(NSUInteger, BCOVInteractivityAnnotationState)
{
    BCOVInteractivityAnnotationStateNew,
    BCOVInteractivityAnnotationStateView,
    BCOVInteractivityAnnotationStateEnded
};

typedef NS_ENUM(NSUInteger, BCOVInteractivityAnnotationTransition)
{
    BCOVInteractivityAnnotationTransitionFade,
    BCOVInteractivityAnnotationTransitionNone
};


typedef NSString *BCOVInteractivityAnnotationPosition NS_TYPED_ENUM;

static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionTop = @"top";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionTopRight = @"topRight";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionRight = @"right";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionBottomRight = @"bottomRight";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionBottom = @"bottom";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionTopLeft = @"topLeft";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionLeft = @"left";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionBottomLeft = @"bottomLeft";
static BCOVInteractivityAnnotationPosition const BCOVInteractivityAnnotationPositionNone = @"none";

NS_ASSUME_NONNULL_END
