#include "gps.h"

GPS::GPS(const std::string &name) : PlatformService(name) {
}

GPS::~GPS() {
}

void GPS::service() {
    uint8_t data[8];
	
    if (0 < m_ioservice->read(data, 8)) {
	if (!m_channel->send(data, 8)) {
	    spdlog::warn("{} service send failed", m_channel->getName());
	}
    }
    else {
	spdlog::warn("{} io service read failed", m_ioservice->getName());
    }

    return;
}
