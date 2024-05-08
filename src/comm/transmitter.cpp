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

    memset(&m_recv_addr, 0, sizeof(m_recv_addr));

    if (config.ip.empty()) {
	m_recv_addr.sin_addr.s_addr = INADDR_ANY;
    }
    else {
	if (!isValidAddress(config.ip)) {
	    spdlog::error("invalid IP format for {}", getName());
	    return false;
	}

	m_recv_addr.sin_addr.s_addr = inet_addr(config.ip.c_str());
    }

    if (0 == config.port) {
	spdlog::error("invalid port number for {}", getName());
	return false;
    }

    m_recv_addr.sin_port = htons(config.port);
    m_recv_addr.sin_family = AF_INET;

    if (0 > (m_sock = socket(AF_INET, SOCK_DGRAM, 0))) {
	spdlog::error("could not create socket {}", getName());
	return false;
    }

    m_state = COMM_OPENED;
    
    spdlog::debug("{} transmitter existed with config: IP: {}, port: {}, is blocked: {}, timeout: {}",
		  getName(), config.ip, config.port, config.is_blocked, config.timeout);

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
