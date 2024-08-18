#pragma once

#include "device.h"
#include "task.h"

class GPS : public EAR::Schedule::Task {
public:
  explicit GPS(const std::string &name);
  virtual ~GPS();
  void setDevice(EAR::IO::Device *dev);

  bool initialize(void);
  void cycle(void);

private:
  EAR::IO::Device *m_dev = nullptr;
};
