#ifndef BIT_H
#define BIT_H

#include "pcs.h"
#include "ps.h"
#include "periodic_task.h"
#include "aperiodic_task.h"
#include "scheduler.h"

class BIT : public FACE::PeriodicTask {
 public:
    BIT(FACE::PCSS::PortableComponentService *pcs);
    virtual ~BIT();
    void addHelperService(FACE::PSSS::PlatformService *dev);
    bool init();
    virtual void process() override;
    
 private:
    FACE::PCSS::PortableComponentService *m_pcs;
    FACE::Scheduler m_aper_sched;
};

#endif
