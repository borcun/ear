/**
 * @file pscs.h
 * @brief
 * @author boo
 */

#ifndef COMMON_SERVICE_H
#define COMMON_SERVICE_H

#include "service.h"

namespace FACE {
  namespace PSSS {
    class CommonService : public Service {
    public:
      CommonService(const std::string &name);
      virtual ~CommonService();
    };
  }
}

#endif
