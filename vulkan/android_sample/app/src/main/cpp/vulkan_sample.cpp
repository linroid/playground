#include <stdlib.h>
#include <set>
#include <functional>
#include "vulkan_sample.h"

#define STB_IMAGE_IMPLEMENTATION
#define ENABLE_VALIDATOR_LAYER

#include "utils/stb_image.h"

static const char *kUniqueObjectLayer = "VK_LAYER_GOOGLE_unique_objects";
static const char *kGoogleThreadingLayer = "VK_LAYER_GOOGLE_threading";
static const char *kDbgExtName = "VK_EXT_debug_report";

static std::vector<const char *> validation_layers = {
        "VK_LAYER_GOOGLE_threading",
        "VK_LAYER_LUNARG_parameter_validation",
        "VK_LAYER_LUNARG_object_tracker",
        "VK_LAYER_LUNARG_core_validation",
        "VK_LAYER_GOOGLE_unique_objects"
};
static std::vector<const char *> instance_extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#ifdef ENABLE_VALIDATOR_LAYER
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
#endif
};
static std::vector<const char *> device_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
#ifdef ENABLE_VALIDATOR_LAYER
VkDebugReportCallbackEXT debugReportCallback;
#endif
const float vertexData[] = {-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
                            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                            0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                            -0.5f, 0.5f, 1.0f, 1.0f, 1.0f};
const uint16_t vertexIndices[]{0, 1, 2, 2, 3, 0};
const int MAX_FRAMES_IN_FLIGHT = 2;
std::vector<VkSemaphore> imageAvailableSemaphores;
//std::vector<VkSemaphore> renderFinishedSemaphores;
std::vector<VkFence> fences;
int currentFrame = 0;

bool initialized_ = false;
VkInstance instance;
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
uint32_t queueFamilyIndex;
VkDevice device;
VkQueue graphicsQueue;
VkSurfaceKHR surface;

VkBuffer vertexBuffer;
VkDeviceMemory vertexBufferMemory;
VkBuffer indexBuffer;
VkDeviceMemory indexBufferMemory;

VkImage textureImage;
VkDeviceMemory textureImageMemory;
VkImageView textureImageView;
VkSampler textureSampler;

VkSwapchainKHR swapchain;
uint32_t swapchainImageCount;
std::vector<VkImage> swapchainImages;
std::vector<VkImageView> imageViews;
VkSurfaceFormatKHR surfaceFormat;
VkExtent2D extent;

VkRenderPass renderPass = VK_NULL_HANDLE;
VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
VkPipeline pipeline = VK_NULL_HANDLE;

VkCommandPool commandPool = VK_NULL_HANDLE;
std::vector<VkFramebuffer> frameBuffers;
std::vector<VkCommandBuffer> commandBuffers;

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
    LOGI("querySwapChainSupport");
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    LOGI("Vulkan Surface Capabilities:\n");
    LOGI("\timage count: %u - %u\n", details.capabilities.minImageCount,
         details.capabilities.maxImageCount);
    LOGI("\tarray layers: %u\n", details.capabilities.maxImageArrayLayers);
    LOGI("\timage size (now): %dx%d\n", details.capabilities.currentExtent.width,
         details.capabilities.currentExtent.height);
    LOGI("\timage size (extent): %dx%d - %dx%d\n",
         details.capabilities.minImageExtent.width,
         details.capabilities.minImageExtent.height,
         details.capabilities.maxImageExtent.width,
         details.capabilities.maxImageExtent.height);
    LOGI("\tusage: %x\n", details.capabilities.supportedUsageFlags);
    LOGI("\tcurrent transform: %u\n", details.capabilities.currentTransform);
    LOGI("\tallowed transforms: %x\n", details.capabilities.supportedTransforms);
    LOGI("\tcomposite alpha flags: %u\n", details.capabilities.currentTransform);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    if (formatCount > 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        LOGD("physical device surface formats:");
        for (auto format : details.formats) {
            LOGD("\tformat=%d, colorSpace=%d\n", format.format, format.colorSpace);
        }
    }
    uint32_t presentModesCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModesCount, nullptr);
    if (presentModesCount > 0) {
        details.presentModes.resize(presentModesCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModesCount, details.presentModes.data());
        LOGD("physical device present modes:");
        for (auto mode : details.presentModes) {
            LOGD("\tmode=%d\n", mode);
        }
    }
    LOGI("querySwapChainSupport formatCount=%d, presentModelsCount=%d", formatCount, presentModesCount);
    return details;
}

