#include "dcu.h"
#include "position.h"

DCU::DCU() : EAR::Schedule::PeriodicTask() { }

DCU::~DCU() { }

void DCU::process() {
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
