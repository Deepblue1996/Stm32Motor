//
// Created by mayn on 2020/11/9 0009.
//

#include "log.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "stdarg.h"
#include "usart.h"

char *sprint(char *str, ...) {
    // "/r/n"
    char *pStr = malloc(sizeof(str) * 10);
    memset(pStr, 0, sizeof(str) * 10);
    va_list args;
    int n;

    va_start(args, str);
    n = vsprintf(pStr, str, args);
    va_end(args);

    return pStr;
}

/**
 * PRINT 打印
 * @param str
 * @param ...
 */
void Log(char *str, ...) {
    // "/r/n"
    char pStr[sizeof(str) * 10];
    memset(pStr, 0, sizeof(str) * 10);
    va_list args;
    int n;

    va_start(args, str);
    n = vsprintf(pStr, str, args);
    va_end(args);

    send(&huart2, pStr);
}

void sendToWifi(char *str, ...) {

    char *pStr = malloc(sizeof(str) * 10);
    memset(pStr, 0, sizeof(str) * 10);
    va_list args;

    va_start(args, str);
    vsprintf(pStr, str, args);
    va_end(args);

    const char num = strlen(pStr);

    char *per = sprint("AT+CIPSEND=%d\r\n", num);
    char *string5 = sendResponse1(per, "\r\n>");
    if (strstr(string5, "ERROR") == NULL) {
        Print(pStr);
        Log("Send to Service : %s\r\n", pStr);
    } else {
        Log("ReSendToWifi 2: %s\r\n", string5);
    }
    free(pStr);
    free(per);
}

void Print(char *str, ...) {
    // "/r/n"
    char pStr[sizeof(str) * 10];
    va_list args;

    va_start(args, str);
    vsprintf(pStr, str, args);
    va_end(args);

    send(&huart1, pStr);
}

/**
 * 发送数据
 * @param huart
 * @param msg
 * @return
 */
char *send(UART_HandleTypeDef *huart, char *msg) {
    if (strcmp(msg, "") == 0) {
        return "";
    }
    while (HAL_OK != HAL_UART_Transmit(huart, (uint8_t *) msg, strlen(msg), 0xFFFF));
    //HAL_UART_Transmit(huart, (uint8_t *) msg, strlen(msg), 3000);
    /*Receive command and save in "rxBuffer" array with 5s timeout*/
    return "";
}

/**
 * 接收数据
 * @param huart
 * @return
 */
char *response(UART_HandleTypeDef *huart) {
    char *rxBuffer = malloc(100);
    memset(rxBuffer, 0, 100);
    HAL_UART_Receive(huart, (uint8_t *) rxBuffer, 100, 300);

    char *str = strchr(rxBuffer, ':');

    if (str != NULL) {
        char *rxBufferTemp = malloc(100);
        memset(rxBufferTemp, 0, 100);
        strncpy(rxBufferTemp, str + 1, strlen(str) - 1);

        free(rxBuffer);
        return rxBufferTemp;
    }

    return rxBuffer;
}

char *sendResponse1(char *msg, char *isOk) {

    static char rxBuffer[100];

    memset(rxBuffer, 0, sizeof(rxBuffer));

    HAL_UART_Transmit(&huart1, (uint8_t *) msg, strlen(msg), 100);
    /*Receive command and save in "rxBuffer" array with 5s timeout*/
    HAL_UART_Receive(&huart1, (uint8_t *) rxBuffer, 255, 100);
    /*Process recived command*/

    if (strstr(rxBuffer, isOk) != NULL || strstr(rxBuffer, "ALREADY CONNECTED") != NULL
        || strstr(rxBuffer, "OK") != NULL || strstr(rxBuffer, "busy") != NULL || strstr(rxBuffer, "bu") != NULL) {
        char *str = strstr(rxBuffer, "\000");
        char *dest = malloc(strlen(str));
        memset(dest, 0, strlen(dest));
        strncpy(dest, str + strlen(msg), strlen(str) - strlen(msg));
        char len = strlen(dest);
        dest[len - 1] = '\0';
        return dest;
    } else {
        return rxBuffer;
    }
}

char *sendResponse2(char *msg, char *isOk) {

    int index = 5;

    char rxBuffer[100];

    memset(rxBuffer, 0, sizeof(rxBuffer));

    while (index > 0) {
        HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 30);
        /*Receive command and save in "rxBuffer" array with 5s timeout*/
        HAL_UART_Receive(&huart2, (uint8_t *) rxBuffer, 255, 30);
        /*Process recived command*/

        if (strstr(rxBuffer, isOk) != NULL || strstr(rxBuffer, "ALREADY CONNECTED") != NULL) {
            char *str = strstr(rxBuffer, "\000");
            char *dest = malloc(strlen(str));
            memset(dest, 0, strlen(dest));
            strncpy(dest, str + strlen(msg), strlen(str) - strlen(msg));
            char len = strlen(dest);
            dest[len - 1] = '\0';
            return dest;
        }
        if (strstr(rxBuffer, "ERROR") == 0) {
            return NULL;
        }
        index--;
    }
    return "ERROR";
}
