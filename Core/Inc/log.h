//
// Created by mayn on 2020/11/9 0009.
//

#ifndef FREERTOS_LOG_H
#define FREERTOS_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void sendToWifi(char *str, ...);
void Print(char *str, ...);
void Log(char *str, ...);

char *sprint(char *str, ...);
char *send(UART_HandleTypeDef *huart, char *msg);
char *response(UART_HandleTypeDef *huart);
char *sendResponse1(char *msg, char *isOk);
char *sendResponse2(char *msg, char *isOk);

#endif //FREERTOS_LOG_H
