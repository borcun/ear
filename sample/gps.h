#ifndef GPS_H
#define GPS_H

#include "ps.h"

class GPS : public FACE::PSSS::PlatformService {
 public:
    GPS(const std::string &name);
    virtual ~GPS();
    virtual void service() override;
};

#endif
