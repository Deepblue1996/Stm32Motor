//
// Created by mayn on 2020/11/23 0023.
//

#ifndef FREERTOS_PWM_H
#define FREERTOS_PWM_H

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

#define CKTIM       ((u32)100000000uL)  //��Ƶ
#define PWM_PRSC    ((u8)1)            //TIM1��Ƶϵ��
// 0 - 2100000-2000(����) ��ת Խ��Խ��
// 1 - 16000 ��ת(��԰���)
#define PWM_FREQ    ((u16) 18000)      //PWMƵ��(Hz)
#define PWM_PERIOD  ((u16) (CKTIM / (u32)(2 * PWM_FREQ *(PWM_PRSC+1))))

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void sHandler();
void iqHandler();

#endif //FREERTOS_PWM_H
