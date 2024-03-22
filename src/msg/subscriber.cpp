#include "subscriber.h"

EAR::Subscriber::Subscriber(const std::string &node) : EAR::Messenger(node) {

}

EAR::Subscriber::~Subscriber() {

}

bool EAR::Subscriber::open() {
    int ec = 0;

    if (0 != (ec = nng_sub0_open(&m_sub))) {
	spdlog::error("could not open [sub {} - {}]", getNode(), nng_strerror(ec));
	close();
    }
    else {
	m_state = MESSENGER_OPENED;
    }
    
    return MESSENGER_OPENED == m_state;
}

void EAR::Subscriber::close() {
    // we do not care return value of close function
    nng_close(m_sub);    
    m_state = MESSENGER_CLOSED;

    return;
}

bool EAR::Subscriber::subscribe(const Messenger *pub, const int32_t timeout) {
    int ec = 0;
    std::string pub_node = std::string(NODE_DIR) + pub->getNode();
        
    if (MESSENGER_CLOSED == m_state) {
	spdlog::error("could not subscribe, sub {} not opened yet", getNode());
    }
    else if (0 != (ec = nng_socket_set(m_sub, NNG_OPT_SUB_SUBSCRIBE, "", 0))) {
	spdlog::error("could not set socket subscription [sub {} - {}]", getNode(), nng_strerror(ec));
    }
    else if (0 != (ec = nng_socket_set_ms(m_sub, NNG_OPT_RECVTIMEO, timeout))) {
	spdlog::error("could not set receive timeout [sub {} - {}]", getNode(), nng_strerror(ec));
    }
    else if (0 != (ec = nng_dial(m_sub, pub_node.c_str(), NULL, 0))) {
	spdlog::error("could not dial [sub {} - {}]", getNode(), nng_strerror(ec));
    }
    else {
	m_state = MESSENGER_SUBSCRIBED;
    }

    // if there is an error related to nng, close sockets opened
    if (0 != ec) {
	close();
    }
    
    return MESSENGER_SUBSCRIBED == m_state;
}

bool EAR::Subscriber::receive(void *buf, size_t &size) {
    if (MESSENGER_SUBSCRIBED != m_state) {
	spdlog::error("could not receive data, sub {} not subscribed anywhere", getNode());
	return false;
    }
    
    int ec = nng_recv(m_sub, buf, &size, 0);

    // skip timeout log because socket might be non-blocking
    if (0 != ec && NNG_ETIMEDOUT != ec) {
	spdlog::error("could not receive [sub {} - {}]", getNode(), nng_strerror(ec));
    }
    
    return 0 == ec;
}
