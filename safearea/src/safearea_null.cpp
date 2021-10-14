#include "safearea.h"

#if !defined(DM_PLATFORM_IOS) && !defined(DM_PLATFORM_ANDROID)

void safeareans::ResizeGameView(float* bg_color) {
}

safeareans::SafeAreaStatus safeareans::GetInsets(Insets* insets) {
	return STATUS_NOT_AVAILABLE;
}

#endif // !defined(DM_PLATFORM_IOS) && !defined(DM_PLATFORM_ANDROID)
