#include "gps.h"

GPS::GPS(const std::string &name) : PlatformService(name) {
}

GPS::~GPS() {
}

void GPS::service() {
    uint8_t data[8];
	
    if (0 < m_ioservice->read(data, 8)) {
	FACE::TSS::TSMessage msg(data, 8);
	
	if (!m_tservice->send(msg)) {
	    spdlog::warn("{} service send failed", m_tservice->getName());
	}
    }
    else {
	spdlog::warn("{} io service read failed", m_ioservice->getName());
    }

    return;
}
