# Using Interactivity With The Brightcove Player SDK for iOS, version 7.0.0.9

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

```swift
if let interactivityOverlayView = playerView.interactivityOverlayView, let playbackController = playbackController {
    interactivityHandler = BCOVInteractivityHandler(accountId: playbackConfig.accountID, projectId: playbackConfig.interactivityProjectID, containerView: interactivityOverlayView,  playbackController: playbackController)
    interactivityHandler?.delegate = self
}
```

### Customization

The following delegate methods are available for customizing annotations:

```swift
func animationTime(for transition: BCOVInteractivityAnnotationTransition) -> CGFloat
func font(forTextAnnotation annotation: BCOVInteractivityAnnotation) -> UIFont
func backgroundColor(forTextAnnotation annotation: BCOVInteractivityAnnotation) -> UIColor
func textColor(forTextAnnotation annotation: BCOVInteractivityAnnotation) -> UIColor
func annotationWasTapped(_ annotation: BCOVInteractivityAnnotation)
func annotationWasTriggered(_ annotation: BCOVInteractivityAnnotation)
```

Detailed information for each method can be found in `BCOVInteractivityHandler.h`.

### Behavior

On iOS if an annotation is set up to "Jump to video time" or launch a URL it will do so without any additional work on your end when the annotation is tapped and the `annotationWasTapped:` will be called.

A Time Triggered annotation will be triggered at the specified time and the `annotationWasTriggered:` delegate method will be called. This delegate method can be used if you want additional behavior other than "Jump to video time".

You may also configure additional behavior on iOS by giving the annotation a Command value in the Interactivity editor (Edit > More > Link > Advanced). You may also supply additional values for the Command by adding key/value pairs to the Command Data.

Here's an example of displaying a Chapters menu using an `UIAlertController`:

```swift
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

```swift
func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didReceive lifecycleEvent: BCOVPlaybackSessionLifecycleEvent) {

    if kBCOVPlaybackSessionLifecycleEventPause == lifecycleEvent.eventType {
        xRayTimer = Timer.scheduledTimer(withTimeInterval: 5, repeats: false, block: { [weak self] (timer: Timer) in
            self?.interactivityHandler?.enablePrecondition("xRay")
        })
    }

    if kBCOVPlaybackSessionLifecycleEventPlay == lifecycleEvent.eventType {
        xRayTimer?.invalidate()
        interactivityHandler?.disablePrecondition("xRay")
    }

}
```
