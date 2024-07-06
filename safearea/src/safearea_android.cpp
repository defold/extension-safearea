#include "safearea.h"
#include <dmsdk/sdk.h>

#ifdef DM_PLATFORM_ANDROID
#include "safearea_jni.h"
namespace safeareans
{
void ResizeGameView(float* bg_color)
{
}

void SetBackgroundColor(float x, float y, float z, float w) 
{
}

SafeAreaStatus GetInsets(Insets* insets)
{
    // API is avaliable on Android 9.0+ (API 28+)
    if (android_get_device_api_level() < 28)
    {
        return STATUS_NOT_AVAILABLE;
    }

    ThreadAttacher attacher;
    JNIEnv *env = attacher.env;
    ClassLoader class_loader = ClassLoader(env);

    jclass cls = class_loader.load("android/app/Activity");
    jobject jwindow = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), env->GetMethodID(cls, "getWindow", "()Landroid/view/Window;"));
    
    cls = class_loader.load("android/view/Window");
    jobject jdecorView = env->CallObjectMethod(jwindow, env->GetMethodID(cls, "getDecorView", "()Landroid/view/View;"));
    
    cls = class_loader.load("android/view/View");
    jobject jinsets = env->CallObjectMethod(jdecorView, env->GetMethodID(cls, "getRootWindowInsets", "()Landroid/view/WindowInsets;"));
    
    cls = class_loader.load("android/view/WindowInsets");
    jobject cutouts = env->CallObjectMethod(jinsets, env->GetMethodID(cls, "getDisplayCutout", "()Landroid/view/DisplayCutout;"));

    if (!cutouts)
    {
        return STATUS_NOT_READY_YET;
    }
    
    cls = class_loader.load("android/view/DisplayCutout");
    insets->bottom = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetBottom", "()I"));
    insets->left = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetLeft", "()I"));
    insets->right = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetRight", "()I"));
    insets->top = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetTop", "()I"));
    return STATUS_OK;
}

SafeAreaStatus GetCornersRadius(Corners* corners)
{
    // API is avaliable on Android 12+ (API 31+)
    if (android_get_device_api_level() < 31)
    {
        return STATUS_NOT_AVAILABLE;
    }

    ThreadAttacher attacher;
    JNIEnv *env = attacher.env;
    ClassLoader class_loader = ClassLoader(env);

    jclass cls = class_loader.load("android/app/Activity");
    jobject jwindow = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), env->GetMethodID(cls, "getWindow", "()Landroid/view/Window;"));

    cls = class_loader.load("android/view/Window");
    jobject jdecorView = env->CallObjectMethod(jwindow, env->GetMethodID(cls, "getDecorView", "()Landroid/view/View;"));

    cls = class_loader.load("android/view/View");
    jobject jinsets = env->CallObjectMethod(jdecorView, env->GetMethodID(cls, "getRootWindowInsets", "()Landroid/view/WindowInsets;"));

    cls = class_loader.load("android/view/WindowInsets");
    jobject cutouts = env->CallObjectMethod(jinsets, env->GetMethodID(cls, "getDisplayCutout", "()Landroid/view/DisplayCutout;"));

    if (!cutouts)
    {
        return STATUS_NOT_READY_YET;
    }

    jclass roundedCornerClass = class_loader.load("android/view/RoundedCorner");
    jmethodID getRoundedCornerMethodID = env->GetMethodID(cls, "getRoundedCorner", "(I)Landroid/view/RoundedCorner;");
    jmethodID getRadiusMethodID = env->GetMethodID(roundedCornerClass, "getRadius", "()I");

    jint POSITION_TOP_LEFT = 0;
    jint POSITION_TOP_RIGHT = 1;
    jint POSITION_BOTTOM_RIGHT = 2;
    jint POSITION_BOTTOM_LEFT = 3;

    jobject topLeftCorner = env->CallObjectMethod(jinsets, getRoundedCornerMethodID, POSITION_TOP_LEFT);
    if (topLeftCorner) {
        corners->top_left = env->CallIntMethod(topLeftCorner, getRadiusMethodID);
    }

    jobject topRightCorner = env->CallObjectMethod(jinsets, getRoundedCornerMethodID, POSITION_TOP_RIGHT);
    if (topRightCorner) {
        corners->top_right = env->CallIntMethod(topRightCorner, getRadiusMethodID);
    }

    jobject bottomLeftCorner = env->CallObjectMethod(jinsets, getRoundedCornerMethodID, POSITION_BOTTOM_LEFT);
    if (bottomLeftCorner) {
        corners->bottom_left = env->CallIntMethod(bottomLeftCorner, getRadiusMethodID);
    }

    jobject bottomRightCorner = env->CallObjectMethod(jinsets, getRoundedCornerMethodID, POSITION_BOTTOM_RIGHT);
    if (bottomRightCorner) {
        corners->bottom_right = env->CallIntMethod(bottomRightCorner, getRadiusMethodID);
    }
    
    return STATUS_OK;
}

} // namespace
#endif // DM_PLATFORM_ANDROID
