#pragma once

#include "sched/task.h"
#include "comm/receiver.h"

class DCUService : public EAR::Schedule::Task {
public:
  explicit DCUService(const std::string &name);
  virtual ~DCUService();
  void setEndpointConfiguration(const EAR::Communication::Configuration &ep_config);
  virtual bool initialize(void) override;
  virtual void cycle(void) override;

private:
  EAR::Communication::Configuration m_ep_config;
  EAR::Communication::Receiver m_endpoint {"dcu-ep"};
};
