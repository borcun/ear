/**
 * @file serial_device.h
 * @brief
 * @author boo
 * @copyright
 */

#ifndef SERIAL_DEVICE_H
#define SERIAL_DEVICE_H

#include "position.h"
#include "io_device.h"

class SerialDevice : public EAR::IODevice {
 public:
  SerialDevice();
  virtual ~SerialDevice();

  virtual int32_t open();
  virtual int32_t close();
  virtual int32_t read(uint8_t *buf, const uint32_t size);
  virtual int32_t write(const uint8_t *buf, const uint32_t size);
  virtual int32_t ioctl(void *target, const int32_t op);

private:
    Position pos = {0.0f, 0.0f};
};

#endif
