/**
 ******************************************************************************
 * @file    a3144.c
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Hall Effect Transistor
 ******************************************************************************
 */
//PA0 is connected to the A3144 Hall Effect Sensor and uses the EXTI0 interrupt.
#include "a3144.h"
#include "stm32f4xx.h"

volatile int count = 0; // Global variable to count interrupts

void A3144_Init(void)
{
    routing(); // Routing for the interrupt
    iqr();     // Interrupt request
    nvic_priority(); // NVIC priority setup
}



void routing()
{
	// Component selection
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Clock for GPIO Port A
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // System conf. Clock enable
	// Routing Pin 0 of Port A -> EXTI0
	SYSCFG->EXTICR[0] &= ~(0x0F << (4 * 0)); // Remove old selection
	SYSCFG->EXTICR[0] |= 0x00 << (4 * 0);	 
}

void iqr() // which action should cause an interrupt
{
	EXTI->RTSR |= (1 << 0); // select rising trigger for INT0
	EXTI->FTSR |= (1 << 0); // select falling trigger for INT0
	EXTI->IMR |= (1 << 0);	// Unmask INT0
}

void nvic_priority()
{
	NVIC_SetPriorityGrouping(2); // Setup interrupt controller:
	// 4 subpriority for each priority

	NVIC_SetPriority(EXTI0_IRQn, 0); // Setup EXTI0:
	// priority = 0, subpriority = 0
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable EXTI0
}

void EXTI0_IRQHandler(void) 
{
	EXTI->PR |= (1 << 0);// Clear pending bit for EXTI0
	count++; 
}
