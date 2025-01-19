#pragma once

#include "io/device.h"
#include "sched/task.h"
#include "comm/transmitter.h"

class LocationService : public EAR::Schedule::Task {
public:
  explicit LocationService(const std::string &name);
  virtual ~LocationService();
  void setDevice(EAR::IO::Device *dev);
  void setEndpointConfiguration(const EAR::Communication::Configuration &ep_config);
  virtual bool initialize() override;
  virtual void cycle() override;

private:
  EAR::IO::Device *m_dev = nullptr;
  EAR::Communication::Configuration m_ep_config;
  EAR::Communication::Transmitter m_endpoint {"loc-serv-ep"};
};
