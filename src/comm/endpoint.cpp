#include "endpoint.h"

EAR::Communication::Endpoint::Endpoint() { }

EAR::Communication::Endpoint::~Endpoint() { }

EAR::Communication::State EAR::Communication::Endpoint::getState() const {
    return m_state;
}
