#include "gps.h"

GPS::GPS(const std::string &name)
  : EAR::Schedule::Task(name)
{
}

GPS::~GPS() {
}

void GPS::setDevice(EAR::IO::Device *dev) {
    m_dev = dev;
    return;
}

bool GPS::initialize(void) {
    spdlog::info("GPS task {} initialized", getName());
    return true;
}

void GPS::cycle(void) {
    uint8_t data[8];
	
    if (nullptr != m_dev) {
	if (0 < m_dev->receive(data, 8)) {
	    spdlog::info("{} received data from device {}", getName(), m_dev->toString());
	}
	else {
	    spdlog::warn("GPS task {} read failed", getName());
	}
    }
    
    return;
}
