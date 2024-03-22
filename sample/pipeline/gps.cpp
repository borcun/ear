#include "gps.h"

GPS::GPS(const std::string &node) : EAR::PeriodicTask(), EAR::Publisher(node) {
}

GPS::~GPS() {
}

void GPS::setIODevice(EAR::IODevice *iodev) {
    m_iodev = iodev;
}

void GPS::process() {
    uint8_t data[8];
	
    if (0 < m_iodev->read(data, 8)) {
	if (!send(data, 8)) {
	    spdlog::warn("could not send data to subscriber by gps {}", getNode());
	}
	else {
	    spdlog::info("gps {} sends to subscriber", getNode());
	}
    }
    else {
	spdlog::warn("gps task {} read failed", getId());
    }

    return;
}
