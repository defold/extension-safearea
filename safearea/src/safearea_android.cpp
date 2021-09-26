#include "safearea.h"
#include <dmsdk/sdk.h>

#ifdef DM_PLATFORM_ANDROID
#include "safearea_jni.h"
namespace safeareans
{
void ResizeGameView(float* bg_color)
{
}

void GetInsets(Insets* insets)
{
    if (android_get_device_api_level() < 28)
    {
        return;
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

    cls = class_loader.load("android/view/DisplayCutout");
    insets->bottom = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetBottom", "()I"));
    insets->left = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetLeft", "()I"));
    insets->right = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetRight", "()I"));
    insets->top = (float)env->CallIntMethod(cutouts, env->GetMethodID(cls, "getSafeInsetTop", "()I"));
}

} // namespace
#endif // DM_PLATFORM_ANDROID
