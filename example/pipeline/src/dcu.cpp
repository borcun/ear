#include "dcu.h"
#include "position.h"

DCU::DCU(const std::string &name) :
  EAR::Schedule::Task(name)
{
}

DCU::~DCU() {
}

bool DCU::initialize(void) {
  spdlog::info("DCU task {} initialized", getName());
  return true;
}

void DCU::cycle(void) {
  /*
    Position pos;
    size_t size = 8;
    
    while (receive(&pos, size)) {
    spdlog::info("DCU get data, lon {}, lat {}", pos.lon, pos.lat);
    }
  */

  spdlog::info("DCU process called");
    
  return;
}
