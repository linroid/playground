//
// Created by linroid on 2018/11/9.
//

#ifndef ANDROID_SAMPLE_VULKAN_SAMPLE_H
#define ANDROID_SAMPLE_VULKAN_SAMPLE_H

#include "vulkan_wrapper/vulkan_wrapper.h"
#include "log.h"
#include <android_native_app_glue.h>
#include <set>
#include <functional>
#include "vulkan_wrapper/android_util.h"
#include <stdlib.h>
#include <vector>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

std::vector<const char *> validation_layers = {
        "VK_LAYER_LUNARG_standard_validation"
};
std::vector<const char *> instance_extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
};
std::vector<const char *> device_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

void handle_cmd(struct android_app *app, int32_t cmd);

void initialize(android_app *app);

void terminate();

bool checkValidatorLayerSupport();

void createInstance();

void setDebugCallback();

bool isDeviceSuitable(VkPhysicalDevice device);

int findDeviceQueueFamily(VkPhysicalDevice device);

void createDevice();

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

void destroy();

void createSurface(ANativeWindow *pWindow);

bool checkDeviceExtensionSupport(VkPhysicalDevice device);

void createSwapChain();

void createImageViews();

void createGraphicsPipeline();

void createRenderPass();

void createFrameBuffers();

void createCommandPool();

void createCommandBuffers();

#endif //ANDROID_SAMPLE_VULKAN_SAMPLE_H
