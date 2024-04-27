#include "gps.h"

GPS::GPS() : EAR::Schedule::PeriodicTask() { }

GPS::~GPS() { }

void GPS::setDevice(EAR::IO::Device *dev) {
    m_dev = dev;
}

void GPS::process() {
    uint8_t data[8];
	
    if (nullptr != m_dev) {
	if (0 < m_dev->receive(data, 8)) {
	    spdlog::info("received from device {}", getId());
	}
	else {
	    spdlog::warn("gps task {} read failed", getId());
	}
    }
    
    return;
}
