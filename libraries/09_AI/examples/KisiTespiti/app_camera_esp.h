/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_

#include "config.h"
#include "esp_camera.h"
#include "esp_log.h"
#include "esp_system.h"
#include "deneyap.h"

#define CAMERA_PIXEL_FORMAT PIXFORMAT_GRAYSCALE

/*#ifdef FRAMESIZE_96X96
#define CAMERA_FRAME_SIZE FRAMESIZE_96X96
#else
#define CAMERA_FRAME_SIZE FRAMESIZE_QQVGA
#endif*/

#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    CAMXC
#define SIOD_GPIO_NUM    CAMSD
#define SIOC_GPIO_NUM    CAMSC

#define Y9_GPIO_NUM      CAMD9
#define Y8_GPIO_NUM      CAMD8
#define Y7_GPIO_NUM      CAMD7
#define Y6_GPIO_NUM      CAMD6
#define Y5_GPIO_NUM      CAMD5
#define Y4_GPIO_NUM      CAMD4
#define Y3_GPIO_NUM      CAMD3
#define Y2_GPIO_NUM      CAMD2
#define VSYNC_GPIO_NUM   CAMV
#define HREF_GPIO_NUM    CAMH
#define PCLK_GPIO_NUM    CAMPC 


#define XCLK_FREQ 20000000

#ifdef __cplusplus
extern "C" {
#endif

int app_camera_init();

#ifdef __cplusplus
}
#endif
#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_
