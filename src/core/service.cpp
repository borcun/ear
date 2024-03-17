#include "service.h"

FACE::Service::Service(const std::string &name) {
  m_name = name;
}

FACE::Service::~Service() {

}

const std::string &FACE::Service::getName() const {
  return m_name;
}
