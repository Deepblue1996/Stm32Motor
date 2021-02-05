//
// Created by deep on 2020/11/27 0027.
//

#include "data.h"
#include "string.h"
#include "usart.h"
#include "stdarg.h"
#include "stdio.h"

// -------------------------------------------------------

char *uart1_send_data;                    // ��������
uint8_t aTxBuffer1;
uint8_t Uart1_Tx_Cnt = 0;                 // ���ջ������
uint8_t Uart1_Tx_All = 0;                 // ��һ�ε�����

char *uart2_send_data;                    // ��������
uint8_t aTxBuffer2;
uint8_t Uart2_Tx_Cnt = 0;                 // ���ջ������
uint8_t Uart2_Tx_All = 0;                 // ��һ�ε�����

// -------------------------------------------------------

uint8_t cAlmStr[] = "�������(����256)\r\n";

uint8_t aRxBuffer1;                       // �����жϻ���
char Uart1_RxBuff[256];                   // ���ջ���
uint8_t Uart1_Rx_Cnt = 0;                 // ���ջ������

// �������
char uart1_data[256];

uart_state uart1_state = FREE;            // ��־λ

uint8_t aRxBuffer2;                       // �����жϻ���
char Uart2_RxBuff[256];                   // ���ջ���
uint8_t Uart2_Rx_Cnt = 0;                 // ���ջ������

// �������
char uart2_data[256];

uart_state uart2_state = FREE;            // ��־λ

// -------------------------------------------------------

void uart_rev_init() {
    uart1_state = FREE;
    uart2_state = FREE;
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer1, 1);   //�ٿ��������ж�
    HAL_UART_Receive_IT(&huart2, (uint8_t *) &aRxBuffer2, 1);   //�ٿ��������ж�
}

void send_uart(char *msg) {
    send_uart1(msg);
    send_uart2(msg);
}

void send_uart1(char *msg) {
    if (huart1.gState == HAL_UART_STATE_READY && Uart1_Tx_All == 0) {
        uart1_send_data = msg;
        Uart1_Tx_All = strlen(msg);
        Uart1_Tx_Cnt = 0;
        aTxBuffer1 = uart1_send_data[Uart1_Tx_Cnt];
        HAL_UART_Transmit_IT(&huart1, (uint8_t *) &aTxBuffer1, 1);
    }
}

void send_uart1_sprint(char *msg, ...) {
    if (huart1.gState == HAL_UART_STATE_READY && Uart1_Tx_All == 0) {

        // "/r/n"
        char pStr[255];
        memset(pStr, 0, 255);
        va_list args;

        va_start(args, msg);
        vsprintf(pStr, msg, args);
        va_end(args);

        uart1_send_data = pStr;
        Uart1_Tx_All = strlen(pStr);
        Uart1_Tx_Cnt = 0;
        aTxBuffer1 = uart1_send_data[Uart1_Tx_Cnt];
        HAL_StatusTypeDef statusTypeDef = HAL_UART_Transmit_IT(&huart1, (uint8_t *) &aTxBuffer1, 1);
        if (statusTypeDef != HAL_OK) {
            Uart1_Tx_Cnt--;
        }
    }
}

void send_uart1_loop() {
    if (huart1.gState == HAL_UART_STATE_READY) {
        if (Uart1_Tx_Cnt < Uart1_Tx_All) {
            Uart1_Tx_Cnt++;
            aTxBuffer1 = uart1_send_data[Uart1_Tx_Cnt];
            HAL_StatusTypeDef statusTypeDef = HAL_UART_Transmit_IT(&huart1, (uint8_t *) &aTxBuffer1, 1);
            if (statusTypeDef != HAL_OK) {
                Uart1_Tx_Cnt--;
            }
        } else {
            Uart1_Tx_All = 0;
        }
    }
}

void send_uart2(char *msg) {
    if (huart2.gState == HAL_UART_STATE_READY && Uart2_Tx_All == 0) {
        uart2_send_data = msg;
        Uart2_Tx_All = strlen(msg);
        Uart2_Tx_Cnt = 0;
        aTxBuffer2 = uart2_send_data[Uart2_Tx_Cnt];
        HAL_UART_Transmit_IT(&huart2, (uint8_t *) &aTxBuffer2, 1);
    }
}

void send_uart2_sprint(char *msg, ...) {
    if (huart2.gState == HAL_UART_STATE_READY && Uart2_Tx_All == 0) {

        // "/r/n"
        char pStr[255];
        memset(pStr, 0, 255);
        va_list args;

        va_start(args, msg);
        vsprintf(pStr, msg, args);
        va_end(args);

        uart2_send_data = pStr;
        Uart2_Tx_All = strlen(pStr);
        Uart2_Tx_Cnt = 0;
        aTxBuffer2 = uart2_send_data[Uart2_Tx_Cnt];
        HAL_StatusTypeDef statusTypeDef = HAL_UART_Transmit_IT(&huart2, (uint8_t *) &aTxBuffer2, 1);
        if (statusTypeDef != HAL_OK) {
            Uart2_Tx_Cnt--;
        }
    }
}

