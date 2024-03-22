#include "messenger.h"

EAR::Messenger::Messenger(const std::string &node) : m_node(node) {

}

EAR::Messenger::~Messenger() {

}
const std::string &EAR::Messenger::getNode() const {
    return m_node;
}

bool EAR::Messenger::open(const std::string &node) {
    int ec = 0;
    std::string pub_node = std::string("ipc:///tmp/") + node;
    
    if (MESSENGER_CLOSED != m_state) {
	spdlog::error("could not open messenger for {}", node);
    }    
    else if (0 != (ec = nng_pub0_open(&m_pub)) || 0 != (ec = nng_sub0_open(&m_sub))) {
	spdlog::error("could not open messenger for {} [{}]", node, ec);
    }
    else if ((ec = nng_listen(m_pub, pub_node.c_str(), NULL, 0)) < 0) {
	spdlog::error("could not listen for {} [{}]", node, ec);
    }
    else {
	m_state = MESSENGER_OPENED;
    }

    // if there is an error related to nng, close sockets opened
    if (0 != ec) {
	close();
    }
    
    return MESSENGER_OPENED == m_state;
}

void EAR::Messenger::close() {
    // we do not care return values of close functions
    nng_close(m_pub);
    nng_close(m_sub);
    
    m_state = MESSENGER_CLOSED;

    return;
}

bool EAR::Messenger::subscribe(const Messenger *source, const int32_t timeout) {
    int ec = 0;
    std::string sub_node = std::string("ipc:///tmp/") + source->getNode();
        
    if (MESSENGER_OPENED != m_state && MESSENGER_SUBSCRIBED != m_state) {
	spdlog::error("could not subscribe socket not opened yet");
    }
    else if (0 != (ec = nng_socket_set(m_sub, NNG_OPT_SUB_SUBSCRIBE, "", 0))) {
	spdlog::error("could not set subscribe option for {} [{}]", m_node, ec);
    }
    else if (0 != (ec = nng_socket_set_ms(m_sub, NNG_OPT_RECVTIMEO, timeout))) {
	spdlog::error("could not set recv timeout option for {} [{}]", m_node, ec);
    }
    else if (0 != (ec = nng_dial(m_sub, sub_node.c_str(), NULL, 0))) {
	spdlog::error("could not dial subscriber for {} [{}]", m_node, ec);
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

bool EAR::Messenger::send(void *buf, size_t size) {
    if (MESSENGER_CLOSED == m_state) {
	spdlog::error("could not send by messenger closed");
	return false;
    }
    
    int ec = nng_send(m_pub, buf, size, 0);

    if (0 != ec) {
	spdlog::error("could not send messenger {} [{}]", m_node, ec);
    }
    
    return 0 == ec;
}

bool EAR::Messenger::receive(void *buf, size_t &size) {
    if (MESSENGER_SUBSCRIBED != m_state) {
	spdlog::error("could not receive data by messenger not subscribed");
	return false;
    }
    
    int ec = nng_recv(m_sub, buf, &size, 0);

    // skip timeout log because socket might be non-blocking
    if (0 != ec && NNG_ETIMEDOUT != ec) {
	spdlog::error("could not receive messenger {} [{}]", m_node, ec);
    }
    
    return 0 == ec;
}
