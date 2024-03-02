/**
 * @file pscs.h
 * @brief
 * @author boo
 */

#ifndef COMMON_SERVICE_H
#define COMMON_SERVICE_H

#include "service.h"

namespace PSSS {
  class CommonService : public FACE::Service {
  public:
    CommonService(const std::string &name);
    virtual ~CommonService();
  };
}

#endif
