#pragma once

#include "device.h"
#include "task.h"
#include "transmitter.h"

class GPS : public EAR::Schedule::Task {
public:
    GPS(const std::string &name);
    virtual ~GPS();
    void setDevice(EAR::IO::Device *dev);
    void setTransmitter(EAR::Communication::Transmitter *transmitter);

    virtual bool initialize() override;
    virtual void cycle() override;

private:
    EAR::IO::Device *m_dev = nullptr;
    EAR::Communication::Transmitter *m_transmitter = nullptr;
};
