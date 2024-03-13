#include "positioning.h"

Positioning::Positioning(const std::string &name) : PlatformService(name) {
}

Positioning::~Positioning() {
}

void Positioning::service() {
    FACE::TSS::TSMessage msg;

    if (!m_tservice->receive(msg)) {
	spdlog::warn("{} service received failed", m_tservice->getName());
    }
    else {
	Position pos;
	
	memcpy(&pos, msg.getData(), msg.getSize());
	spdlog::info("{}: {}, {}", getName(), pos.lon, pos.lat);
    }
}
