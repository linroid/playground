# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(LIB_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp)

message(STATUS "LIB_PATH: ${LIB_PATH}")

include_directories(${LIB_PATH})
aux_source_directory(${LIB_PATH} CPP_SRCS)

# build native_app_glue as a static lib
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror ")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(vulkan_sample
        SHARED
        src/main/cpp/vulkan_wrapper/vulkan_wrapper.h
        src/main/cpp/vulkan_wrapper/vulkan_wrapper.cpp
        ${CPP_SRCS} )
target_include_directories(vulkan_sample PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        vulkan_sample
        android
        native_app_glue
        EGL
        GLESv1_CM
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )