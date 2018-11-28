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
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

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

void createDescriptorSetLayout();

void createFrameBuffers();

void createVertexBuffers();

void createIndexBuffer();

void createUniformBuffers();

void createDescriptorPool();

void createDescriptorSets();

void createBuffer(VkDeviceSize size, VkBufferUsageFlags flags, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                  VkDeviceMemory &memory);

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

void createTextureImage();

void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                 VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

void setImageLayout(VkCommandBuffer commandBuffer, VkImage image,
                    VkImageLayout oldLayout, VkImageLayout newLayout);

void copyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

VkCommandBuffer beginSingleTimeCommands();

void endSingleTimeCommands(VkCommandBuffer commandBuffer);

void createTextureImageView();

VkImageView createImageView(VkImage image, VkFormat format);

void createTextureSampler();

void createCommandPool();

void createCommandBuffers();

void createSemaphores();

void drawFrame();

void updateUniformBuffer(uint32_t currentImage);

bool isVulkanReady();

void cleanSwapChain();

void recreateSwapChain();

#endif //ANDROID_SAMPLE_VULKAN_SAMPLE_H
