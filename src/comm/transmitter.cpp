#include <cstdlib>
#include <string>
#include <unistd.h>
#include "transmitter.h"

EAR::Communication::Transmitter::Transmitter(const std::string &name)
    : Endpoint(name)
{
    spdlog::debug("transmitter {} created", name);
}

EAR::Communication::Transmitter::~Transmitter() {
    spdlog::debug("transmitter {} terminated", getName());
}

bool EAR::Communication::Transmitter::initialize(const Configuration &config) {
    if (COMM_OPENED == m_state) {
	spdlog::error("socket for transmitter {} already opened", getName());
	return false;
    }

    /// @todo check IP and port validities
    
    if (0 > (m_sock = socket(AF_INET, SOCK_DGRAM, 0))) {
	spdlog::error("could not create socket {}", getName());
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

    m_state = COMM_OPENED;
    return true;
}

void EAR::Communication::Transmitter::shutdown() {
    close(m_sock);    
    m_state = COMM_CLOSED;
    
    spdlog::debug("transmitter {} shutdown", getName());

    return;
}

int32_t EAR::Communication::Transmitter::send(const char *buf) {
    return send(buf, strlen(buf));
}

int32_t EAR::Communication::Transmitter::send(const void *buf, size_t size) {
    if (COMM_OPENED != m_state) {
	spdlog::error("could not send data, connection closed {}", getName());
	return ENOENT;
    }

    return sendto(m_sock, buf, size, 0,
		  (struct sockaddr *) &m_recv_addr,
		  sizeof(m_recv_addr));
}
