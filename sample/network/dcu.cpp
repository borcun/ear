#include "dcu.h"
#include "position.h"

DCU::DCU() : EAR::Schedule::PeriodicTask() { }

DCU::~DCU() { }

void DCU::setServer(EAR::Communication::Listener *server) {
    m_server = server;
}

void DCU::process() {
    Position pos;
    size_t size = 8;

    if (nullptr != m_server) {
	while (m_server->receive(&pos, size)) {
	    spdlog::info("DCU get data, lon {}, lat {}", pos.lon, pos.lat);
	}
    }

    spdlog::info("DCU process called");
    
    return;
}
