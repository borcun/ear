#pragma once

#include "periodic_task.h"

class DCU : public EAR::Schedule::PeriodicTask {
 public:
    DCU();
    virtual ~DCU();
    virtual void process() override;
};