//#if NDEBUG
//const bool enableValidatorLayer = true;
//#else
//const bool enableValidatorLayer = false;
//#endif

void initVulkan(android_app *app) {
    if (!InitVulkan()) {
        LOGE("init vulkan falied");
        return;
    }
    app_ctx_ = app;
    createInstance();
    setDebugCallback();
    createSurface(app_ctx_->window);
    createDevice();
    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createFrameBuffers();
    createCommandPool();
    createTextureImage();
    createTextureImageView();
    createTextureSampler();
    createVertexBuffers();
    createIndexBuffer();
    createCommandBuffers();
    createSemaphores();
}

void createTextureSampler() {
    VkSamplerCreateInfo samplerInfo = {
            .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
            .magFilter = VK_FILTER_LINEAR,
            .minFilter = VK_FILTER_LINEAR,
            .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            .anisotropyEnable = VK_FALSE,
            .maxAnisotropy = 1,
            .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
            .unnormalizedCoordinates = VK_FALSE,
            .compareEnable = VK_FALSE,
            .compareOp = VK_COMPARE_OP_ALWAYS,
            .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
            .mipLodBias = 0.0f,
            .minLod = 0.0f,
            .maxLod = 0.0f,
    };
    CALL_VK(vkCreateSampler(device, &samplerInfo, nullptr, &textureSampler));
}

void createTextureImageView() {
    textureImageView = createImageView(textureImage, VK_FORMAT_R8G8B8A8_UNORM);
}

VkImageView createImageView(VkImage image, VkFormat format) {
    VkImageViewCreateInfo viewInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = image,
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = format,
            .components = {
                    .r = VK_COMPONENT_SWIZZLE_R,
                    .g = VK_COMPONENT_SWIZZLE_G,
                    .b = VK_COMPONENT_SWIZZLE_B,
                    .a = VK_COMPONENT_SWIZZLE_A
            },
            .subresourceRange = {
                    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                    .baseMipLevel = 0,
                    .levelCount = 1,
                    .baseArrayLayer = 0,
                    .layerCount = 1
            }
    };
    VkImageView imageView;
    CALL_VK(vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
    return imageView;
}

void createSemaphores() {
    LOGD("createSemaphores");
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
//    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    fences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .pNext = nullptr,
    };
    VkFenceCreateInfo fenceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .flags = VK_FENCE_CREATE_SIGNALED_BIT,
            .pNext = nullptr
    };
    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        CALL_VK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &imageAvailableSemaphores[i]));
//        CALL_VK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &renderFinishedSemaphores[i]));
        CALL_VK(vkCreateFence(device, &fenceCreateInfo, nullptr, &fences[i]));
    }

    initialized_ = true;
}

void drawFrame() {
    CALL_VK(vkWaitForFences(device, 1, &fences[currentFrame], VK_TRUE, INT64_MAX));
    uint32_t imageIndex;
    CALL_VK(vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE,
                                  &imageIndex));
    CALL_VK(vkResetFences(device, 1, &fences[currentFrame]));
    VkPipelineStageFlags waitStageFlags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submitInfo = {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .waitSemaphoreCount = 1,
            .pWaitSemaphores = &imageAvailableSemaphores[currentFrame],
            .pWaitDstStageMask = &waitStageFlags,
            .commandBufferCount= 1,
            .pCommandBuffers = &commandBuffers[imageIndex],
            .signalSemaphoreCount = 0,
            .pSignalSemaphores = nullptr,
    };
    CALL_VK(vkQueueSubmit(graphicsQueue, 1, &submitInfo, fences[currentFrame]));
    LOGV("drawFrame[%d]: imageIndex=%d", currentFrame, imageIndex);
    VkResult result;
    VkPresentInfoKHR presentInfo = {
            .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            .pNext = nullptr,
            .waitSemaphoreCount = 0,
            .pWaitSemaphores = nullptr,
            .swapchainCount = 1,
            .pSwapchains=&swapchain,
            .pImageIndices = &imageIndex,
            .pResults = &result
    };
    CALL_VK(vkQueuePresentKHR(graphicsQueue, &presentInfo));
//    LOGI("vkQueuePresentKHR: result=%d", result);
    vkQueueWaitIdle(graphicsQueue);
    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

bool isVulkanReady() {
    return initialized_;
}

void createImageViews() {
    imageViews.resize(swapchainImageCount);
    for (int i = 0; i < swapchainImageCount; ++i) {
        imageViews[i] = createImageView(swapchainImages[i], surfaceFormat.format);
    }
}

