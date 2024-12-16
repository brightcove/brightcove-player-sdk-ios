//
// BCOVInteractivityHandler.h
// BrightcovePlayerSDK
//
// Copyright (c) 2024 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>
#import <BrightcovePlayerSDK/BCOVInteractivityAnnotation.h>
#import <BrightcovePlayerSDK/BCOVPlaybackController.h>

NS_ASSUME_NONNULL_BEGIN

@class BCOVInteractivityProject, BCOVInteractivityAnnotation;

@protocol BCOVInteractivityHandlerDelegate <NSObject>

@optional

/**
 * This delegate method is called if the GET request for fetching the
 * Interactivity project is successful.
 *
 * @param project The `BCOVInteractivityProject` that was created.
 */
- (void)projectWasCreated:(BCOVInteractivityProject *)project;

/**
 * This delegate method is called if the GET request for fetching the
 * Interactivity project fails.
 *
 * @param error The error that was returned.
 */
- (void)projectRequestFailed:(NSError *)error;

/**
 * The animation timing for a given transition class.
 * Currently only the "Fade" transition is supported.
 * The default value is `0.35`
 *
 * @param transition The transition type for the annotation.
 */
- (CGFloat)animationTimeForTransition:(BCOVInteractivityAnnotationTransition)transition;

/**
 * The desired font for a text annotation.
 * Unlike a web browser a UIFont size isn't uniform across iPhone, iPad and tvOS.
 * We use `systemFontOfSize:weight:` with the font size being 0.018%
 * of AVPlayerLayer's videoRect width and a weight of `UIFontWeightMedium`
 *
 * You can use this delegate method to ovewrite the default UIFont.
 *
 * If using a custom font make sure to follow Apple's guidelines on embedding fonts.
 * https://developer.apple.com/documentation/uikit/text_display_and_fonts/adding_a_custom_font_to_your_app
 *
 * @param annotation The Annotation to be styled.
 */
- (UIFont *)fontForTextAnnotation:(BCOVInteractivityAnnotation *)annotation;

/**
 * The desired background color for a text annotation.
 * Currently we only support the "MULLINS SPECIAL" (black) and "White" themes.
 * If any other theme is selected the styling for "White" will be used.
 *
 * For "MULLINS SPECIAL" we use RBG(68, 68, 68) with an 0.4 alpha component.
 * For "White" we use UIColor.white with an 0.5 alpha component.
 *
 * You can use this delegate method to set a custom background color for
 * the text annotation.
 *
 * @param annotation The Annotation to be styled.
 */
- (UIColor *)backgroundColorForTextAnnotation:(BCOVInteractivityAnnotation *)annotation;

/**
 * The desired text color for a text annotation.
 * Currently we only support the "MULLINS SPECIAL" (black) and "White" themes.
 * If any other theme is selected the styling for "White" will be used.
 *
 * For "MULLINS SPECIAL" we use UIColor.whiteColor.
 * For "White" we use UIColor.black.
 *
 * You can use this delegate method to set a custom text color for
 * the text annotation.
 *
 * @param annotation The Annotation to be styled.
 */
- (UIColor *)textColorForTextAnnotation:(BCOVInteractivityAnnotation *)annotation;

/**
 * This delegate method is called when a user taps the view of an BCOVInteractivityAnnotation
 * which has been configured with a command.
 *
 * You can access the command and command data with the annotation's
 * `command` and `commandData` properties.
 *
 * You can then use those values to add additional behavior.
 *
 * @param annotation The Annotation that was tapped.
 */
- (void)annotationWasTapped:(BCOVInteractivityAnnotation *)annotation API_UNAVAILABLE(tvos);

/**
 * This delegate method is called when a Time Triggered annotation becomes active
 *
 * You can access the command and command data with the annotation's
 * `command` and `commandData` properties.
 *
 * You can then use those values to add additional behavior.
 *
 * @param annotation The Annotation that was triggered.
 */
- (void)annotationWasTriggered:(BCOVInteractivityAnnotation *)annotation;

@end

@interface BCOVInteractivityHandler : NSObject<BCOVPlaybackSessionConsumer>

@property (nonatomic, weak, nullable) id<BCOVInteractivityHandlerDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;

/**
 * Returns an instance of `BCOVInteractivityHandler`
 *
 * @param accountId The account ID for the Interactivity Project
 * @param projectId The project ID for the Interactivity Project
 * @param containerView The UIVIew in which the annotations should be displayed.
 * @param playbackController The BCOVPlaybackController used for playback.
 */
- (instancetype)initWithAccountId:(NSString *)accountId projectId:(NSString *)projectId containerView:(UIView *)containerView playbackController:(id<BCOVPlaybackController>)playbackController NS_DESIGNATED_INITIALIZER;

/**
 * The current `BCOVInteractivityProject`
 */
@property (nonatomic, strong, readonly) BCOVInteractivityProject *interactivityProject;

/**
 * Enable a precondition that show any annotations configured with the precondition
 *
 * @param precondition The precondition string
 */
- (void)enablePrecondition:(NSString *)precondition;

/**
 * Disable a precondition that hide any annotations configured with the precondition
 *
 * @param precondition The precondition string
 */
- (void)disablePrecondition:(NSString *)precondition;

@end

NS_ASSUME_NONNULL_END
