#include "dcu.h"
#include "position.h"

DCU::DCU(const std::string &name) : EAR::Schedule::Task(name) {
}

DCU::~DCU() {
    if (nullptr != m_receiver) {
	m_receiver->shutdown();
    }
}

void DCU::setReceiver(EAR::Communication::Receiver *receiver) {
    m_receiver = receiver;
    return;
}

bool DCU::initialize() {
    spdlog::info("DCU task {} initialized", getName());
    return true;
}

void DCU::cycle() {
    Position pos;
    size_t size = 8;

    if (nullptr != m_receiver) {
	while (0 < m_receiver->receive(&pos, size)) {
	    spdlog::info("DCU get data, lon {}, lat {}", pos.lon, pos.lat);
	}
    }
    
    return;
}
