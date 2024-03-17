#ifndef GPS_H
#define GPS_H

#include "ps.h"
#include "aperiodic_task.h"

class GPS : public FACE::PSSS::PlatformService, public FACE::APeriodicTask {
 public:
    GPS(const std::string &name);
    virtual ~GPS();
    virtual void process() override;
};

#endif
