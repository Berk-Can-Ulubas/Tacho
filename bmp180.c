/**
 ******************************************************************************
 * @file    bmp180.c
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Digital pressure sensor
 ******************************************************************************
 */

 //PA2 is SCL and PA3 is SDA for I2C communication of the BMP180 sensor


#include "bmp180.h"
#include "timer.h"
#include "stm32f4xx.h"
#include "gpio.h"

#define sda 2
#define scl 3

#define OUT_XLSB_REGISTER 0xF8
#define OUT_LSB_REGISTER 0xF7
#define OUT_MSB_REGISTER 0xF6
#define CTRL_MEAS_REGISTER 0xF4
#define SOFT_RESET_REGISTER 0xE0
#define ID_REGISTER 0xD0
#define CALIB21_REGISTER 0xBF
#define CALIB0_REGISTER 0xAA

#define write 0
#define read 1

#define hold_time_START_condition 4 //tHD;STA
#define bus_free_time_STOP_START 4.7 //tBUF
#define set_up_time_STOP_condition 4 //tSU;STO


void init_bmp180()
{
    set_GPIOA_pin_mode(sda, OPEN_DRAIN);
    set_GPIOA_pin_mode(scl, OPEN_DRAIN);
    
    set_GPIOA_pin_output(sda);
    set_GPIOA_pin_output(scl);

    set_GPIOA_pin_high(sda);
    set_GPIOA_pin_high(scl);
}

void start_condition()
{
    set_GPIOA_pin_output(sda);
    set_GPIOA_pin_output(scl);

    set_GPIOA_pin_high(sda);
    set_GPIOA_pin_high(scl);
    
    sleep(bus_free_time_STOP_START));

    set_GPIOA_pin_low(sda);

    sleep(hold_time_START_condition);

    set_GPIOA_pin_low(scl);
}

void stop_condition()
{
    set_GPIOA_pin_output(sda);
    set_GPIOA_pin_output(scl);

    set_GPIOA_pin_low(sda);
    set_GPIOA_pin_high(scl);

    sleep(bus_free_time_STOP_START);

    set_GPIOA_pin_high(sda);

    sleep(set_up_time_STOP_condition);
}