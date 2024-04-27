#pragma once

#include "device.h"
#include "periodic_task.h"
#include "transmitter.h"

class GPS : public EAR::Schedule::PeriodicTask {
 public:
    GPS();
    virtual ~GPS();
    void setDevice(EAR::IO::Device *dev);
    void setClient(EAR::Communication::Transmitter *client);
    virtual void process() override;

private:
    EAR::IO::Device *m_dev = nullptr;
    EAR::Communication::Transmitter *m_client = nullptr;
};
