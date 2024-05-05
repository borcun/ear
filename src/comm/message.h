#pragma once

#include <cstdint>

namespace EAR {
    namespace Communication {
	struct Message {
	    uint8_t src;
	    uint8_t len;
	    uint8_t *buf;
	    uint16_t crc;
	};
    }
}
