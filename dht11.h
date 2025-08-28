/**
 ******************************************************************************
 * @file    dht11.h
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Humidity & Temperature Sensor
 ******************************************************************************
 */
#ifndef __DHT11__H__
#define __DHT11__H__

#include <stdint.h>

void init_dht11(void);

int read_data_dht11(uint8_t *temperature, uint8_t *humidity);

#endif  //!__DHT11__H__