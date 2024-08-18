#pragma once

#include "task.h"
#include "receiver.h"

class DCU : public EAR::Schedule::Task {
public:
    DCU(const std::string &name);
    virtual ~DCU();
    void setReceiver(EAR::Communication::Receiver *receiver);
    virtual bool initialize(void) override;
    virtual void cycle(void) override;

private:
    EAR::Communication::Receiver *m_receiver = nullptr;
};
