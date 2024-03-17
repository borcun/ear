#include "node.h"

FACE::Node::Node(const std::string &url) : m_url(url) {

}

FACE::Node::~Node() {

}
const std::string &FACE::Node::getURL() const {
    return m_url;
}

bool FACE::Node::open() {
    int ec = 0;
    std::string pub_url = std::string("ipc:///tmp/") + m_url;
    
    if (NODE_CLOSED != m_state) {
	spdlog::error("could not open node for {}", m_url);
    }    
    else if (0 != (ec = nng_pub0_open(&m_pub)) || 0 != (ec = nng_sub0_open(&m_sub))) {
	spdlog::error("could not open node for {} [{}]", m_url, ec);
    }
    else if ((ec = nng_listen(m_pub, pub_url.c_str(), NULL, 0)) < 0) {
	spdlog::error("could not listen for {} [{}]", m_url, ec);
    }
    else {
	m_state = NODE_OPENED;
    }

    // if there is an error related to nng, close sockets opened
    if (0 != ec) {
	close();
    }
    
    return NODE_OPENED == m_state;
}

void FACE::Node::close() {
    // we do not care return values of close functions
    nng_close(m_pub);
    nng_close(m_sub);
    
    m_state = NODE_CLOSED;

    return;
}

bool FACE::Node::subscribe(const Node *source, const int32_t timeout) {
    int ec = 0;
    std::string sub_url = std::string("ipc:///tmp/") + source->getURL();
        
    if (NODE_OPENED != m_state && NODE_SUBSCRIBED != m_state) {
	spdlog::error("could not subscribe socket not opened yet");
    }
    else if (0 != (ec = nng_socket_set(m_sub, NNG_OPT_SUB_SUBSCRIBE, "", 0))) {
	spdlog::error("could not set subscribe option for {} [{}]", m_url, ec);
    }
    else if (0 != (ec = nng_socket_set_ms(m_sub, NNG_OPT_RECVTIMEO, timeout))) {
	spdlog::error("could not set recv timeout option for {} [{}]", m_url, ec);
    }
    else if (0 != (ec = nng_dial(m_sub, sub_url.c_str(), NULL, 0))) {
	spdlog::error("could not dial subscriber for {} [{}]", m_url, ec);
    }
    else {
	m_state = NODE_SUBSCRIBED;
    }

    // if there is an error related to nng, close sockets opened
    if (0 != ec) {
	close();
    }
    
    return NODE_SUBSCRIBED == m_state;
}

bool FACE::Node::send(void *buf, size_t size) {
    if (NODE_CLOSED == m_state) {
	spdlog::error("could not send by node closed");
	return false;
    }
    
    int ec = nng_send(m_pub, buf, size, 0);

    if (0 != ec) {
	spdlog::error("could not send node {} [{}]", m_url, ec);
    }
    
    return 0 == ec;
}

bool FACE::Node::receive(void *buf, size_t &size) {
    if (NODE_SUBSCRIBED != m_state) {
	spdlog::error("could not receive data by node not subscribed");
	return false;
    }
    
    int ec = nng_recv(m_sub, buf, &size, 0);

    // skip timeout log because socket might be non-blocking
    if (0 != ec && NNG_ETIMEDOUT != ec) {
	spdlog::error("could not receive node {} [{}]", m_url, ec);
    }
    
    return 0 == ec;
}