void createRenderPass() {
    LOGD("createRenderPass");
    VkAttachmentDescription colorAttachment = {
            .format = surfaceFormat.format,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    };
    VkSubpassDependency dependency = {
            .srcSubpass = VK_SUBPASS_EXTERNAL,
            .dstSubpass = 0,
            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .srcAccessMask = 0,
            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
    };
    VkAttachmentReference colorAttachmentRef = {
            .attachment = 0,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkSubpassDescription subpassDescription = {
            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .colorAttachmentCount = 1,
            .pColorAttachments = &colorAttachmentRef
    };
    VkRenderPassCreateInfo renderPassCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .attachmentCount = 1,
            .pAttachments = &colorAttachment,
            .subpassCount = 1,
            .pSubpasses = &subpassDescription,
            .dependencyCount = 1,
            .pDependencies = &dependency
    };
    CALL_VK(vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass));

}

void createGraphicsPipeline() {
    LOGD("createGraphicsPipeline");

    VkShaderModule vertexShader, fragmentShader;
    CALL_VK(loadShaderFromAssets(app_ctx_, "shaders/triangle.vert.spv", device, &vertexShader, VERTEX_SHADER));
    CALL_VK(loadShaderFromAssets(app_ctx_, "shaders/triangle.frag.spv", device, &fragmentShader, FRAGMENT_SHADER));

    VkPipelineShaderStageCreateInfo vertexStageCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = vertexShader,
            .pNext = nullptr,
            .pName = "main"
    };
    VkPipelineShaderStageCreateInfo fragStageCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = fragmentShader,
            .pNext = nullptr,
            .pName = "main"
    };
    VkPipelineShaderStageCreateInfo stageCreateInfos[] = {
            vertexStageCreateInfo,
            fragStageCreateInfo
    };

    VkVertexInputBindingDescription bindingDescription[]
            = {{
                       .binding = 0,
                       .stride = 5 * sizeof(float),
                       .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
               }};
    VkVertexInputAttributeDescription attributeDescriptions[]
            = {{
                       .binding = 0,
                       .location = 0,
                       .format = VK_FORMAT_R32G32_SFLOAT,
                       .offset = 0
               },
               {
                       .binding = 0,
                       .location = 1,
                       .format = VK_FORMAT_R32G32B32_SFLOAT,
                       .offset = 2 * sizeof(float)
               }};

    VkPipelineVertexInputStateCreateInfo vertexInputStage = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            .vertexBindingDescriptionCount = 1,
            .pVertexBindingDescriptions = bindingDescription,
            .vertexAttributeDescriptionCount = 2,
            .pVertexAttributeDescriptions = attributeDescriptions
    };

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            .primitiveRestartEnable =VK_FALSE
    };
    VkViewport viewport = {
            .x = 0.0f,
            .y = 0.0f,
            .width = (float) extent.width,
            .height = (float) extent.height,
            .minDepth = 0.0F,
            .maxDepth = 1.0F
    };

    VkRect2D scissor = {
            .offset = {0, 0},
            .extent = extent
    };

    VkPipelineViewportStateCreateInfo viewportCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .pNext = nullptr,
            .viewportCount = 1,
            .pViewports = &viewport,
            .scissorCount = 1,
            .pScissors = &scissor
    };
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            .pNext = nullptr,
            .rasterizerDiscardEnable = VK_FALSE,
            .polygonMode = VK_POLYGON_MODE_FILL,
            .lineWidth = 1.0f,
            .cullMode = VK_CULL_MODE_BACK_BIT,
            .frontFace = VK_FRONT_FACE_CLOCKWISE,
            .depthBiasEnable = VK_FALSE,
            .depthBiasConstantFactor = 0.f,
            .depthBiasClamp = 0.f,
            .depthBiasSlopeFactor  =0.f
    };
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            .sampleShadingEnable = VK_FALSE,
            .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
            .minSampleShading = 1.0f,
            .pSampleMask = nullptr,
            .alphaToCoverageEnable = VK_FALSE,
            .alphaToOneEnable = VK_FALSE
    };
    VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {
            .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                              VK_COLOR_COMPONENT_A_BIT,
            .blendEnable = VK_FALSE,
//            .srcColorBlendFactor  = VK_BLEND_FACTOR_ONE,
//            .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
            .colorBlendOp = VK_BLEND_OP_ADD,
            .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
            .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
            .alphaBlendOp = VK_BLEND_OP_ADD
    };

    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            .logicOpEnable = VK_FALSE,
            .logicOp = VK_LOGIC_OP_COPY,
            .attachmentCount = 1,
            .pAttachments = &colorBlendAttachmentState,
            .blendConstants[0] = 0.0f,
            .blendConstants[1] = 0.0f,
            .blendConstants[2] = 0.0f,
            .blendConstants[3] = 0.0f,
    };
