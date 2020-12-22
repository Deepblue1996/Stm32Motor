//
// Created by mayn on 2020/11/26 0026.
//

#ifndef FREERTOS_WIFI_H
#define FREERTOS_WIFI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

uint8_t connectService();
uint8_t connected();

#endif //FREERTOS_WIFI_H
