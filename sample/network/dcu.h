#pragma once

#include "task.h"
#include "listener.h"

class DCU : public EAR::Schedule::Task {
public:
    DCU(const std::string &name);
    virtual ~DCU();
    void setServer(EAR::Communication::Listener *server);
    virtual bool initialize() override;
    virtual void cycle() override;

private:
    EAR::Communication::Listener *m_server = nullptr;
};
