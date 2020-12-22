//
// Created by mayn on 2020/11/27 0027.
//

#ifndef WIFIBO_DATA_H
#define WIFIBO_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

typedef enum UART_STATE {
    FREE = 0,    // 空闲
    RUNNING, // 接收中
    FINISH,  // 接收完毕
    ERR404    // 溢出
} uart_state;

extern uart_state uart1_state;
extern uart_state uart2_state;

extern char uart1_data[256];
extern char uart2_data[256];

/**
 * uart 双通道发送
 * @param msg
 */
void send_uart(char *msg);

/**
 * uart1 发送
 * @param msg
 */
void send_uart1(char *msg);

/**
 * uart1 发送扩展
 * @param msg
 * @param ...
 */
void send_uart1_sprint(char *msg, ...);

/**
 * uart2 发送
 * @param msg
 */
void send_uart2(char *msg);

/**
 * uart2 发送扩展
 * @param msg
 * @param ...
 */
void send_uart2_sprint(char *msg, ...);

/**
 * uart 发送中断循环任务
 * @param msg
 */
void uart2_time_loop();

/**
 * uart 发送中断循环
 * @param msg
 */
void uart_send_all_loop(UART_HandleTypeDef *huart);

/**
 * uart 接收中断初始化
 * @param msg
 */
void uart_rev_init();

/**
 * uart 接收中断循环
 * @param msg
 */
void uart_rev_all_loop(UART_HandleTypeDef *huart);

#endif //WIFIBO_DATA_H
