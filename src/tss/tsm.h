#ifndef TRANSPORT_SERVICE_MESSAGE_H
#define TRANSPORT_SERVICE_MESSAGE_H

#include "service_util.h"

namespace FACE {
    namespace TSS {
	class TSMessage {
	public:
	    TSMessage();
	    TSMessage(const uint8_t *data, const uint32_t size);
	    virtual ~TSMessage();
	    void setData(const uint8_t *data, const uint32_t size);
	    const uint8_t *getData() const;
	    uint32_t getSize() const;
	    
	private:
	    uint8_t m_data[TS_MAX_DATA_SIZE];
	    uint32_t m_size = 0;
	};
    }
}

#endif
