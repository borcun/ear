#include "gateway.h"

FACE::TSS::Gateway::Gateway(const std::string &name) : m_name(name) {

}

FACE::TSS::Gateway::~Gateway() {

}

std::string FACE::TSS::Gateway::getName() const {
    return m_name;
}

bool FACE::TSS::Gateway::open() {
    int ec = 0;
    std::string pub_url = std::string("ipc:///tmp/") + m_name;
    
    if (GATEWAY_CLOSED != m_state) {
	spdlog::error("could not open gateway for {}", m_name);
    }    
    else if (0 != (ec = nng_pub0_open(&m_pub)) || 0 != (ec = nng_sub0_open(&m_sub))) {
	spdlog::error("could not open gateway for {} [{}]", m_name, ec);
    }
    else if ((ec = nng_listen(m_pub, pub_url.c_str(), NULL, 0)) < 0) {
	spdlog::error("could not listen for {} [{}]", m_name, ec);
    }
    else {
	m_state = GATEWAY_OPENED;
    }

    // if there is an error related to nng, close sockets opened
    if (0 != ec) {
	close();
    }
    
    return GATEWAY_OPENED == m_state;
}

void FACE::TSS::Gateway::close() {
    // we do not care return values of close functions
    nng_close(m_pub);
    nng_close(m_sub);
    
    m_state = GATEWAY_CLOSED;

    return;
}

bool FACE::TSS::Gateway::subscribe(const Gateway *source) {
    int ec = 0;
    std::string sub_url = std::string("ipc:///tmp/") + source->getName();
        
    if (GATEWAY_OPENED != m_state) {
	spdlog::error("could not subscribe socket not opened to the source");
    }
    else if (0 != (ec = nng_socket_set(m_sub, NNG_OPT_SUB_SUBSCRIBE, "", 0))) {
	spdlog::error("could not set subscribe option for {} [{}]", m_name, ec);
    }
    else if (0 != (ec = nng_dial(m_sub, sub_url.c_str(), NULL, 0))) {
	spdlog::error("could not dial subscriber for {} [{}]", m_name, ec);
    }
    else {
	m_state = GATEWAY_SUBSCRIBED;
    }

    // if there is an error related to nng, close sockets opened
    if (0 != ec) {
	close();
    }
    
    return GATEWAY_SUBSCRIBED == m_state;
}

bool FACE::TSS::Gateway::transmit(void *buf, size_t size) {
    if (GATEWAY_CLOSED == m_state) {
	return false;
    }
    
    int ec = nng_send(m_pub, buf, size, 0);

    if (0 != ec) {
	spdlog::error("could not write gateway {} [{}]", m_name, ec);
    }
    
    return 0 == ec;
}

bool FACE::TSS::Gateway::receive(void *buf, size_t &size) {
    if (GATEWAY_SUBSCRIBED != m_state) {
	return false;
    }
    
    int ec = nng_recv(m_sub, buf, &size, 0);

    if (0 != ec) {
	spdlog::error("could not read gateway {} [{}]", m_name, ec);
    }
    
    return 0 == ec;
}