void send_uart2_loop() {
    if (huart2.gState == HAL_UART_STATE_READY) {
        if (Uart2_Tx_Cnt < Uart2_Tx_All) {
            Uart2_Tx_Cnt++;
            aTxBuffer2 = uart2_send_data[Uart2_Tx_Cnt];
            HAL_StatusTypeDef statusTypeDef = HAL_UART_Transmit_IT(&huart2, (uint8_t *) &aTxBuffer2, 1);
            if (statusTypeDef != HAL_OK) {
                Uart2_Tx_Cnt--;
            }
        } else {
            Uart2_Tx_All = 0;
        }
    }
}

/**
 * �ж�ѭ��
 * @param huart
 */
void uart_send_all_loop(UART_HandleTypeDef *huart) {
    UNUSED(huart);
    if (huart->Instance == USART1) {
        send_uart1_loop();
    } else if (huart->Instance == USART2) {
        send_uart2_loop();
    }
}

void uart1_loop() {

    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer1, 1);   //�ٿ��������ж�

    if (Uart1_Rx_Cnt >= 255)  //����ж�
    {
        // ����
        Uart1_Rx_Cnt = 0;
        memset(Uart1_RxBuff, 0x00, sizeof(Uart1_RxBuff));
        //HAL_UART_Transmit(&huart1, (uint8_t *) &cAlmStr, sizeof(cAlmStr), 0xFFFF);

        memset(uart1_data, 0, sizeof(cAlmStr));
        // ���Ƶ������
        strcpy(uart1_data, (char *) cAlmStr);
        // ���豨��״̬
        uart1_state = ERR404;
    } else {
        if (uart1_state == FREE) {
            Uart1_Rx_Cnt = 0;
            memset(Uart1_RxBuff, 0x00, sizeof(Uart1_RxBuff));
        }
        if (uart1_state == FINISH || uart1_state == ERR404) {
            return;
        }
        // ����
        Uart1_RxBuff[Uart1_Rx_Cnt++] = aRxBuffer1;   //��������ת��
        uart1_state = RUNNING;

        if (Uart1_Rx_Cnt > 2 && (Uart1_RxBuff[Uart1_Rx_Cnt - 1] == 0x0A) &&
            (Uart1_RxBuff[Uart1_Rx_Cnt - 2] == 0x0D)) //�жϽ���λ
        {
            memset(uart1_data, 0, sizeof(uart1_data));
            // ���Ƶ�ָ���ڴ�
            strcpy(uart1_data, Uart1_RxBuff);
            // ������ɽ��
            uart1_state = FINISH;
            //HAL_UART_Transmit(&huart1, (uint8_t *) &Uart1_RxBuff, Uart1_Rx_Cnt, 0xFFFF); //���յ�����Ϣ���ͳ�ȥ
            // ��ջ���
            Uart1_Rx_Cnt = 0;
            memset(Uart1_RxBuff, 0x00, sizeof(Uart1_RxBuff)); //�������
        }
    }

}

void uart2_loop() {
    HAL_UART_Receive_IT(&huart2, (uint8_t *) &aRxBuffer2, 1);   //�ٿ��������ж�

    if (Uart2_Rx_Cnt >= 255)  //����ж�
    {
        // ����
        Uart2_Rx_Cnt = 0;
        memset(Uart2_RxBuff, 0x00, sizeof(Uart2_RxBuff));
        //HAL_UART_Transmit(&huart2, (uint8_t *) &cAlmStr, sizeof(cAlmStr), 0xFFFF);

        memset(uart2_data, 0, sizeof(cAlmStr));
        // ���Ƶ������
        strcpy(uart2_data, (char *) cAlmStr);
        // ���豨��״̬
        uart2_state = ERR404;
    } else {
        if (uart2_state == FREE) {
            Uart2_Rx_Cnt = 0;
            memset(Uart2_RxBuff, 0x00, sizeof(Uart2_RxBuff));
        }
        if (uart2_state == FINISH || uart2_state == ERR404) {
            return;
        }
        // ����
        Uart2_RxBuff[Uart2_Rx_Cnt++] = aRxBuffer2;   //��������ת��
        uart2_state = RUNNING;

        if (Uart2_Rx_Cnt > 2 && (Uart2_RxBuff[Uart2_Rx_Cnt - 1] == 0x0A) &&
            (Uart2_RxBuff[Uart2_Rx_Cnt - 2] == 0x0D) &&
            (strstr(Uart2_RxBuff, "OK") != 0 || strstr(Uart2_RxBuff, "ERROR") != 0 ||
             strstr(Uart2_RxBuff, "busy") != 0 || strstr(Uart2_RxBuff, "#\r\n") != 0)) //�жϽ���λ
        {
            memset(uart2_data, 0, sizeof(uart2_data));
            // ���Ƶ�ָ���ڴ�
            strcpy(uart2_data, Uart2_RxBuff);
            // ������ɽ��
            uart2_state = FINISH;
            //HAL_UART_Transmit(&huart2, (uint8_t *) &Uart2_RxBuff, Uart2_Rx_Cnt, 0xFFFF); //���յ�����Ϣ���ͳ�ȥ
            // ��ջ���
            Uart2_Rx_Cnt = 0;
            memset(Uart2_RxBuff, 0x00, sizeof(Uart2_RxBuff)); //�������
        }
    }
}

/**
 * �ж�ѭ��
 * @param huart
 */
void uart_rev_all_loop(UART_HandleTypeDef *huart) {
    UNUSED(huart);
    if (huart->Instance == USART1) {
        uart1_loop();
    } else if (huart->Instance == USART2) {
        uart2_loop();
    }
}