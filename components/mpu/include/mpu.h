#ifndef mpu_h
#define mpu_h

#include "driver/i2c.h"
#include <esp_err.h>

class Mpu {
public:
  esp_err_t mpu9250_read(i2c_port_t i2c_num, uint8_t reg_address, uint8_t *data,
                         size_t data_len);
  esp_err_t mpu9250_init(i2c_port_t i2c_num);
  esp_err_t mpu9250_write(i2c_port_t i2c_num, uint8_t reg_address,
                          uint8_t *data, size_t data_len);

private:
};

#endif
