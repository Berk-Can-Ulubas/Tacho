/**
 ******************************************************************************
 * @file    gpio.c
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   GPIO Module encapsulates the GPIOA port to set pin modes and states.
 ******************************************************************************
 */

#include "gpio.h"
#include "stm32f4xx.h"
#include "timer.h"

void set_GPIOA_pin_input(pin)
{
    GPIOA->MODER &= ~(3 << (2 * pin));
}

void set_GPIOA_pin_output(pin)
{
    GPIOA->MODER &= ~(3 << (2 * pin));
    GPIOA->MODER |= (1 << (2 * pin));
}

void set_GPIOA_pin_high(pin)
{
    GPIOA->BSSR = (1 << pin);
}

void set_GPIOA_pin_low(pin)
{
    GPIOA->BSSR = (1 << (pin + 16));
}

int polling_GPIOA_pin(int value, pin)
{
    uint32_t t1 = getTimeStamp();
    uint32_t t2 = t1;
    while ((GPIOA->IDR & (1 << pin)) >> pin == value) 
    {
        t2 = getTimeStamp();
    }
    return timeDiff(t1, t2);
}

int read_GPIOA_pin(pin)
{
    return (GPIOA->IDR & (1 << pin)) >> pin;
}

void set_GPIOA_pin_mode(pin, PinType type)
{
    if (type == OPEN_DRAIN)
    {
        GPIOA->OTYPER |= (1 << pin);
    }
    else // PUSH_PULL
    {
        GPIOA->OTYPER &= ~(1 << pin);
    }
}