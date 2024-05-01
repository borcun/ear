#pragma once

#include "device.h"
#include "task.h"
#include "transmitter.h"

class GPS : public EAR::Schedule::Task {
public:
    GPS(const std::string &name);
    virtual ~GPS();
    void setDevice(EAR::IO::Device *dev);
    void setClient(EAR::Communication::Transmitter *client);

    virtual bool initialize() override;
    virtual void cycle() override;

private:
    EAR::IO::Device *m_dev = nullptr;
    EAR::Communication::Transmitter *m_client = nullptr;
};
