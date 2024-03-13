/**
 * @file ts.h
 * @brief
 * @author boo
 */

#ifndef TRANSPORT_SERVICE_H
#define TRANSPORT_SERVICE_H

#include "channel.h"

namespace FACE {
    namespace TSS {
	enum ChannelDirection {
	    CH_NONE,
	    CH_UNIDIRECT,
	    CH_BIDIRECT
	};
	
	class TransportService : public Service {
	public:
	    explicit TransportService(const std::string &name);
	    virtual ~TransportService();
	    Channel *create(const std::string &ch1, const std::string &ch2);
	    void destroy();
	    bool send(void *buf, size_t size);
	    bool receive(void *buf, size_t size);
	    
	private:
	};
    }
}

#endif
