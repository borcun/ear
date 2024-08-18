#pragma once

#include "task.h"

class DCU : public EAR::Schedule::Task {
public:
  explicit DCU(const std::string &name);
  virtual ~DCU();

  bool initialize(void);
  void cycle(void);
};
