#include "bit.h"

BIT::BIT(FACE::PCSS::PortableComponentService *pcs) : FACE::APeriodicTask()
{
    m_pcs = pcs;
}

BIT::~BIT() {
    if (nullptr != m_pcs) {
	delete m_pcs;
    }
}

void BIT::addHelperService(FACE::PSSS::PlatformService *dev) {
    m_aper_sched.add(dev);
}

bool BIT::init() {
    return m_aper_sched.start();
}

void BIT::process() {
    uint8_t data[16];
    size_t size = 16;
    
    m_aper_sched.restart();

    if (!m_pcs->receive(data, size)) {
	spdlog::error("could not receive data");
    }
    else {
	spdlog::error("data received");
    }
}
