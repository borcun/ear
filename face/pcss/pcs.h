/**
 * @file pcs.h
 * @brief
 * @author boo
 */

#ifndef PORTABLE_COMPONENT_SERVICE_H
#define PORTABLE_COMPONENT_SERVICE_H

#include "service.h"

namespace PCSS {
  class PortableComponentService : public FACE::Service {
  public:
    PortableComponentService(const std::string &name);
    virtual ~PortableComponentService();
  };
}

#endif
