#include "network_manager.h"

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

    config.port = 10000;
    m_server = new Listener(getName() + "-server");

    if (!m_server->initialize(config)) {
	delete m_server;
	return false;
    }

    return true;
}

EAR::Communication::Listener *EAR::Communication::NetworkManager::getServer() {
    return m_server;
}

EAR::Communication::Transmitter *EAR::Communication::NetworkManager::getClient() {
    Configuration config;
    Transmitter *client = new Transmitter(getName() + "-client-" + std::to_string(m_clients.size() + 1));

    config.port = 10000;

    if (!client->initialize(config)) {
	delete client;
	return nullptr;
    }

    m_clients.push_back(client);
    return client;
}

void EAR::Communication::NetworkManager::terminate() {
    if (m_is_init) {
	m_server->shutdown();

	for (auto &client : m_clients) {
	    client->shutdown();
	    delete client;
	    client = nullptr;
	}

	delete m_server;
	m_server = nullptr;
	m_is_init = false;
    }

    return;
}
