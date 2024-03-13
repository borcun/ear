#include "positioning.h"

Positioning::Positioning(const std::string &name) : PlatformService(name) {
}

Positioning::~Positioning() {
}

void Positioning::service() {
    uint8_t data[8];
    size_t size = 8;

    if (!m_channel->receive(data, size)) {
	spdlog::warn("{} service received failed", m_channel->getName());
    }
    else {
	Position pos;
	
	memcpy(&pos, data, size);
	spdlog::info("{}: {}, {}", getName(), pos.lon, pos.lat);
    }
}
