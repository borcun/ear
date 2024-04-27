#include "gps.h"

GPS::GPS() : EAR::Schedule::PeriodicTask() { }

GPS::~GPS() { }

void GPS::setDevice(EAR::IO::Device *dev) {
    m_dev = dev;
}

void GPS::setClient(EAR::Communication::Transmitter *client) {
    m_client = client;
}

void GPS::process() {
    uint8_t data[8];
	
    if (nullptr != m_dev) {
	if (0 < m_dev->receive(data, 8)) {
	    spdlog::info("received from device [{}]", getId());

	    if (nullptr != m_client) {
		size_t size = 8;
		
		if (m_client->send(data, size)) {
		    spdlog::info("send data to DCU [{}]", getId());
		}
		else {
		    spdlog::info("could not send data to DCU [{}]", getId());
		}
	    }
	}
	else {
	    spdlog::warn("gps task {} read failed", getId());
	}
    }
    
    return;
}
