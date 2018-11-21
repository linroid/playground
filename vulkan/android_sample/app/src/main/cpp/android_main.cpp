//
// Created by linroid on 2018/11/21.
//
#include "log.h"
#include "android_main.h"
#include <android_native_app_glue.h>

void android_main(struct android_app *app) {
    LOGI("android_main");
    app->onAppCmd = handle_cmd;
    int events;
    android_poll_source *source;
    do {
        if (ALooper_pollAll(isVulkanReady() ? 1 : 0, nullptr, &events, (void **) &source) >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }
        }
        if (isVulkanReady()) {
            drawFrame();
        }
    } while (app->destroyRequested == 0);
}

void handle_cmd(struct android_app *app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            initVulkan(app);
            break;
        case APP_CMD_TERM_WINDOW:
            destroyVulkan();
            break;
        default:
            LOGI("event not handled: %d", cmd);
            break;
    }
}
