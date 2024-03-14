#include "edge_service.h"

FACE::TSS::EdgeService::EdgeService(const std::string &name) : Service(name) {
    m_gateway = new Gateway(name);
    m_gateway->open();
}

FACE::TSS::EdgeService::~EdgeService() {
    m_gateway->close();
    m_gateway = nullptr;
}

bool FACE::TSS::EdgeService::connect(const EdgeService *service) {
    return m_gateway->subscribe(service->m_gateway);
}

bool FACE::TSS::EdgeService::send(void *buf, size_t size) {
    if (nullptr == m_gateway) {
	return false;
    }

    return m_gateway->transmit(buf, size);
}

bool FACE::TSS::EdgeService::receive(void *buf, size_t &size) {
    if (nullptr == m_gateway) {
	return false;
    }

    return m_gateway->receive(buf, size);
}
