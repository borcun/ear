#include "localization.h"

Localization::Localization(const std::string &name)
    : FACE::PeriodicService(name),
      FACE::Node(name)
{
    open();
}

Localization::~Localization() {
    close();
}

void Localization::process() {
    uint8_t data[8];
    size_t size = 8;

    while (receive(data, size)) {
	if (0 != size) {
	    Position pos;
	
	    memcpy(&pos, data, size);
	    spdlog::info("{}: {}, {}", getName(), pos.lon, pos.lat);
	}
	else {
	    spdlog::warn("{} service received failed", getName());
	}
    }

    return;
}
