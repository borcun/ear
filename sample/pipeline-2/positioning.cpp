#include "positioning.h"

Positioning::Positioning(const std::string &name) : FACE::PCSS::PortableComponentService(name) {
}

Positioning::~Positioning() {
}

void Positioning::process() {
    uint8_t data[8];
    size_t size = 8;

    if (!receive(data, size)) {
	spdlog::warn("service received failed");
    }
    else {
	Position pos;
	
	memcpy(&pos, data, size);
	spdlog::info("{}: {}, {}", getName(), pos.lon, pos.lat);
    }
}
