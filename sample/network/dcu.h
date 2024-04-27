#pragma once

#include "periodic_task.h"
#include "listener.h"

class DCU : public EAR::Schedule::PeriodicTask {
public:
    DCU();
    virtual ~DCU();
    void setServer(EAR::Communication::Listener *server);
    virtual void process() override;

private:
    EAR::Communication::Listener *m_server = nullptr;
};
