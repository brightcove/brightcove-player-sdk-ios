# Using Interactivity With The Brightcove Player SDK for iOS, version 6.13.3.8

The Brightcove Player SDK currently supports Interactivity in a limited capacity.

### Supported Annotations:

* Text Overlay
* Image Overlay
* Transparent Overlay
    * Adding text is not currently supported.
* Time Triggered Action

### Additional Limitations

* The "Mullins Special" and "White" themes are supported for Text overlay annotations.
* Only the "Fade" transition is supported for Text and Image overlays.
* Text, Transparent and Image overlays can be configured to be interactive on iOS but this behavior is not yet supported on tvOS.

## Requirements

- Brightcove Native Player SDK v6.13.3+
- Brightcove Account with Dynamic Delivery
- Brightcove Account with [Interactivity](https://www.brightcove.com/en/products/interactivity) Enabled

## Quick Start

Here is an example of adding Interactivity to your project:

```
// Obj-C
self.interactivityHandler = [[BCOVInteractivityHandler alloc] initWithAccountId:kViewControllerAccountID projectId:kViewControllerProjectId containerView:self.playerView.interactivityOverlayView playbackController:self.playbackController];
self.interactivityHandler.delegate = self;
```

```
// Swift
if let interactivityOverlayView = playerView.interactivityOverlayView, let playbackController = playbackController {
    interactivityHandler = BCOVInteractivityHandler(accountId: playbackConfig.accountID, projectId: playbackConfig.interactivityProjectID, containerView: interactivityOverlayView,  playbackController: playbackController)
    interactivityHandler?.delegate = self
}
```

### Customization

The following delegate methods are available for customizing annotations:

```
- (CGFloat)animationTimeForTransition:(BCOVInteractivityAnnotationTransition)transition;
- (UIFont *)fontForTextAnnotation:(BCOVInteractivityAnnotation *)annotation;
- (UIColor *)backgroundColorForTextAnnotation:(BCOVInteractivityAnnotation *)annotation;
- (UIColor *)textColorForTextAnnotation:(BCOVInteractivityAnnotation *)annotation;
- (void)annotationWasTapped:(BCOVInteractivityAnnotation *)annotation; // iOS Only
- (void)annotationWasTriggered:(BCOVInteractivityAnnotation *)annotation;
```

Detailed information for each method can be found in `BCOVInteractivityHandler.h`.

### Behavior

On iOS if an annotation is set up to "Jump to video time" or launch a URL it will do so without any additional work on your end when the annotation is tapped and the `annotationWasTapped:` will be called.

A Time Triggered annotation will be triggered at the specified time and the `annotationWasTriggered:` delegate method will be called. This delegate method can be used if you want additional behavior other than "Jump to video time".

You may also configure additional behavior on iOS by giving the annotation a Command value in the Interactivity editor (Edit > More > Link > Advanced). You may also supply additional values for the Command by adding key/value pairs to the Command Data.

Here's an example of displaying a Chapters menu using an `UIAlertController`:

```
// Obj-C
- (void)annotationWasTapped:(BCOVInteractivityAnnotation *)annotation
{
    NSString *command = annotation.command;
    NSDictionary *commandData = annotation.commandData;

    if ([command isEqualToString:@"my-command"])
    {
        NSArray *sortedKeys = [commandData keysSortedByValueUsingComparator:^NSComparisonResult(id  _Nonnull obj1, id  _Nonnull obj2) {
            return [obj1 compare:obj2];
        }];

        NSMutableArray *sortedChapters = @[].mutableCopy;
        for (NSString *key in sortedKeys)
        {
            NSNumber *time = commandData[key];
            NSDictionary *chapter = @{
                @"title": key,
                @"time": time
            };
            [sortedChapters addObject:chapter];
        }

        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Interactivity" message:@"Chapter Selection" preferredStyle:UIAlertControllerStyleActionSheet];

        for (NSDictionary *chapter in sortedChapters)
        {
            NSNumber *timeNum = chapter[@"time"];
            NSString *title = chapter[@"title"];
            CMTime time = CMTimeMake(timeNum.longLongValue, 1);
            [alert addAction:[UIAlertAction actionWithTitle:title style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                [self.playbackController seekToTime:time completionHandler:nil];
            }]];
        }

        [alert addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil]];

        alert.popoverPresentationController.sourceView = annotation.annotationView;

        [self presentViewController:alert animated:YES completion:nil];
    }
}
```

```
// Swift
func annotationWasTapped(_ annotation: BCOVInteractivityAnnotation) {
    guard let command = annotation.command, let commandData = annotation.commandData else {
        return
    }

    if command == "my-command" {
        let sortedKeys = (commandData as NSDictionary).keysSortedByValue { (obj1, obj2) -> ComparisonResult in
            return (obj1 as! String).compare(obj2 as! String)
        }

        var sortedChapters: [NSDictionary] = []
        for key in sortedKeys {
            guard let key = key as? String, let timeStr = commandData[key] as? String, let time = NumberFormatter().number(from: timeStr) else {
                continue
            }
            let chapter: [String: Any] = [
                "title": key,
                "time": time
            ]
            sortedChapters.append(chapter as NSDictionary)
        }

        let alert = UIAlertController(title: "Interactivity", message: "Chapter Selection", preferredStyle: .actionSheet)

        for chapter in sortedChapters {
            if let timeNum = chapter["time"] as? NSNumber, let title = chapter["title"] as? String {
                let time = CMTimeMake(value: timeNum.int64Value, timescale: 1)
                alert.addAction(UIAlertAction(title: title, style: .default) { _ in
                    self.playbackController.seek(to: time, completionHandler: nil)
                })
            }
        }

        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))

        alert.popoverPresentationController?.sourceView = annotation.annotationView

        self.present(alert, animated: true, completion:nil)
    }
}
```

### Preconditions

You can set up preconditions for your annotations to show and hide them on demand. Here is an example of hiding an annotation when playback begins and showing it five seconds after pause:

```
- (void)playbackController:(id<BCOVPlaybackController>)controller playbackSession:(id<BCOVPlaybackSession>)session didReceiveLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)lifecycleEvent
{
    if ([lifecycleEvent.eventType isEqualToString:kBCOVPlaybackSessionLifecycleEventPause])
    {
        self.xRayTimer = [NSTimer scheduledTimerWithTimeInterval:5 repeats:NO block:^(NSTimer * _Nonnull timer) {
            [self.interactivityHandler enablePrecondition:@"xRay"];
        }];
    }

    if ([lifecycleEvent.eventType isEqualToString:kBCOVPlaybackSessionLifecycleEventPlay])
    {
        [self.xRayTimer invalidate];
        [self.interactivityHandler disablePrecondition:@"xRay"];
    }
}
```
