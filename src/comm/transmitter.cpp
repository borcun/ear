#include "transmitter.h"

EAR::Communication::Transmitter::Transmitter() : Endpoint() { }

EAR::Communication::Transmitter::~Transmitter() { }

bool EAR::Communication::Transmitter::initialize(const Configuration &config) {
    if (COMM_OPENED == m_state) {
	spdlog::error("socket already opened");
	return false;
    }

    /// @todo check IP and port validities
    
    if (0 > (m_sock = socket(AF_INET, SOCK_DGRAM, 0))) {
	spdlog::error("could not create socket");
	return false;
    }

    memset(&m_recv_addr, 0, sizeof(m_recv_addr));
    m_recv_addr.sin_family = AF_INET;
    m_recv_addr.sin_port = htons(config.port);
    
    if (config.ip.empty()) {
	m_recv_addr.sin_addr.s_addr = INADDR_ANY;
    }
    else {
	//inet_aton(config.ip.c_str(), &m_recv_addr.sin_addr.s_addr);
    }

    return true;
}

void EAR::Communication::Transmitter::shutdown() {
    close(m_sock);    
    m_state = COMM_CLOSED;

    return;
}

bool EAR::Communication::Transmitter::send(void *buf, size_t &size) {
    if (COMM_CLOSED != m_state) {
	spdlog::error("could not send data, connection closed");
	return false;
    }

    return 0 < sendto(m_sock, buf, size, 0, (const struct sockaddr *) &m_recv_addr, sizeof(m_recv_addr));
}
