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
    SerialDevice(const std::string &name, const std::string &model, const std::string &version);
    virtual ~SerialDevice();
    virtual int32_t receive(void *buf, const uint32_t size) override;

private:
    Position pos = {0.0f, 0.0f};
};
