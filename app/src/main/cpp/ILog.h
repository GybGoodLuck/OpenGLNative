//
// Created by yuanbin on 19-8-9.
//

#pragma once

#include <android/log.h>

#define LOG_TAG  "C_TAG"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
