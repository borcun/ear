#pragma once

#include "task.h"

class DCU : public EAR::Schedule::Task {
public:
    DCU(const std::string &name);
    virtual ~DCU();
    virtual bool initialize() override;
    virtual void cycle() override;
};
