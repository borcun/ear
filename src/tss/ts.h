/**
 * @file ts.h
 * @brief
 * @author boo
 */

#ifndef TRANSPORT_SERVICE_H
#define TRANSPORT_SERVICE_H

#include "service.h"
#include "tsm.h"
#include <mutex>
#include <queue>

namespace FACE {
    namespace TSS {
	class TransportService : public Service {
	public:
	    explicit TransportService(const std::string &name);
	    virtual ~TransportService();
	    bool send(const TSMessage &message);
	    bool receive(TSMessage &message);
	    
	private:
	    std::mutex m_mutex;
	    std::queue<TSMessage> m_queue;
	};
    }
}

#endif
