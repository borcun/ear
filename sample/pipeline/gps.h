#ifndef GPS_H
#define GPS_H

#include "ios.h"
#include "periodic_service.h"
#include "node.h"

class GPS : public FACE::PeriodicService, public FACE::Node {
 public:
    GPS(const std::string &name);
    virtual ~GPS();
    void setIOService(FACE::IOSS::IOService *ios);
    virtual void process() override;

private:
    FACE::IOSS::IOService *m_ios;
};

#endif