//
//    VkDynamicState dynamicStates[] = {
//            VK_DYNAMIC_STATE_VIEWPORT,
//            VK_DYNAMIC_STATE_LINE_WIDTH
//    };
//    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {
//            .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
//            .dynamicStateCount = 2,
//            .pDynamicStates = dynamicStates
//    };

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .setLayoutCount = 0,
            .pSetLayouts = nullptr,
            .pushConstantRangeCount =  0,
            .pPushConstantRanges = nullptr
    };
    CALL_VK(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout))

    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            .stageCount = 2,
            .pStages = stageCreateInfos,
            .pVertexInputState = &vertexInputStage,
            .pInputAssemblyState = &inputAssembly,
            .pViewportState = &viewportCreateInfo,
            .pRasterizationState = &rasterizationStateCreateInfo,
            .pMultisampleState = &multisampleStateCreateInfo,
            .pDepthStencilState = nullptr,
            .pColorBlendState = &colorBlendStateCreateInfo,
//            .pDynamicState = &dynamicStateCreateInfo,
            .layout = pipelineLayout,
            .renderPass = renderPass,
            .subpass = 0,
            .basePipelineHandle = VK_NULL_HANDLE,
            .basePipelineIndex = -1
    };

    CALL_VK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, &pipeline));
    vkDestroyShaderModule(device, vertexShader, nullptr);
    vkDestroyShaderModule(device, fragmentShader, nullptr);

}

void createFrameBuffers() {
    LOGD("createFrameBuffers");
    frameBuffers.resize(imageViews.size());
    for (int i = 0; i < imageViews.size(); ++i) {
        VkImageView colorAttachments = imageViews[i];
        VkFramebufferCreateInfo framebufferCreateInfo = {
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .renderPass = renderPass,
                .attachmentCount = 1,
                .pAttachments = &colorAttachments,
                .width = extent.width,
                .height = extent.height,
                .layers = 1
        };
        CALL_VK(vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &frameBuffers[i]))
    }
}

// A helper function
uint32_t findMemoryType(uint32_t typeBits, VkFlags requirements_mask) {
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
    // Search memtypes to find first index with those properties
    for (uint32_t i = 0; i < 32; i++) {
        if ((typeBits & 1) == 1) {
            // Type is available, does it match user properties?
            if ((memoryProperties.memoryTypes[i].propertyFlags & requirements_mask) ==
                requirements_mask) {
                return i;
            }
        }
        typeBits >>= 1;
    }
    return 0;
}

void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                  VkDeviceMemory &memory) {
    LOGD("createBuffer: size=%d", size);
    VkBufferCreateInfo createInfo = {
            .sType= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .pNext = nullptr,
            .size = size,
            .usage = usage,
            .flags = 0,
            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .pQueueFamilyIndices = &queueFamilyIndex,
            .queueFamilyIndexCount = 1
    };
    CALL_VK(vkCreateBuffer(device, &createInfo, nullptr, &buffer));

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);
    VkMemoryAllocateInfo allocateInfo = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext = nullptr,
            .allocationSize = memoryRequirements.size,
            .memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, properties)
    };
    CALL_VK(vkAllocateMemory(device, &allocateInfo, nullptr, &memory));
    CALL_VK(vkBindBufferMemory(device, buffer, memory, 0));
}

VkCommandBuffer beginSingleTimeCommands() {
    VkCommandBufferAllocateInfo allocateInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandPool = commandPool,
            .commandBufferCount = 1,
    };
    VkCommandBuffer commandBuffer;
    CALL_VK(vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer));
    VkCommandBufferBeginInfo beginInfo = {
            .sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .flags= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
            .pInheritanceInfo = nullptr,
    };
    CALL_VK(vkBeginCommandBuffer(commandBuffer, &beginInfo));
    return commandBuffer;
}

