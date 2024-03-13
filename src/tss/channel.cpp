#include "channel.h"

FACE::TSS::Channel::Channel(const std::string &name) : m_name(name) {

}

FACE::TSS::Channel::~Channel() {

}

std::string FACE::TSS::Channel::getName() const {
    return m_name;
}

bool FACE::TSS::Channel::init() {
    int ec = 0;
    
    if (0 != nng_pub0_open(&m_pub) || 0 != nng_sub0_open(&m_sub)) {
	destroy();
	spdlog::error("could not open channel for {}", m_name);
	
	return false;
    }

    std::string pub_url = std::string("ipc:///tmp/") + m_name;

    if ((ec = nng_listen(m_pub, pub_url.c_str(), NULL, 0)) < 0) {
	destroy();
	spdlog::error("could not create publisher for {} [{}]", m_name, ec);
	
	return false;
    }

    m_is_initialized = true;
    return true;
}

void FACE::TSS::Channel::destroy() {
    // we do not care return values of close functions
    nng_close(m_pub);
    nng_close(m_sub);
    
    m_is_initialized = false;
    m_is_connected = false;

    return;
}

bool FACE::TSS::Channel::connect(const Channel &other) {
    std::string sub_url = std::string("ipc:///tmp/") + other.getName();
    int ec = 0;
    
    m_is_connected = false;
    
    if (!m_is_initialized) {
	spdlog::warn("could not connect channel {} not initialized yet", m_name);
    }
    else if (m_is_connected) {
	spdlog::warn("could not connect channel {} already connected", m_name);
    }
    else if (0 != (ec = nng_socket_set(m_sub, NNG_OPT_SUB_SUBSCRIBE, "", 0))) {
	destroy();
	spdlog::error("could not set subscriber option for [{}]", m_name, ec);
    }
    else if (0 != (ec = nng_dial(m_sub, sub_url.c_str(), NULL, 0))) {
	destroy();
	spdlog::error("could not dial subscriber for [{}]", m_name, ec);
    }
    else {
	m_is_connected = true;
    }
    
    return m_is_connected;
}

bool FACE::TSS::Channel::send(void *buf, size_t size) {
    if (!m_is_connected) { return false; }
    
    int ec = nng_send(m_pub, buf, size, 0);

    if (0 != ec) {
	spdlog::error("could not send data for {} [{}]", m_name, ec);
    }
    
    return 0 == ec;
}

bool FACE::TSS::Channel::receive(void *buf, size_t size) {
    if (!m_is_connected) { return false; }
    
    int ec = nng_recv(m_sub, buf, &size, 0);

    if (0 != ec) {
	spdlog::error("could not receive data for {} [{}]", m_name, ec);
    }
    
    return 0 == ec;
}
