/**
 * @file serial_service.h
 * @brief
 * @author boo
 * @copyright
 */

#ifndef SERIAL_SERVICE_H
#define SERIAL_SERVICE_H

#include "position.h"
#include "ios.h"

class SerialService : public FACE::IOSS::IOService {
 public:
  explicit SerialService(const std::string &name);
  virtual ~SerialService();

  virtual int32_t open();
  virtual int32_t close();
  virtual int32_t read(uint8_t *buf, const uint32_t size);
  virtual int32_t write(const uint8_t *buf, const uint32_t size);
  virtual int32_t ioctl(void *target, const int32_t op);

private:
    Position pos = {0.0f, 0.0f};
};

#endif
