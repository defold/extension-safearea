#include "safearea.h"

#if !defined(DM_PLATFORM_IOS) && !defined(DM_PLATFORM_ANDROID)

void safeareans::ResizeGameView(float* bg_color) {
}

void safeareans::SetBackgroundColor(float x, float y, float z, float w) {
}

safeareans::SafeAreaStatus safeareans::GetInsets(Insets* insets) {
    return STATUS_NOT_AVAILABLE;
}

SafeAreaStatus safeareans::GetCornersRadius(Corners* corners){
    return STATUS_NOT_AVAILABLE;
}

#endif // !defined(DM_PLATFORM_IOS) && !defined(DM_PLATFORM_ANDROID)
