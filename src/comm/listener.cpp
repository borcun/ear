#include "listener.h"

EAR::Communication::Listener::Listener(const std::string &name)
    : Endpoint(name)
{
    spdlog::debug("{} listener created", name);
}

EAR::Communication::Listener::~Listener() {
    spdlog::debug("{} listener terminated", getName());
}

bool EAR::Communication::Listener::initialize(const Configuration &config) {
    if (COMM_OPENED == m_state) {
	spdlog::error("{} socket already opened", getName());
	return false;
    }
    
    /// @todo check IP validity, is it v4?
    if (config.ip.empty() || config.ip.length() < 7) {
	spdlog::error("invalid IP format for {}", getName());
	return false;
    }

    if (0 == config.port) {
	spdlog::error("invalid port number for {}", getName());
	return false;
    }

    if (0 > (m_sock = socket(AF_INET, SOCK_DGRAM, 0))) {
	spdlog::error("could not create socket {}", getName());
	return false;
    }

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config.port);
    
    if (config.ip.empty()) {
	server_addr.sin_addr.s_addr = INADDR_ANY;
    }
    else {
	// inet_aton(config.ip.c_str(), &server_addr.sin_addr.s_addr);
    }

    if (0 > bind(m_sock, (const struct sockaddr *) &server_addr, sizeof(server_addr))) {
	spdlog::error("could not bind socket {}", getName());
	return false;
    }

    // non-blocking is upper mode of timeout, if it is set, no need timeout
    if (!config.is_blocked) {
	if(fcntl(m_sock, F_SETFL, fcntl(m_sock, F_GETFL) | O_NONBLOCK) < 0) {
	    spdlog::error("could not set non-blocking option of socket {}", getName());
	    shutdown();
	    
	    return false;
	}
    }
    else if (0 != config.timeout) {
	struct timeval read_timeout;
    
	read_timeout.tv_sec = config.timeout / 1000;
	read_timeout.tv_usec = config.timeout * 1000;
	setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
    }
    else {
	// blocking mode, do nothing
    }
    
    m_state = COMM_OPENED;
    return true;
}

void EAR::Communication::Listener::shutdown() {
    ::shutdown(m_sock, SHUT_RD);
    m_state = COMM_CLOSED;

    return;
}

int32_t EAR::Communication::Listener::receive(void *buf, size_t &size) {
    if (COMM_OPENED != m_state) {
	spdlog::error("could not receive data, connection closed {}", getName());
	return ENOENT;
    }

    /// @todo debug purpose?
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    return recvfrom(m_sock, buf, size, 0,
		    (struct sockaddr *) &client_addr, &len);
}
