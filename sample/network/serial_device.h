/**
 * @file serial_device.h
 * @brief
 * @author boo
 * @copyright
 */

#pragma once

#include "position.h"
#include "device.h"

class SerialDevice : public EAR::IO::Device {
public:
    SerialDevice();
    virtual ~SerialDevice();
    virtual int32_t initialize() override;
    virtual int32_t shutdown() override;
    virtual int32_t receive(void *buf, const uint32_t size) override;
    virtual int32_t transmit(const void *buf, const uint32_t size) override;
    virtual int32_t configure(void *target, const int32_t op) override;

private:
    Position pos = {0.0f, 0.0f};
};
