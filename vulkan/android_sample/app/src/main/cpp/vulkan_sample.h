//
// Created by linroid on 2018/11/9.
//

#ifndef ANDROID_SAMPLE_VULKAN_SAMPLE_H
#define ANDROID_SAMPLE_VULKAN_SAMPLE_H

#include <android_native_app_glue.h>
#include <set>
#include <functional>
#include <stdlib.h>
#include <vector>
#include "vulkan_wrapper/vulkan_wrapper.h"
#include "utils/log.h"
#include "utils/android_util.h"

// Vulkan call wrapper
#define CALL_VK(func)                                                 \
  if (VK_SUCCESS != (func)) {                                         \
    __android_log_print(ANDROID_LOG_ERROR, "VulkanError",               \
                        "File[%s], line[%d]", __FILE__, \
                        __LINE__);                                    \
    assert(false);                                                    \
  }

const VkFormat kTexFmt = VK_FORMAT_R8G8B8A8_UNORM;

typedef struct texture_object {
    VkSampler sampler;
    VkImage image;
    VkImageLayout imageLayout;
    VkDeviceMemory mem;
    VkImageView view;
    int32_t tex_width;
    int32_t tex_height;
} texture_object;

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

void createIndexBuffer();

void createBuffer(VkDeviceSize size, VkBufferUsageFlags flags, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                  VkDeviceMemory &memory);

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

void createTextureImage();

void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                 VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

VkCommandBuffer beginSingleTimeCommands();

void endSingleTimeCommands(VkCommandBuffer commandBuffer);

void createCommandPool();

void createCommandBuffers();

void createSemaphores();

void drawFrame();

bool isVulkanReady();

void cleanSwapChain();

void recreateSwapChain();

#endif //ANDROID_SAMPLE_VULKAN_SAMPLE_H
