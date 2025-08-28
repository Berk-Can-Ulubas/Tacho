/**
 ******************************************************************************
 * @file    timer.c
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Timer Module encapsulates the TIM2 timer to sleep, get curent time and calculate time differences.
 ******************************************************************************
 */
#include "timer.h"
#include "stm32f4xx.h"

#define TICKS_PER_SECOND 90000000 // 90MHz clock
#define TICKS_PER_MS 90000
#define TICKS_PER_US 90

void init_timer(void)
{
    // 1. Enable clock for TIM2 (TIM2 is connected to APB1 bus)
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // disable timer 
    TIM2->CR1 = 0;

    TIM2->CR2 = 0; //  control register 2 not used 

    // set prescaler (90 MHz) 
    TIM2->PSC = 0;

    // set auto-reload register (maximum counter value)
    TIM2->ARR = 0xFFFFFFFF;   // 32-bit 

    //disable the update interrupt
    TIM2->DIER  = 0;

    // enable timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

uint32_t getTimeStamp(void);
{
    return TIM2->CNT;
}

double timeDiff(uint32_t start, uint32_t end)
{
	double diff;
    if (end < start) 
	{
		diff = (0xFFFFFFFF - start) + end;
    }
	else 
	{
		diff = end - start;
    }
	return (diff / TICKS_PER_US);
}

void sleep(double time)
{
	double t1 = getTimeStamp();
	while(timeDiff(t1, getTimeStamp()) < time)
    {
		//NOP
	}
}

