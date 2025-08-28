/**
 ******************************************************************************
 * @file    dht11.c
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Humidity & Temperature Sensor
 ******************************************************************************
 */
//PA1 is for one wire bus communication of the DHT11 sensor.

#include "dht11.h"
#include "timer.h"
#include "stm32f4xx.h"
#include "gpio.h"

#define data_pin_dht11 1 //PA1

static void start_signal_dht11(void);
static int read_response_dht11(void);
static int read_bit_dht11(void);
static uint8_t read_byte_dht11(void);

void init_dht11()
{
    set_GPIOA_pin_mode(data_pin_dht11, OPEN_DRAIN);
}

void start_signal_dht11()
{
    set_GPIOA_pin_output(data_pin_dht11);

    set_GPIOA_pin_low(data_pin_dht11);
    sleep(18000);

    set_GPIOA_pin_high(data_pin_dht11);
    sleep(20);
}

int read_response_dht11(void)
{
    polling_GPIOA_pin(1, data_pin_dht11);

    double response_time1 = polling_GPIOA_pin(0, data_pin_dht11);
    double response_time2 = polling_GPIOA_pin(1, data_pin_dht11);
    return response_time1 > 70 && response_time1 < 90 && response_time2 > 70 && response_time2 < 90;
}

int read_bit_dht11(void)
{
    double low_pulse_time = polling_GPIOA_pin(0, data_pin_dht11);
    if (low_pulse_time < 40 || low_pulse_time > 60)
    {
        return -1; // error
    }
    double high_pulse_time = polling_GPIOA_pin(1, data_pin_dht11);
    if (high_pulse_time < 40)
    {
        return 0; 
    }
    else
    {
        return 1; 
    }
}

uint8_t read_byte_dht11(void)
{
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++)
    {
        int bit = read_bit_dht11();
        if (bit == -1) {
            return 0xFF; // error
        }
        byte = (byte << 1) | bit;
    }
    return byte;
}

int read_data_dht11(uint8_t *temperature, uint8_t *humidity)
{
    start_signal_dht11();
    if (!read_response_dht11()) 
    { 
        return -3; // response error
    }
    uint8_t expected_checksum = 0;
    uint8_t integral_RH = read_byte_dht11();
    uint8_t decimal_RH = read_byte_dht11();
    uint8_t integral_T = read_byte_dht11();
    uint8_t decimal_T = read_byte_dht11();
    expected_checksum = integral_RH + decimal_RH + integral_T + decimal_T;
    uint8_t real_checksum = read_byte_dht11();
    if (integral_RH == 0xFF || integral_T == 0xFF || decimal_RH == 0xFF || decimal_T == 0xFF || real_checksum == 0xFF)
    {
        return -1; // bit start puls error
    }
    else if (expected_checksum != real_checksum)
    {
        return -2; // checksum error
    } else {
        *humidity = integral_RH;
        *temperature = integral_T;
        return 0;
    }
}