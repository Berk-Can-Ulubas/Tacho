/**
 ******************************************************************************
 * @file    gpio.h
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   GPIO Module encapsulates the GPIOA port to set pin modes and states.
 ******************************************************************************
 */

#ifndef __GPIO__H__
#define __GPIO__H__

void set_GPIOA_pin_input(void);
void set_GPIOA_pin_output(void);
void set_GPIOA_pin_high(void);
void set_GPIOA_pin_low(void);
int polling_GPIOA_pin(int value);
int read_GPIOA_pin(void);
void set_GPIOA_pin_mode(int pin, PinType type);

typedef enum {
    PUSH_PULL,
    OPEN_DRAIN
} PinType;

#endif  //!__GPIO__H__