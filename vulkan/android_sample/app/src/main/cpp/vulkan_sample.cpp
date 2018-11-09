#include <stdlib.h>
#include <set>
#include <functional>
#include "vulkan_wrapper/android_util.h"
#include "vulkan_sample.h"
// Vulkan call wrapper
#define CALL_VK(func)                                                 \
  if (VK_SUCCESS != (func)) {                                         \
    __android_log_print(ANDROID_LOG_ERROR, "Tutorial ",               \
                        "Vulkan error. File[%s], line[%d]", __FILE__, \
                        __LINE__);                                    \
    assert(false);                                                    \
  }

bool initialized_ = false;
VkInstance instance;
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
uint32_t queueFamilyIndex;
VkDevice device;
VkQueue graphicsQueue;
VkSurfaceKHR surface;
VkSwapchainKHR swapchain;
uint32_t swapchainImageCount;
VkSurfaceFormatKHR surfaceFormat;
std::vector<VkImage> swapchainImages;
std::vector<VkImageView> imageViews;
android_app *app_context;
VkExtent2D extent;

VkRenderPass renderPass = VK_NULL_HANDLE;
VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
VkPipeline pipeline = VK_NULL_HANDLE;
std::vector<VkFramebuffer> frameBuffers;
VkCommandPool commandPool;

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
    LOGI("querySwapChainSupport");
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    if (formatCount > 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        LOGD("physical device surface formats:");
        for (auto format : details.formats) {
            LOGD("format=%d, colorSpace=%d", format.format, format.colorSpace);
        }
    }
    uint32_t presentModesCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModesCount, nullptr);
    if (presentModesCount > 0) {
        details.presentModes.resize(presentModesCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModesCount, details.presentModes.data());
        LOGD("physical device present modes:");
        for (auto mode : details.presentModes) {
            LOGD("mode=%d", mode);
        }
    }
    LOGI("querySwapChainSupport formatCount=%d, presentModelsCount=%d", formatCount, presentModesCount);
    return details;
}

const bool enableValidatorLayer = false;
//#if NDEBUG
//const bool enableValidatorLayer = true;
//#else
//const bool enableValidatorLayer = false;
//#endif


void android_main(struct android_app *app) {
    LOGI("android_main");
    app_context = app;
    app->onAppCmd = handle_cmd;
    int events;
    android_poll_source *source;
    do {
        if (ALooper_pollAll(initialized_ ? 1 : 0, nullptr, &events, (void **) &source) >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }
        }
    } while (app->destroyRequested == 0);
}

void handle_cmd(struct android_app *app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            initialize(app);
            break;
        case APP_CMD_TERM_WINDOW:
            terminate();
            break;
        default:
            LOGI("event not handled: %d", cmd);
            break;
    }
}

void initialize(android_app *app) {
    if (!InitVulkan()) {
        LOGE("init vulkan falied");
        return;
    }
    createInstance();
    setDebugCallback();
    createSurface(app->window);
    createDevice();
    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createFrameBuffers();
    crateCommandPool();
    destroy();
}

void createImageViews() {
    imageViews.resize(swapchainImageCount);
    for (int i = 0; i < swapchainImageCount; ++i) {
        VkImageViewCreateInfo createInfo = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                .image = swapchainImages[i],
                .viewType = VK_IMAGE_VIEW_TYPE_2D,
                .format = surfaceFormat.format,
                .components.a = VK_COMPONENT_SWIZZLE_IDENTITY,
                .components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
                .components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
                .components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
                .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .subresourceRange.baseMipLevel = 0,
                .subresourceRange.levelCount = 1,
                .subresourceRange.baseArrayLayer = 0,
                .subresourceRange.layerCount = 1,
        };
        CALL_VK(vkCreateImageView(device, &createInfo, nullptr, &imageViews[i]));
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
            .pSubpasses = &subpassDescription
    };
    CALL_VK(vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass));
    
}

