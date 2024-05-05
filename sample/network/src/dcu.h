#pragma once

#include "task.h"
#include "receiver.h"

class DCU : public EAR::Schedule::Task {
public:
    DCU(const std::string &name);
    virtual ~DCU();
    virtual bool initialize() override;
    virtual void cycle() override;

    void setReceiver(EAR::Communication::Receiver *receiver);

private:
    EAR::Communication::Receiver *m_receiver = nullptr;
};
