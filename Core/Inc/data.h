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
    FREE = 0,    // ����
    RUNNING, // ������
    FINISH,  // �������
    ERR404    // ���
} uart_state;

extern uart_state uart1_state;
extern uart_state uart2_state;

extern char uart1_data[256];
extern char uart2_data[256];

/**
 * uart ˫ͨ������
 * @param msg
 */
void send_uart(char *msg);

/**
 * uart1 ����
 * @param msg
 */
void send_uart1(char *msg);

/**
 * uart1 ������չ
 * @param msg
 * @param ...
 */
void send_uart1_sprint(char *msg, ...);

/**
 * uart2 ����
 * @param msg
 */
void send_uart2(char *msg);

/**
 * uart2 ������չ
 * @param msg
 * @param ...
 */
void send_uart2_sprint(char *msg, ...);

/**
 * uart �����ж�ѭ������
 * @param msg
 */
void uart2_time_loop();

/**
 * uart �����ж�ѭ��
 * @param msg
 */
void uart_send_all_loop(UART_HandleTypeDef *huart);

/**
 * uart �����жϳ�ʼ��
 * @param msg
 */
void uart_rev_init();

/**
 * uart �����ж�ѭ��
 * @param msg
 */
void uart_rev_all_loop(UART_HandleTypeDef *huart);

#endif //WIFIBO_DATA_H
