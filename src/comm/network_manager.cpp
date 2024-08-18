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

std::string EAR::Communication::NetworkManager::getName(void) const {
  return m_name;
}

bool EAR::Communication::NetworkManager::initialize(const EAR::Communication::Configuration &config) {
  if (m_is_init) {
    spdlog::error("could not initialize network manager {}, already initialized", getName());
    return false;
  }

  m_config = config;
  m_receiver = new Receiver(getName() + "-receiver");

  if (!m_receiver->initialize(m_config)) {
    delete m_receiver;
    return false;
  }

  m_is_init = true;
  return true;
}

void EAR::Communication::NetworkManager::terminate(void) {
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

EAR::Communication::Receiver *EAR::Communication::NetworkManager::getReceiver(void) {
  return m_receiver;
}

EAR::Communication::Transmitter *EAR::Communication::NetworkManager::getTransmitter(void) {
  Transmitter *transmitter = new Transmitter(getName() + "-transmitter-" + std::to_string(m_transmitters.size() + 1));

  if (!transmitter->initialize(m_config)) {
    spdlog::error("could not initialize transmitter for {}", getName());
    delete transmitter;
    transmitter = nullptr;
    
    return nullptr;
  }

  m_transmitters.push_back(transmitter);
  return transmitter;
}
