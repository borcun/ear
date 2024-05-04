#pragma once

#include "device.h"
#include "task.h"

class GPS : public EAR::Schedule::Task {
public:
    GPS(const std::string &name);
    virtual ~GPS();
    void setDevice(EAR::IO::Device *dev);
    virtual bool initialize() override;
    virtual void cycle() override;

private:
    EAR::IO::Device *m_dev = nullptr;
};
