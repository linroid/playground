#include <android_native_app_glue.h>
#include <stdlib.h>
#include <vector>
#include "vulkan_wrapper/vulkan_wrapper.h"
#include "log.h"

bool initialized_ = false;
VkInstance instance;
VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
uint32_t queueFamilyIndex;
VkDevice device;
VkQueue graphicsQueue;
VkSurfaceKHR surface;

std::vector<const char *> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
};

const bool enableValidatorLayer = true;
//#if NDEBUG
//const bool enableValidatorLayer = true;
//#else
//const bool enableValidatorLayer = false;
//#endif


void handle_cmd(struct android_app *app, int32_t cmd);

void initialize(android_app *app);

void terminate();

bool checkValidatorLayerSupport();

void createInstance();

void setDebugCallback();

void pickPhysicalDevice();

bool isDeviceSuitable(VkPhysicalDevice device);

int findDeviceQueueFamily(VkPhysicalDevice device);

void createLogicDevice();

void destroy();

void android_main(struct android_app *app) {
    LOGI("android_main");
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
    pickPhysicalDevice();
    createLogicDevice();
    vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
    destroy();
}

void destroy() {
    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(instance, nullptr);
}

void createLogicDevice() {
    LOGI("createLogicDevice");
    queueFamilyIndex = static_cast<uint32_t>(findDeviceQueueFamily(physicalDevice));
    VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.pNext = nullptr;
    float queuePriority = 1.0f;
    deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.enabledExtensionCount = 0;
    if (enableValidatorLayer) {
        deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        deviceCreateInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
        LOGE("vkCreateDevice failed");
        exit(-1);
    }
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
            LOGI("found queue family %d", i);
            return i;
        }
    }
    return -1;
}

void pickPhysicalDevice() {
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
    return (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU or
            properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) &&
           features.geometryShader;
}

void setDebugCallback() {
    // enumerate extension
    uint32_t extension_count;
    if (vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr) != VK_SUCCESS) {
        LOGE("vkEnumerateInstanceExtensionProperties failed");
    }
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
    LOGI("available extensions:");
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
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = nullptr;
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

    for (auto name: validationLayers) {
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
