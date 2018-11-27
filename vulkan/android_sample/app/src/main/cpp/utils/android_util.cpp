//
// Created by linroid on 2018/11/7.
//

#include <cassert>
#include "utils/android_util.h"
#include "utils/stb_image.h"
#include "utils/log.h"

VkResult loadShaderFromAssets(android_app *app, const char *path, VkDevice &device, VkShaderModule *output,
                              ShaderType shaderType) {
    size_t len = 0;
    unsigned char *content = loadFromAssets(app, path, len);
    VkShaderModuleCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .codeSize = len,
            .pCode = (const uint32_t *) content,
            .flags = 0
    };
    VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, output);
    assert(result == VK_SUCCESS);
    delete[] content;
    return result;
}


unsigned char *loadFromAssets(android_app *app, const char *path, size_t &len) {
    assert(app);
    AAsset *fp = AAssetManager_open(app->activity->assetManager, path, AASSET_MODE_BUFFER);
    assert(fp);
    LOGI("open %s from assets", path);
    len = static_cast<size_t>(AAsset_getLength(fp));
    LOGI("open succeed, len=%ld", len);
    unsigned char *content = new unsigned char[len];
    AAsset_read(fp, content, len);
    AAsset_close(fp);
    LOGI("file read finished");
    return content;
}