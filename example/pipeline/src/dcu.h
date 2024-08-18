#pragma once

#include "task.h"

class DCU : public EAR::Schedule::Task {
public:
  explicit DCU(const std::string &name);
  virtual ~DCU();
  virtual bool initialize(void) override;
  virtual void cycle(void) override;
};
