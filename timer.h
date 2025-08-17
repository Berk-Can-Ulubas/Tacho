/**
 ******************************************************************************
 * @file    timer.h
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Timer Module encapsulates the TIM2 timer to sleep, get curent time and calculate time differences.
 ******************************************************************************
 */
#ifndef __TIMER__H__
#define __TIMER__H__
#include <stdint.h>

uint32_t getTimeStamp(void);

double timeDiff(uint32_t start, uint32_t end);

void sleep(double zeit);

void init_timer(void);

#endif  //!__TIMER__H__