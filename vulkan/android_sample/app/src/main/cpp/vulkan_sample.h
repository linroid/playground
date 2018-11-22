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

static android_app *app_ctx_;

void initVulkan(android_app *app);

bool checkValidatorLayerSupport();

void createInstance();

void setDebugCallback();

bool isDeviceSuitable(VkPhysicalDevice device);

int findDeviceQueueFamily(VkPhysicalDevice device);

void createDevice();

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

void destroyVulkan();

void createSurface(ANativeWindow *pWindow);

bool checkDeviceExtensionSupport(VkPhysicalDevice device);

void createSwapChain();

void createImageViews();

void createGraphicsPipeline();

void createRenderPass();

void createFrameBuffers();

void createVertexBuffers();

void createCommandPool();

void createCommandBuffers();

void createSemaphores();

void drawFrame();

bool isVulkanReady();

void cleanSwapChain();

void recreateSwapChain();

#endif //ANDROID_SAMPLE_VULKAN_SAMPLE_H
