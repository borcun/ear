#include "gps.h"

GPS::GPS(const std::string &name)
    : FACE::PSSS::PlatformService(name),
      FACE::APeriodicTask()
{

}

GPS::~GPS() {
}

void GPS::process() {
    uint8_t data[8];
	
    if (0 < m_ioservice->read(data, 8)) {
	if (!send(data, 8)) {
	    spdlog::warn("{} service send failed", getName());
	}
    }
    else {
	spdlog::warn("{} io service read failed", m_ioservice->getName());
    }

    return;
}
