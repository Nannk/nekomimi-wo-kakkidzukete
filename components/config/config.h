#pragma once

#ifndef Config_h
#define Config_h

#include <i2c.h>

// #define SCL D1
// #define SDA D2

// Left
#define LMAINPIN 0 // D3 // 5
//    wings
#define LLEFTWINGPIN 14  // D5  // 3
#define LRIGHTWINGPIN 12 // D6 // 6

// Right
#define RMAINPIN 2 // D4 // 10
//    wings
#define RLEFTWINGPIN 13  // D7  // 9
#define RRIGHTWINGPIN 15 // D8 // 11

#define MIN_MICROS 500
#define MAX_MICROS 2400

// TODO: set the correct values here
#define I2C_MASTER_SCL_IO 5 /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 4 /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM                                                         \
  I2C_NUM_0                         /*!< I2C port number for master dev        \
                                     */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master do not need buffer */

#define MPU9250_SENSOR_ADDR 0x68   /*!< slave address for MPU9250 sensor */
#define MPU9250_CMD_START 0x41     /*!< Command to set measure mode */
#define MPU9250_WHO_AM_I 0x75      /*!< Command to read WHO_AM_I reg */
#define WRITE_BIT I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ   /*!< I2C master read */
#define ACK_CHECK_EN 0x1           /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0 /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0       /*!< I2C ack value */
#define NACK_VAL 0x1      /*!< I2C nack value */
#define LAST_NACK_VAL 0x2 /*!< I2C last_nack value */

/**
 *  TODO: Define the mpu9250 register address:
 */
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define PWR_MGMT_1 0x6B
#define WHO_AM_I 0x75 /*!< Command to read WHO_AM_I reg */

#endif
