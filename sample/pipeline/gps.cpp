#include "gps.h"

GPS::GPS() : EAR::PeriodicTask() {
}

GPS::~GPS() {
}

void GPS::setIODevice(EAR::IODevice *iodev) {
    m_iodev = iodev;
}

void GPS::process() {
    uint8_t data[8];
	
    if (0 < m_iodev->read(data, 8)) {
	spdlog::info("gps task {} read", m_id);
    }
    else {
	spdlog::warn("gps task {} read failed", m_id);
    }

    return;
}
