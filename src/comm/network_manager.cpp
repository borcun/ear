#include "network_manager.h"

#define NET_BASE_ADDR  (10000U)
#define NET_RANGE_SIZE (100U)

static int32_t range_index = 0;

EAR::Communication::NetworkManager::NetworkManager(const std::string &name)
    : m_name(name)
{
    spdlog::debug("network manager {} created", name);
}

EAR::Communication::NetworkManager::~NetworkManager() {
    terminate();
    spdlog::debug("network manager {} terminated", getName());
}

std::string EAR::Communication::NetworkManager::getName() const {
    return m_name;
}

bool EAR::Communication::NetworkManager::initialize() {
    if (m_is_init) {
	spdlog::error("could not initialize network manager {}, already initialized", getName());
	return false;
    }

    Configuration config;

    /// @todo get configuration via parameter
    config.ip = "";
    config.port = NET_BASE_ADDR + (range_index * NET_RANGE_SIZE);
    config.is_blocked = false;
    config.timeout = 0U;

    m_receiver = new Receiver(getName() + "-receiver");

    if (!m_receiver->initialize(config)) {
	delete m_receiver;
	return false;
    }

    range_index++;
    return true;
}

EAR::Communication::Receiver *EAR::Communication::NetworkManager::getReceiver() {
    return m_receiver;
}

EAR::Communication::Transmitter *EAR::Communication::NetworkManager::getTransmitter() {
    Configuration config;
    Transmitter *transmitter = new Transmitter(getName() + "-transmitter-" + std::to_string(m_transmitters.size() + 1));

    config.port = 10000; /// @todo solve port problem

    if (!transmitter->initialize(config)) {
	spdlog::error("could not initialize transmitter for {}", getName());
	delete transmitter;
	return nullptr;
    }

    m_transmitters.push_back(transmitter);
    return transmitter;
}

void EAR::Communication::NetworkManager::terminate() {
    if (m_is_init) {
	m_receiver->shutdown();

	for (auto &transmitter : m_transmitters) {
	    transmitter->shutdown();
	    delete transmitter;
	    transmitter = nullptr;
	}

	delete m_receiver;
	m_receiver = nullptr;
	m_is_init = false;
    }

    return;
}
