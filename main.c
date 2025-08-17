/**
 ******************************************************************************
 * @file    main.c
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Main file for the project
 ******************************************************************************
 */
#include "stm32f4xx.h"

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // GPIOB-Takt an
    GPIOB->MODER &= ~(3UL << (14 * 2));  // PB14: Ausgang
    GPIOB->MODER |= (1UL << (14 * 2));

    while (1)
    {
        GPIOB->ODR ^= GPIO_ODR_OD14; // LED toggeln
        for (volatile int i = 0; i < 1000000; i++)
            ;
    }
}