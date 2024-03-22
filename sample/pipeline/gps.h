#ifndef GPS_H
#define GPS_H

#include "io_device.h"
#include "periodic_task.h"

class GPS : public EAR::PeriodicTask {
 public:
    GPS();
    virtual ~GPS();
    void setIODevice(EAR::IODevice *iodev);
    virtual void process() override;

private:
    EAR::IODevice *m_iodev;
};

#endif
