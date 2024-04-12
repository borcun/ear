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
    virtual int32_t initialize() override;
    virtual int32_t shutdown() override;
    virtual int32_t receive(uint8_t *buf, const uint32_t size) override;
    virtual int32_t transmit(const uint8_t *buf, const uint32_t size) override;
    virtual int32_t configure(void *target, const int32_t op) override;

private:
    Position pos = {0.0f, 0.0f};
};

#endif
