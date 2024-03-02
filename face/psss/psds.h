/**
 * @file psds.h
 * @brief
 * @author boo
 */

#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H

#include "service.h"

namespace FACE {
  namespace PSSS {
    class DeviceService : public Service {
    public:
      DeviceService(const std::string &name);
      virtual ~DeviceService();
    };
  }
}

#endif
