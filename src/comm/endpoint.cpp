#include "endpoint.h"

EAR::Communication::Endpoint::Endpoint(const std::string &name)
    : m_name(name)
{
}

EAR::Communication::Endpoint::~Endpoint()
{
}

std::string EAR::Communication::Endpoint::getName() const {
    return m_name;
}

EAR::Communication::State EAR::Communication::Endpoint::getState() const {
    return m_state;
}
