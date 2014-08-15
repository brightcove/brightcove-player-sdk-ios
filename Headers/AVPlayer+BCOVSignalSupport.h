//
// AVPlayer+BCOVSignalSupport.h
// BCOVPlayerSDK
//
// Copyright (c) 2014 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <AVFoundation/AVFoundation.h>

#import "ReactiveCocoa.h"

@interface AVPlayer (Deprecated)
- (RACSignal *)bcov_periodicTimeObserverSignalForInterval:(CMTime)interval __attribute((deprecated("Use -[AVPlayer addPeriodicTimeObserverForInterval:queue:usingBlock:] instead")));
- (RACSignal *)bcov_periodicTimeObserverSignalForInterval:(CMTime)interval queue:(dispatch_queue_t)serialQueue __attribute((deprecated("Use -[AVPlayer addPeriodicTimeObserverForInterval:queue:usingBlock:] instead")));
@end

