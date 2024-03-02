#include "service.h"

FACE::Service::Service(const std::string &name) {
  m_name = name;
}

FACE::Service::~Service() {

}

uint32_t FACE::Service::getId() const {
  return m_id;
}

std::string FACE::Service::getName() const {
  return m_name;
}
