//
// Created by linroid on 2018/11/7.
//

#ifndef ANDROID_SAMPLE_ANDROID_UTIL_H
#define ANDROID_SAMPLE_ANDROID_UTIL_H


#include "vulkan_wrapper.h"
#include <android_native_app_glue.h>

enum ShaderType {
    VERTEX_SHADER, FRAGMENT_SHADER
};

VkResult loadShaderFromAssets(android_app *app, const char *path, VkDevice &device, VkShaderModule *output,
                              ShaderType shaderType);

#endif //ANDROID_SAMPLE_ANDROID_UTIL_H
