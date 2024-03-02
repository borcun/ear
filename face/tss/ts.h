/**
 * @file ts.h
 * @brief
 * @author boo
 */

#ifndef TRANSPORT_SERVICE_H
#define TRANSPORT_SERVICE_H

#include "service.h"

namespace TSS {
  class TransportService : public FACE::Service {
  public:
    TransportService(const std::string &name);
    virtual ~TransportService();
  };
}

#endif
