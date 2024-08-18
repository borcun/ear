#include "gps.h"

GPS::GPS(const std::string &name)
  : EAR::Schedule::Task(name)
{
}

GPS::~GPS() {
}

void GPS::setDevice(EAR::IO::Device *dev) {
  m_dev = dev;
  return;
}

void GPS::setTransmitter(EAR::Communication::Transmitter *transmitter) {
  m_transmitter = transmitter;
  return;
}

bool GPS::initialize(void) {
  spdlog::info("GPS task {} initialized", getName());
  return true;
}

void GPS::cycle(void) {
  uint8_t data[8];
	
  if (nullptr != m_dev) {
    if (0 < m_dev->receive(data, 8)) {
      spdlog::info("{} received data from device {}", getName(), m_dev->toString());

      if (nullptr != m_transmitter) {
	size_t size = 8;
		
	if (0 < m_transmitter->send(data, size)) {
	  spdlog::info("send data to DCU [{}]", getName());
	}
	else {
	  spdlog::error("could not send data to DCU [{}]", getName());
	}
      }
    }
    else {
      spdlog::warn("GPS task {} read failed", getId());
    }
  }
    
  return;
}
