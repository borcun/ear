/**
 * @file gpio_service.h
 * @brief
 * @author boo
 * @copyright
 */

#ifndef GPIO_SERVICE_H
#define GPIO_SERVICE_H

#include "ios.h"

class GPIOService : public FACE::IOSS::IOService {
 public:
  explicit GPIOService(const std::string &name);
  virtual ~GPIOService();

  virtual int32_t open();
  virtual int32_t close();
  virtual int32_t read(uint8_t *buf, const uint32_t size);
  virtual int32_t write(const uint8_t *buf, const uint32_t size);
  virtual int32_t ioctl(void *target, const int32_t op);
};

#endif
