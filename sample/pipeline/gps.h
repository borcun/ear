#pragma once

#include "device.h"
#include "periodic_task.h"

class GPS : public EAR::Schedule::PeriodicTask {
 public:
    GPS();
    virtual ~GPS();
    void setDevice(EAR::IO::Device *dev);
    virtual void process() override;

private:
    EAR::IO::Device *m_dev = nullptr;
};
