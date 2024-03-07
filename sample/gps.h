#ifndef GPS_H
#define GPS_H

#include "pss.h"

class GPS : public FACE::PSSS::PlatformService {
 public:
    GPS(const std::string &name);
    virtual ~GPS();
    virtual void process() override;
};

#endif