void createGraphicsPipeline() {
//    memset(&gfxPipeline, 0, sizeof(gfxPipeline));
    // Create pipeline layout (empty)
//    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
//            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
//            .pNext = nullptr,
//            .setLayoutCount = 0,
//            .pSetLayouts = nullptr,
//            .pushConstantRangeCount = 0,
//            .pPushConstantRanges = nullptr,
//    };
//    CALL_VK(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo,
//                                   nullptr, &gfxPipeline.layout_));
    LOGD("createGraphicsPipeline");
    
    VkShaderModule vertexShader, fragmentShader;
    CALL_VK(loadShaderFromAssets(app_context, "shaders/triangle.vert.spv", device, &vertexShader, VERTEX_SHADER));
    CALL_VK(loadShaderFromAssets(app_context, "shaders/triangle.frag.spv", device, &fragmentShader, FRAGMENT_SHADER));
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
    VkPipelineVertexInputStateCreateInfo vertexInputStage = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            .vertexBindingDescriptionCount = 0,
            .pVertexBindingDescriptions = nullptr,
            .vertexAttributeDescriptionCount = 0,
            .pVertexAttributeDescriptions = nullptr
    };
    
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            .primitiveRestartEnable =VK_FALSE
    };
    VkViewport viewport = {
            .x = 0.0f,
            .y = 0.0f,
            .width = (float) extent.width,
            .height = (float) extent.height,
            .maxDepth = 1.0F,
            .minDepth = 0.0F
    };
    
    VkRect2D rect = {
            .offset = {0, 0},
            .extent = extent
    };
    
    VkPipelineViewportStateCreateInfo viewportCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .pNext = nullptr,
            .viewportCount = 1,
            .pViewports = &viewport,
            .scissorCount = 1,
            .pScissors = &rect
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
    
    VkDynamicState dynamicStates[] = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_LINE_WIDTH
    };
    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
            .dynamicStateCount = 2,
            .pDynamicStates = dynamicStates
    };
    
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
            .pDynamicState = &dynamicStateCreateInfo,
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

void crateCommandPool() {

}

void createSurface(ANativeWindow *window) {
    LOGI("create window");
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

void destroy() {
    LOGD("destroy");
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
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(instance, nullptr);
}

void createDevice() {
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
    for (const auto &device:devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }
    if (physicalDevice == VK_NULL_HANDLE) {
        LOGE("no device suitable");
        exit(-1);
    }
    
    LOGD("createDevice");
    queueFamilyIndex = static_cast<uint32_t>(findDeviceQueueFamily(physicalDevice));
    VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.pNext = nullptr;
    deviceQueueCreateInfo.flags = 0;
    float priorities[] = {
            1.0f,
    };
    deviceQueueCreateInfo.pQueuePriorities = priorities;
    
    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.ppEnabledExtensionNames = device_extensions.data();
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(device_extensions.size());
    if (enableValidatorLayer) {
        deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        deviceCreateInfo.ppEnabledLayerNames = validation_layers.data();
    } else {
        deviceCreateInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
        LOGE("vkCreateDevice failed");
        exit(-1);
    }
    vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}

int findDeviceQueueFamily(VkPhysicalDevice device) {
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    LOGD("queue family count: %d", queueFamilyCount);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                             queueFamilies.data());
    int i = 0;
    for (const auto &queueFamily: queueFamilies) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            LOGI("found queue family at %d, total count=%d", i, queueFamilyCount);
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
    LOGD("check device: %s, deviceType=%d, geometryShader=%d", properties.deviceName,
         properties.deviceType, features.geometryShader);
    if (!checkDeviceExtensionSupport(device)) {
        LOGW("device extensions not suitable");
        return false;
    }
    SwapChainSupportDetails details = querySwapChainSupport(device);
    if (details.formats.empty() || details.presentModes.empty()) {
        return false;
    }
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
    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = details.capabilities.minImageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.imageArrayLayers = 1;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 1;
    createInfo.pQueueFamilyIndices = &queueFamilyIndex;
    createInfo.presentMode = presentMode;
    createInfo.imageExtent = extent;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    createInfo.clipped = VK_FALSE;
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
        LOGI("%s", extension.extensionName);
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

void setDebugCallback() {
    // enumerate extension
    uint32_t extension_count;
    if (vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr) != VK_SUCCESS) {
        LOGE("vkEnumerateInstanceExtensionProperties failed");
    }
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
    LOGI("available instance extensions:");
    for (auto extension: extensions) {
        LOGI("%s", extension.extensionName);
    }
    checkValidatorLayerSupport();
    
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
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    
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

bool checkValidatorLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> layers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());
    LOGI("available layers:");
    for (auto layer: layers) {
        LOGI("name=%s, description=%s", layer.layerName, layer.description);
    }
    
    for (auto name: validation_layers) {
        bool layerFound = false;
        for (auto &layer: layers) {
            if (strcmp(name, layer.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}

void terminate() {
    LOGI("terminate");
}
