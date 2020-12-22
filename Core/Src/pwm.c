//
// Created by mayn on 2020/11/23 0023.
//

#include <pwm.h>
#include <stdint-gcc.h>
#include <tim.h>

int const spwm[250] =
        {
                100, 102, 108, 116, 126, 140, 154, 172, 194, 216,
                242, 270, 300, 334, 370, 408, 448, 490, 536, 582,
                632, 684, 738, 794, 854, 914, 976, 1040, 1108, 1176,
                1246, 1320, 1394, 1470, 1548, 1626, 1708, 1790, 1874, 1960,
                2046, 2136, 2224, 2316, 2408, 2502, 2596, 2690, 2786, 2884,
                2982, 3080, 3180, 3280, 3382, 3482, 3584, 3686, 3788, 3892,
                3994, 4096, 4200, 4304, 4406, 4508, 4612, 4714, 4816, 4918,
                5018, 5120, 5220, 5320, 5418, 5516, 5614, 5710, 5804, 5898,
                5992, 6084, 6176, 6264, 6354, 6440, 6526, 6610, 6692, 6774,
                6852, 6930, 7006, 7080, 7154, 7224, 7292, 7360, 7424, 7486,
                7546, 7606, 7662, 7716, 7768, 7818, 7864, 7910, 7952, 7992,
                8030, 8066, 8100, 8130, 8158, 8184, 8206, 8228, 8246, 8260,
                8274, 8284, 8292, 8298, 8300, 8300, 8298, 8292, 8284, 8274,
                8260, 8246, 8228, 8206, 8184, 8158, 8130, 8100, 8066, 8030,
                7992, 7952, 7910, 7864, 7818, 7768, 7716, 7662, 7606, 7546,
                7486, 7424, 7360, 7292, 7224, 7154, 7080, 7006, 6930, 6852,
                6774, 6692, 6610, 6526, 6440, 6354, 6264, 6176, 6084, 5992,
                5898, 5804, 5710, 5614, 5516, 5418, 5320, 5220, 5120, 5018,
                4918, 4816, 4714, 4612, 4508, 4406, 4304, 4200, 4096, 3994,
                3892, 3788, 3686, 3584, 3482, 3382, 3280, 3180, 3080, 2982,
                2884, 2786, 2690, 2596, 2502, 2408, 2316, 2224, 2136, 2046,
                1960, 1874, 1790, 1708, 1626, 1548, 1470, 1394, 1320, 1246,
                1176, 1108, 1040, 976, 914, 854, 794, 738, 684, 632,
                582, 536, 490, 448, 408, 370, 334, 300, 270, 242,
                216, 194, 172, 154, 140, 126, 116, 108, 102, 100
        };

uint16_t Counter_sine1 = 0; //A相
uint16_t Counter_sine2 = 83; //滞后A相120度
uint16_t Counter_sine3 = 166;//超前A相120度

uint16_t arr = 7199;

/********中断服务函数**************/
void iqHandler() {

//    if (__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_CHANNEL_1) == SET)//溢出中断
//    {
    __HAL_TIM_CLEAR_IT(&htim1, TIM_CHANNEL_1);//清除中断标志位

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, spwm[Counter_sine1]);
    //Log("TIM_CHANNEL_1: %d\r\n", spwm[Counter_sine1]);
    //TIM_SetCompare1(TIM1, spwm[Counter_sine1]);
    Counter_sine1++;
    if (Counter_sine1 == 250) { Counter_sine1 = 0; }

    //}
//    if (__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_CHANNEL_2) == SET)//溢出中断
//    {
    __HAL_TIM_CLEAR_IT(&htim1, TIM_CHANNEL_2);//清除中断标志位

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, spwm[Counter_sine2]);
    //Log("TIM_CHANNEL_2: %d\r\n", spwm[Counter_sine2]);
//        TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);//清除中断标志位
//
//        TIM_SetCompare2(TIM1, spwm[Counter_sine2]);
    Counter_sine2++;
    if (Counter_sine2 == 250) { Counter_sine2 = 0; }
    //}
//    if (__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_CHANNEL_3) == SET)//溢出中断
//    {
    __HAL_TIM_CLEAR_IT(&htim1, TIM_CHANNEL_3);//清除中断标志位

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, spwm[Counter_sine3]);
    //Log("TIM_CHANNEL_3: %d\r\n", spwm[Counter_sine3]);
//        TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);//清除中断标志位
//
//        TIM_SetCompare3(TIM1, spwm[Counter_sine3]);
    Counter_sine3++;
    if (Counter_sine3 == 250) { Counter_sine3 = 0; }
//    }
}