#pragma once

#include <cstdint>

namespace EAR {
    namespace Communication {
	struct Message {
	    uint32_t src;
	    uint32_t len;
	    uint8_t *buf;
	    uint16_t crc;
	};
    }
}
