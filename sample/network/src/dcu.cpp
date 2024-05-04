#include "dcu.h"
#include "position.h"

DCU::DCU(const std::string &name) : EAR::Schedule::Task(name) {
}

DCU::~DCU() {
    if (nullptr != m_server) {
	m_server->shutdown();
    }
}

void DCU::setServer(EAR::Communication::Listener *server) {
    m_server = server;
    return;
}

bool DCU::initialize() {
    spdlog::info("DCU task {} initialized", getName());
    return true;
}

void DCU::cycle() {
    Position pos;
    size_t size = 8;

    if (nullptr != m_server) {
	while (0 < m_server->receive(&pos, size)) {
	    spdlog::info("DCU get data, lon {}, lat {}", pos.lon, pos.lat);
	}
    }
    
    return;
}
