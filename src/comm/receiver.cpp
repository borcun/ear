#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "receiver.h"

EAR::Communication::Receiver::Receiver(const std::string &name)
    : EAR::Communication::Endpoint(name)
{
    m_client_addr_len = sizeof(m_client_addr);
    spdlog::debug("receiver {} created", name);
}

EAR::Communication::Receiver::~Receiver() {
    spdlog::debug("receiver {} terminated", getName());
}

bool EAR::Communication::Receiver::initialize(const Configuration &config) {
    if (COMM_OPENED == m_state) {
	spdlog::error("socket for receiver {} already opened", getName());
	return false;
    }
    
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    if (config.ip.empty()) {
	server_addr.sin_addr.s_addr = INADDR_ANY;
    }
    else {
	if (!isValidAddress(config.ip)) {
	    spdlog::error("invalid IP format for {}", getName());
	    return false;
	}

	server_addr.sin_addr.s_addr = inet_addr(config.ip.c_str());
    }

    if (0 == config.port) {
	spdlog::error("invalid port number for {}", getName());
	return false;
    }

    server_addr.sin_port = htons(config.port);
    server_addr.sin_family = AF_INET;
    
    if (0 > (m_sock = socket(AF_INET, SOCK_DGRAM, 0))) {
	spdlog::error("could not create socket {}", getName());
	return false;
    }
    
    if (0 > bind(m_sock, (const struct sockaddr *) &server_addr, sizeof(server_addr))) {
	spdlog::error("could not bind socket for receiver {}", getName());
	return false;
    }

    if (config.is_blocked && 0 != config.timeout) {
	struct timeval recv_timeout = {config.timeout / 1000, config.timeout * 1000};

	if (0 != setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout))) {
	    spdlog::error("could not set timeout option of socket {}", getName());
	    shutdown();

	    return false;
	}
    }
    else {
    	if(fcntl(m_sock, F_SETFL, fcntl(m_sock, F_GETFL) | O_NONBLOCK) < 0) {
	    spdlog::error("could not set non-blocking option of socket {}", getName());
	    shutdown();
	    
	    return false;
	}
    }
    
    m_state = COMM_OPENED;
    spdlog::debug("{} receiver existed with config: IP: {}, Port: {}, Block: {}, Timeout: {}",
		  getName(), config.ip, config.port, config.is_blocked, config.timeout);
    
    return true;
}

void EAR::Communication::Receiver::shutdown() {
    ::shutdown(m_sock, SHUT_RD);
    m_state = COMM_CLOSED;

    return;
}

int32_t EAR::Communication::Receiver::receive(void *buf, size_t &size) {
    if (COMM_OPENED != m_state) {
	spdlog::error("could not receive data, connection closed {}", getName());
	return ENOENT;
    }

    return recvfrom(m_sock, buf, size, 0,
		    (struct sockaddr *) &m_client_addr,
		    &m_client_addr_len);
}
