#include "gps.h"

GPS::GPS(const std::string &name) : FACE::PeriodicService(name), FACE::Node(name) {
    for (int i = 0; !open(); ++i) {
	spdlog::error("could not open socket {}", name);
    }
}

GPS::~GPS() {
    close();
}

void GPS::setIOService(FACE::IOSS::IOService *ios) {
    m_ios = ios;
}

void GPS::process() {
    uint8_t data[8];
	
    if (0 < m_ios->read(data, 8)) {
	if (!send(data, 8)) {
	    spdlog::warn("gps service send failed");
	}
	else {
	    spdlog::info("{} service send", getName());
	}
    }
    else {
	spdlog::warn("gps io service read failed");
    }

    return;
}
