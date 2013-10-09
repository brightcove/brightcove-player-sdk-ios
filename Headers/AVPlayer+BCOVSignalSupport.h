//
// AVPlayer+BCOVSignalSupport.h
// BCOVPlayerSDK
//
// Copyright (c) 2013 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <AVFoundation/AVFoundation.h>
#import <ReactiveCocoa/ReactiveCocoa.h>


@interface AVPlayer (BCOVSignalSupport)

/**
 * Returns a signal which sends a CMTime wrapped in an NSValue at the interval
 * specified. Values are also sent whenever time jumps and whenever playback
 * starts or stops, just like -addPeriodicTimeObserverForInterval:queue:usingBlock:.
 * That method's caveats regarding scheduling very short intervals apply to
 * this as well. The signal sends complete if this AVPlayer is deallocated
 * before the subscriber disposes of the subscription.
 *
 * The returned signal does not guarantee which thread its events will be
 * delivered on, so it is important to use -[RACSignal deliverOn:RACScheduler.mainThreadScheduler]
 * to force events to be sent on the main thread if main thread execution is
 * required by subscribers. (A private serial queue is created for the periodic
 * observer.)
 *
 * Note: the periodic time observer will be added (and later removed) on the
 * main thread, regardless of which thread this method is called from, as is
 * required by AVFoundation.
 *
 * Note: Adding the periodic observer while content is playing appears to cause
 * nondeterministic crashes due to a bug in AVFoundation.
 *
 * @param interval The interval at which events should be sent to subscribers
 * during normal playback.
 * @return A signal which sends values according to the specified interval.
 * The value sent is the current time of the player as a CMTime wrapped in an
 * NSValue.
 */
- (RACSignal *)bcov_periodicTimeObserverSignalForInterval:(CMTime)interval;

/**
 * Returns a signal which sends a CMTime wrapped in an NSValue at the interval
 * specified. Values are also sent whenever time jumps and whenever playback
 * starts or stops, just like -addPeriodicTimeObserverForInterval:queue:usingBlock:.
 * That method's caveats regarding scheduling very short intervals apply to
 * this as well. The signal sends complete if this AVPlayer is deallocated
 * before the subscriber disposes of the subscription.
 *
 * The events sent to the returned signal will be queued on the specified
 * queue. Specifying NULL will have the same effect as specifying the main
 * thread's dispatch queue. However, it may be preferable to use
 * -[RACSignal deliverOn:RACScheduler.mainThreadScheduler] to deliver the
 * events on the main thread after any further operations have been performed
 * on the events. Specifying a concurrent dispatch queue will result in
 * undefined behavior.
 *
 * Note: the periodic time observer will be added (and later removed) on the
 * main thread, regardless of which thread this method is called from, as is
 * required by AVFoundation.
 *
 * Note: Adding the periodic observer while content is playing appears to cause
 * nondeterministic crashes due to a bug in AVFoundation.
 *
 * @param interval The interval at which events should be sent to subscribers
 * during normal playback.
 * @param serialQueue A serial dispatch queue on which the periodic time
 * observer should send events to the returned signal. Specifying NULL will
 * have the same effect as passing the main thread dispatch queue. Specifying a
 * concurrent dispatch queue will result in undefined behavior.
 * @return A signal which sends values according to the specified interval.
 * The value sent is the current time of the player as a CMTime wrapped in an
 * NSValue.
 */
- (RACSignal *)bcov_periodicTimeObserverSignalForInterval:(CMTime)interval queue:(dispatch_queue_t)serialQueue;

@end