void endSingleTimeCommands(VkCommandBuffer commandBuffer) {
    vkEndCommandBuffer(commandBuffer);
    VkFenceCreateInfo fenceInfo = {
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
    };
    VkFence fence;
    CALL_VK(vkCreateFence(device, &fenceInfo, nullptr, &fence));
    VkSubmitInfo submitInfo = {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .waitSemaphoreCount = 0,
            .pWaitSemaphores = nullptr,
            .pWaitDstStageMask = nullptr,
            .signalSemaphoreCount = 0,
            .pSignalSemaphores = nullptr,
            .pNext = nullptr,
            .commandBufferCount = 1,
            .pCommandBuffers = &commandBuffer
    };
    CALL_VK(vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence));
    vkQueueWaitIdle(graphicsQueue);
    CALL_VK(vkWaitForFences(device, 1, &fence, VK_TRUE, INT64_MAX));
    vkDestroyFence(device, fence, nullptr);
    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    LOGD("copyBuffer: size=%d", size);
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();
    VkBufferCopy copyRegion = {
            .size = size,
            .dstOffset = 0,
            .srcOffset = 0
    };
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    endSingleTimeCommands(commandBuffer);
}

void createVertexBuffers() {
    LOGD("createVertexBuffers");
    size_t bufferSize = sizeof(vertexData);
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingBufferMemory);
    void *data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertexData, bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
    copyBuffer(stagingBuffer, vertexBuffer, bufferSize);
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}


void createIndexBuffer() {
    LOGD("createIndexBuffer");
    VkDeviceSize bufferSize = sizeof(vertexIndices);
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingBufferMemory);
    void *data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertexIndices, bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);
    copyBuffer(stagingBuffer, indexBuffer, bufferSize);
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                 VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory) {
    LOGD("createImage");
    VkImageCreateInfo imageCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext = nullptr,
            .imageType = VK_IMAGE_TYPE_2D,
            .format = kTexFmt,
            .extent = {
                    .width = width,
                    .height = height,
                    .depth = 1
            },
            .mipLevels = 1,
            .arrayLayers = 1,
            .tiling = VK_IMAGE_TILING_OPTIMAL,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .flags = 0
    };
    CALL_VK(vkCreateImage(device, &imageCreateInfo, nullptr, &image));
    VkMemoryRequirements requirements;
    vkGetImageMemoryRequirements(device, image, &requirements);

    VkMemoryAllocateInfo allocateInfo = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = requirements.size,
            .memoryTypeIndex = findMemoryType(requirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    };
    CALL_VK(vkAllocateMemory(device, &allocateInfo, nullptr, &imageMemory));
    vkBindImageMemory(device, image, imageMemory, 0);
}

void createTextureImage() {
    LOGD("createTextureImage");
    uint32_t imgWidth, imgHeight, n;
    size_t file_len = 0;
    const stbi_uc *content = loadFromAssets(app_ctx_, "sample_tex.png", file_len);
    unsigned char *pixels = stbi_load_from_memory(
            content, static_cast<int>(file_len), reinterpret_cast<int *>(&imgWidth),
            reinterpret_cast<int *>(&imgHeight), reinterpret_cast<int *>(&n), 4);
    assert(n == 4);

    VkDeviceSize imageSize = imgWidth * imgHeight * 4;
    LOGI("texture loaded: width=%d, height=%d, pixels=%d", imgWidth, imgHeight, imageSize);
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer,
                 stagingBufferMemory);
    void *data;
    vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, imageSize);
    vkUnmapMemory(device, stagingBufferMemory);
    stbi_image_free(pixels);

    createImage(imgWidth, imgHeight, kTexFmt, VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                textureImage, textureImageMemory);

    VkCommandBuffer commandBuffer = beginSingleTimeCommands();
    setImageLayout(commandBuffer, textureImage, VK_IMAGE_LAYOUT_UNDEFINED,
                   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(commandBuffer, stagingBuffer, textureImage, static_cast<uint32_t>(imgWidth),
                      static_cast<uint32_t>(imgHeight));
    setImageLayout(commandBuffer, textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    endSingleTimeCommands(commandBuffer);
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void setImageLayout(VkCommandBuffer commandBuffer, VkImage image,
                    VkImageLayout oldLayout, VkImageLayout newLayout) {
    LOGD("setImageLayout");
    VkImageMemoryBarrier barrier = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            .oldLayout = oldLayout,
            .newLayout = newLayout,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = image,
            .subresourceRange = {
                    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                    .baseMipLevel = 0,
                    .levelCount = 1,
                    .baseArrayLayer = 0,
                    .layerCount = 1
            },
            .srcAccessMask = 0,
            .dstAccessMask = 0
    };
    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL &&
               newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, NULL, 0, NULL, 1,
                         &barrier);
}

void copyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
    LOGD("copyBufferToImage");
    VkBufferImageCopy region = {
            .bufferOffset = 0,
            .bufferRowLength = 0,
            .bufferImageHeight = 0,
            .imageSubresource = {
                    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                    .mipLevel = 0,
                    .baseArrayLayer = 0,
                    .layerCount = 1
            },
            .imageOffset = {0, 0, 0},
            .imageExtent = {width, height, 1},

    };
    vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
    LOGD("copyBufferToImage finished");
}

void createCommandPool() {
    LOGD("createCommandPool");
    VkCommandPoolCreateInfo commandPoolCreateInfo{
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .queueFamilyIndex = queueFamilyIndex,
            .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
    };
    CALL_VK(vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &commandPool));
}

void createCommandBuffers() {
    LOGD("createCommandBuffers, size=%ld", frameBuffers.size());
    commandBuffers.resize(frameBuffers.size());
    VkCommandBufferAllocateInfo allocateInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .commandPool = commandPool,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount = static_cast<uint32_t>(frameBuffers.size()),
            .pNext = nullptr
    };
    CALL_VK(vkAllocateCommandBuffers(device, &allocateInfo, commandBuffers.data()));
    for (int i = 0; i < commandBuffers.size(); ++i) {
        VkCommandBufferBeginInfo bufferBeginInfo = {
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                .pNext = nullptr,
                .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
//                .flags = 0,
                .pInheritanceInfo = nullptr
        };
        CALL_VK(vkBeginCommandBuffer(commandBuffers[i], &bufferBeginInfo));
        // transition the display image to color attachment layout
//        setImageLayout(commandBuffers[i], swapchainImages[i],
//                       VK_IMAGE_LAYOUT_UNDEFINED,
//                       VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
//                       VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
//                       VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
        VkClearValue clearColor = {
                .color.float32 = {0.0f, 0.34f, 0.90f, 1.0f}
        };
        VkRenderPassBeginInfo renderPassBeginInfo = {
                .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                .renderPass = renderPass,
                .framebuffer = frameBuffers[i],
                .renderArea.offset = {.x=0, .y=0},
                .renderArea.extent = extent,
                .clearValueCount = 1,
                .pClearValues = &clearColor
        };

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
        VkDeviceSize offset = 0;
        vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &vertexBuffer, &offset);
        vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT16);
        // Draw Rectangle
        // vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
        vkCmdDrawIndexed(commandBuffers[i], sizeof(vertexIndices) / sizeof(vertexIndices[0]), 1, 0, 0, 0);
        vkCmdEndRenderPass(commandBuffers[i]);
        CALL_VK(vkEndCommandBuffer(commandBuffers[i]));
    }
}

void createDevice() {
    LOGD("createDevice");
    // enumerate devices
    uint32_t deviceCount;
    if (vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr) != VK_SUCCESS) {
        LOGE("vkEnumeratePhysicalDevices failed");
        exit(-1);
    }
    LOGI("device count: %d", deviceCount);
    if (deviceCount == 0) {
        LOGE("no device available");
        exit(-1);
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    if (vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()) != VK_SUCCESS) {
        LOGE("vkEnumeratePhysicalDevices get devices info failed");
        exit(-1);
    }
    for (const auto &device: devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }
    if (physicalDevice == VK_NULL_HANDLE) {
        LOGE("no device suitable");
        exit(-1);
    }
    queueFamilyIndex = static_cast<uint32_t>(findDeviceQueueFamily(physicalDevice));
    VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.pNext = nullptr;
    deviceQueueCreateInfo.flags = 0;
    float priorities[] = {1.0f};
    deviceQueueCreateInfo.pQueuePriorities = priorities;
    VkPhysicalDeviceFeatures deviceFeatures = {
//            .samplerAnisotropy = VK_TRUE
    };
    VkDeviceCreateInfo deviceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pQueueCreateInfos = &deviceQueueCreateInfo,
            .pEnabledFeatures = &deviceFeatures,
            .queueCreateInfoCount = 1,
            .ppEnabledExtensionNames = device_extensions.data(),
            .enabledExtensionCount = static_cast<uint32_t>(device_extensions.size()),
#ifdef ENABLE_VALIDATOR_LAYER
            .enabledLayerCount = static_cast<uint32_t>(validation_layers.size()),
            .ppEnabledLayerNames = validation_layers.data(),
#else
            .enabledLayerCount = 0
#endif
    };

    CALL_VK(vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device))
    vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}

