#ifndef DCU_H
#define DCU_H

#include "periodic_task.h"
#include "subscriber.h"

class DCU : public EAR::PeriodicTask, public EAR::Subscriber {
 public:
    DCU(const std::string &node);
    virtual ~DCU();
    virtual void process() override;
};

#endif
