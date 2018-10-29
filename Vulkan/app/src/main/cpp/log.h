//
// Created by linroid on 2018/10/25.
//

#ifndef VULKAN_LOG_H
#define VULKAN_LOG_H

#include <android/log.h>

#define LOG_TAG "VulkanSample"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOG(level, ...) __android_log_print(level, LOG_TAG, __VA_ARGS__)
#endif //VULKAN_LOG_H
