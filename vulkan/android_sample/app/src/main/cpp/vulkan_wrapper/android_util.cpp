//
// Created by linroid on 2018/11/7.
//

#include <cassert>
#include <log.h>
#include "android_util.h"

VkResult loadShaderFromAssets(android_app *app, const char *path, VkDevice& device, VkShaderModule *output,
                              ShaderType shaderType) {
    assert(app);
    AAsset *fp = AAssetManager_open(app->activity->assetManager, path, AASSET_MODE_BUFFER);
    assert(fp);
    LOGI("open %s from assets", path);
    size_t length = AAsset_getLength(fp);
    LOGI("open succeed, len=%ld", length);
    char *content = new char[length];
    AAsset_read(fp, content, length);
    AAsset_close(fp);
    LOGI("file read finished");
    VkShaderModuleCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .codeSize = length,
            .pCode = (const uint32_t *) content,
            .flags = 0

    };
    VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, output);
    assert(result == VK_SUCCESS);
    delete[] content;
    return result;
}