void createSurface(ANativeWindow *window) {
    LOGI("createSurface");
    VkAndroidSurfaceCreateInfoKHR createInfo = {
            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            .pNext = nullptr,
            .flags = 0,
            .window = window,
    };
    if (vkCreateAndroidSurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS) {
        LOGE("create android surface khr failed");
        exit(-1);
    }
}


int findDeviceQueueFamily(VkPhysicalDevice device) {
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    LOGD("queue family count: %d", queueFamilyCount);
    assert(queueFamilyCount);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             queueFamilies.data());
    int i = 0;
    for (const auto &queueFamily: queueFamilies) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            LOGI("found queue family at %d, queueCount=%d, queueFamilyCount=%d", i, queueFamily.queueCount,
                 queueFamilyCount);
            return i;
        }
    }
    return -1;
}

bool isDeviceSuitable(VkPhysicalDevice device) {
    if (findDeviceQueueFamily(device) == -1) {
        return false;
    }
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(device, &properties);

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(device, &features);
    LOGD("check device: %s, deviceType=%d, geometryShader=%d, apiVersion=%x, driverVersion=%x",
         properties.deviceName, properties.deviceType, features.geometryShader, properties.apiVersion,
         properties.driverVersion);
    LOGI("API Version Supported: %d.%d.%d",
         VK_VERSION_MAJOR(properties.apiVersion),
         VK_VERSION_MINOR(properties.apiVersion),
         VK_VERSION_PATCH(properties.apiVersion));
    if (!checkDeviceExtensionSupport(device)) {
        LOGW("device extensions not suitable");
        return false;
    }
    SwapChainSupportDetails details = querySwapChainSupport(device);
    if (details.formats.empty() || details.presentModes.empty()) {
        return false;
    }
//    if (!features.samplerAnisotropy) {
//        return false;
//    }
    return (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
            properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) {
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }
    for (auto format: availableFormats) {
        if (format.format == VK_FORMAT_B8G8R8A8_UNORM
            && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return format;
        }
    }
    return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes) {
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_MAILBOX_KHR;
    for (const auto &presentMode : availablePresentModes) {
        if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return presentMode;
        } else if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = presentMode;
        }
    }
    return bestMode;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {800, 600};
        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    };
}


void createSwapChain() {
    SwapChainSupportDetails details = querySwapChainSupport(physicalDevice);
    surfaceFormat = chooseSwapSurfaceFormat(details.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(details.presentModes);
    extent = chooseSwapExtent(details.capabilities);
    uint32_t imageCount = details.capabilities.minImageCount + 1;
    if (details.capabilities.maxImageCount > 0 && imageCount > details.capabilities.maxImageCount) {
        imageCount = details.capabilities.maxImageCount;
    }
    LOGD("imageCount=%d, %d (%d, %d)", imageCount, queueFamilyIndex, extent.width, extent.height);
    VkSwapchainCreateInfoKHR createInfo = {
            .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
            .surface = surface,
            .minImageCount = details.capabilities.minImageCount,
            .imageFormat = surfaceFormat.format,
            .imageColorSpace = surfaceFormat.colorSpace,
            .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
            .imageArrayLayers = 1,
            .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .queueFamilyIndexCount = 1,
            .pQueueFamilyIndices = &queueFamilyIndex,
            .presentMode = presentMode,
            .imageExtent = extent,
            .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
            .compositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
            .oldSwapchain = VK_NULL_HANDLE,
            .clipped = VK_FALSE,
    };
    CALL_VK(vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain));
    LOGI("swapchain create successfully");
    CALL_VK(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, nullptr));
    LOGI("swapchain create %d image(s)", swapchainImageCount);
    swapchainImages.resize(swapchainImageCount);
    CALL_VK(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages.data()));
}

bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    CALL_VK(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr));
    std::vector<VkExtensionProperties> available_extensions(extensionCount);
    CALL_VK(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, available_extensions.data()));
    LOGI("available device extensions:");
    for (const auto extension: available_extensions) {
        LOGI("\t%s\n", extension.extensionName);
    }
    for (const auto require_extension : device_extensions) {
        bool supported = false;
        for (const auto extension: available_extensions) {
            if (strcmp(extension.extensionName, require_extension) == 0) {
                supported = true;
                break;
            }
        }
        if (!supported) {
            LOGW("device not has %s extension", require_extension);
            return false;
        }
    }
    return true;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(
        VkDebugReportFlagsEXT msgFlags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t srcObject, size_t location,
        int32_t msgCode, const char *pLayerPrefix,
        const char *pMsg, void *pUserData) {
    if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
        LOGE("ERROR: [%s] Code %i : %s", pLayerPrefix, msgCode, pMsg);
    } else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
        LOGW("WARNING: [%s] Code %i : %s", pLayerPrefix, msgCode, pMsg);
    } else if (msgFlags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
        LOGW("PERFORMANCE WARNING: [%s] Code %i : %s", pLayerPrefix, msgCode, pMsg);
    } else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
        LOGI("INFO: [%s] Code %i : %s", pLayerPrefix, msgCode, pMsg);
    } else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
        LOGD("DEBUG: [%s] Code %i : %s", pLayerPrefix, msgCode, pMsg);
    }

    // Returning false tells the layer not to stop when the event occurs, so
    // they see the same behavior with and without validation layers enabled.
    return VK_FALSE;
}

