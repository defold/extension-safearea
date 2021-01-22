#include "safearea.h"
#include <dmsdk/sdk.h>

#ifdef DM_PLATFORM_IOS

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

void safeareans::ResizeGameView(float* bg_color) {
    // Get UIView from Defold, and its parent view.
    // We need to get the parent view to actually get the
    // safe area layout guide.
    UIView* glview = (UIView*)dmGraphics::GetNativeiOSUIView();
    UIView* view = (UIView*)glview.superview;

    // API and usage only available on iOS 11 and above.
    if ([view respondsToSelector: @selector(safeAreaLayoutGuide)]) {
        UILayoutGuide* margins = view.safeAreaLayoutGuide;
        glview.translatesAutoresizingMaskIntoConstraints = NO;

        // Activate safe area constraints.
        [NSLayoutConstraint activateConstraints:@[
                                                 [margins.trailingAnchor constraintEqualToAnchor:glview.trailingAnchor],
                                                 [glview.leadingAnchor constraintEqualToAnchor:margins.leadingAnchor],
                                                 [glview.topAnchor constraintEqualToAnchor:margins.topAnchor],
                                                 [margins.bottomAnchor constraintEqualToAnchor:glview.bottomAnchor]
                                                ]];

        // Set the background color to the parent view.
        view.backgroundColor = [UIColor colorWithRed: bg_color[0] green: bg_color[1] blue: bg_color[2] alpha: 1.0f];
    }
}

void safeareans::GetInsets(Insets* insets) {
    UIView* glview = (UIView*)dmGraphics::GetNativeiOSUIView();

    // API and usage only available on iOS 11 and above.
    if ([glview respondsToSelector: @selector(safeAreaInsets)]) {
        UIEdgeInsets viewInsets = glview.safeAreaInsets;
        CGFloat scale = glview.layer.contentsScale;

        insets->bottom = viewInsets.bottom * scale;
        insets->left = viewInsets.left * scale;
        insets->right = viewInsets.right * scale;
        insets->top = viewInsets.top * scale;
    }
}

#endif // DM_PLATFORM_IOS
