/**
 ******************************************************************************
 * @file    bmp180.c
 * @author  Berk Can Ulubas
 * @date    13.08.2025
 * @brief   Digital pressure sensor
 ******************************************************************************
 */

 //PA3 is SCL for I2C communication for I2C communication of the BMP180 sensor.
 //PA4 is for the pull-up resistor of the SLC pin.
 //PA5 is SDA for I2C communication of the BMP180 sensor.
 //PA6 is for the pull-up resistor of the SDA pin.

#include "bmp180.h"