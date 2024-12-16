//
// BCOVInteractivityProject.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>
#import <BrightcovePlayerSDK/BCOVInteractivityHandler.h>

@class BCOVInteractivityAnnotation;

NS_ASSUME_NONNULL_BEGIN

@interface BCOVInteractivityProject : NSObject

+ (instancetype _Nullable)initWithJSON:(NSDictionary *)json;

@property (nonatomic, copy) NSString *projectId;
@property (nonatomic, copy, nullable) NSString *sessionId;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, strong) NSArray<BCOVInteractivityAnnotation *> *annotations;
@property (nonatomic, weak, nullable) BCOVInteractivityHandler *handler;

- (NSArray<BCOVInteractivityAnnotation *> *)annotationsAtTime:(NSTimeInterval)time;

@end

NS_ASSUME_NONNULL_END
