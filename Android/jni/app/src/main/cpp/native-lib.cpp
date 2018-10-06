#include <jni.h>
#include <string>
#include <android/log.h>
#include <SLES/OpenSLES.h>
#include<SLES/OpenSLES_Android.h>

extern "C" JNIEXPORT jstring
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "NativeLib", __VA_ARGS__)
JNICALL stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGD("Java version: %d", env->GetVersion());
    return env->NewStringUTF(hello.c_str());
}

static JNINativeMethod s_methods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) &stringFromJNI},
};


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    LOGD("JNI_OnLoad");
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jclass cls = env->FindClass("com/linroid/jni/MainActivity");
    if (cls == NULL) {
        return JNI_ERR;
    }
    int len = sizeof(s_methods) / sizeof(s_methods[0]);
    if (env->RegisterNatives(cls, s_methods, len) < 0) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}