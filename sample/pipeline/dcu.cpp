#include "dcu.h"
#include "position.h"

DCU::DCU(const std::string &name) : EAR::Schedule::Task(name)
{
}

DCU::~DCU()
{
}

bool DCU::initialize() {
    spdlog::info("DCU task {} initialized", getName());
    return true;
}

void DCU::cycle() {
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
