//
// BCOVInteractivityAnnotation.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

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

typedef NSString *BCOVInteractivtyAnnotationPosition NS_TYPED_ENUM;

extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionTop;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionTopRight;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionRight;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionBottomRight;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionBottom;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionTopLeft;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionLeft;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionBottomLeft;
extern BCOVInteractivtyAnnotationPosition const BCOVInteractivityAnnotationPositionNone;

@interface BCOVInteractivityAnnotation : NSObject

+ (NSArray<BCOVInteractivityAnnotation *> *)annotationsFromJSONArray:(NSArray<NSDictionary *> *)jsonArray;
+ (instancetype)initWithJSON:(NSDictionary *)json;

@property (nonatomic, strong, nullable) UIView *annotationView;
@property (nonatomic, assign) BCOVInteractivityAnnotationType type;
@property (nonatomic, assign) BCOVInteractivityAnnotationState state;
@property (nonatomic, assign) BCOVInteractivityAnnotationTransition transition;

// Properties from API
@property (nonatomic, copy) NSString *annotationId;
@property (nonatomic, assign) NSTimeInterval startTime;
@property (nonatomic, assign) NSTimeInterval duration;
@property (nonatomic, copy, nullable) NSString *rawType;
@property (nonatomic, copy, nullable) NSString *text;
@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) NSString *left;
@property (nonatomic, copy, nullable) NSString *top;
@property (nonatomic, copy, nullable) NSString *width;
@property (nonatomic, copy, nullable) NSString *height;
@property (nonatomic, copy, nullable) NSString *url;
@property (nonatomic, copy, nullable) NSString *precondition;
@property (nonatomic, copy, nullable) NSString *command;
@property (nonatomic, copy, nullable) NSString *mode;
@property (nonatomic, strong, nullable) NSDictionary *commandData;
@property (nonatomic, strong, nullable) NSDictionary *onClick;
@property (nonatomic, copy, nullable) NSString *gotoTrack;
@property (nonatomic, copy, nullable) NSString *backgroundColor;

@end

NS_ASSUME_NONNULL_END