void setDebugCallback() {
    // enumerate extension
    uint32_t extension_count;
    CALL_VK(vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr))
    std::vector<VkExtensionProperties> instanceExts(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, instanceExts.data());
    LOGI("available instance extensions:");
    for (auto extension: instanceExts) {
        LOGI("\t%s\n", extension.extensionName);
    }
    if (!checkValidatorLayerSupport()) {
        LOGE("checkValidatorLayerSupport failed");
    }
    VkDebugReportCallbackCreateInfoEXT createInfo = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT,
            .flags = VK_DEBUG_REPORT_ERROR_BIT_EXT |
                     VK_DEBUG_REPORT_WARNING_BIT_EXT |
                     VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT,
            .pNext = nullptr,
            .pfnCallback = DebugReportCallback,
            .pUserData = nullptr,
    };
    PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;

    vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)
            vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)
            vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");

    assert(vkCreateDebugReportCallbackEXT);
    assert(vkDestroyDebugReportCallbackEXT);
    CALL_VK(vkCreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &debugReportCallback));
}

void createInstance() {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pEngineName = "Hello Vulkan";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo createInfo = {};
    createInfo.pApplicationInfo = &appInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(instance_extensions.size());
    createInfo.ppEnabledExtensionNames = instance_extensions.data();
    createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
    createInfo.ppEnabledLayerNames = validation_layers.data();

    int ret = vkCreateInstance(&createInfo, nullptr, &instance);
    if (ret != VK_SUCCESS) {
        LOGE("vkCreateInstance failed: %d", ret);
        if (ret == VK_ERROR_INCOMPATIBLE_DRIVER) {
            LOGE("VK_ERROR_INCOMPATIBLE_DRIVER");
            exit(-1);
        }
    }
    LOGI("create vkInstance succeed");
}

void destroyVulkan() {
    LOGD("destroyVulkan");

    vkDestroyImage(device, textureImage, nullptr);
    vkFreeMemory(device, textureImageMemory, nullptr);

    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);

    vkDestroyBuffer(device, indexBuffer, nullptr);
    vkFreeMemory(device, indexBufferMemory, nullptr);

    vkDeviceWaitIdle(device);
    cleanSwapChain();
    vkDestroySampler(device, textureSampler, nullptr);
    vkDestroyImageView(device, textureImageView, nullptr);
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
//        vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(device, fences[i], nullptr);
    }

    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyDevice(device, nullptr);

#ifdef ENABLE_VALIDATOR_LAYER
    vkDestroyDebugReportCallbackEXT(instance, debugReportCallback, nullptr);
#endif
    vkDestroyInstance(instance, nullptr);
    initialized_ = false;
}

void cleanSwapChain() {
    vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
    vkDestroyCommandPool(device, commandPool, nullptr);
    for (auto frameBuffer : frameBuffers) {
        vkDestroyFramebuffer(device, frameBuffer, nullptr);
    }
    vkDestroyPipeline(device, pipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyRenderPass(device, renderPass, nullptr);
    for (int i = 0; i < imageViews.size(); ++i) {
        vkDestroyImageView(device, imageViews[0], nullptr);
    }
    vkDestroySwapchainKHR(device, swapchain, nullptr);
}

void recreateSwapChain() {
    vkDeviceWaitIdle(device);
    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createFrameBuffers();
    createCommandBuffers();
}

bool checkValidatorLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());
    LOGI("available layers:");
    for (auto layer: layers) {
        LOGI("\tname=%s, description=%s\n", layer.layerName, layer.description);
    }

    for (auto name: validation_layers) {
        bool layerFound = false;
        for (auto &layer: layers) {
            if (strcmp(name, layer.layerName) == 0) {
                layerFound = true;
                LOGI("found layer=%s", name);
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}