#include "publisher.h"

EAR::Publisher::Publisher(const std::string &node) : EAR::Messenger(node) { }

EAR::Publisher::~Publisher() { }

bool EAR::Publisher::open() {
    int ec = 0;
    std::string pub_node = std::string(NODE_DIR) + getNode();
    
    if (MESSENGER_CLOSED != m_state) {
	spdlog::error("could not open, publisher {} already opened", getNode());
    }    
    else if (0 != (ec = nng_pub0_open(&m_pub))) {
	spdlog::error("could not open [pub {} - {}]", getNode(), nng_strerror(ec));
    }
    else if ((ec = nng_listen(m_pub, pub_node.c_str(), NULL, 0)) < 0) {
	spdlog::error("could not listen [pub {} - {}]", getNode(), nng_strerror(ec));
    }
    else {
	m_state = MESSENGER_OPENED;
    }

    // if there is an error related to nng, close socket opened
    if (0 != ec) {
	close();
    }
    
    return MESSENGER_OPENED == m_state;
}

void EAR::Publisher::close() {
    // do not care return value of close function
    nng_close(m_pub);
    m_state = MESSENGER_CLOSED;

    return;
}

bool EAR::Publisher::send(void *buf, size_t size) {
    if (MESSENGER_CLOSED == m_state) {
	spdlog::error("could not send, pub {} already closed", getNode());
	return false;
    }
    
    int ec = nng_send(m_pub, buf, size, 0);

    if (0 != ec) {
	spdlog::error("could not send [pub {} - {}]", getNode(), nng_strerror(ec));
    }
    
    return 0 == ec;
}
