#include "dcu.h"
#include "position.h"

DCU::DCU(const std::string &name)
  : EAR::Schedule::Task(name)
{
}

DCU::~DCU() {
}

void DCU::setReceiver(EAR::Communication::Receiver *receiver) {
  m_receiver = receiver;
  return;
}

bool DCU::initialize(void) {
  spdlog::info("DCU task {} initialized", getName());
  return true;
}

void DCU::cycle(void) {
  Position pos;
  size_t size = 8;

  if (nullptr != m_receiver) {
    while (0 < m_receiver->receive(&pos, size)) {
      spdlog::info("DCU get data, lon {}, lat {}", pos.lon, pos.lat);
    }
  }
    
  return;
}
