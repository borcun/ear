/**
 * @file transmitter.h
 * @brief class that provides transmitting infrastructure for message transfer
 * @author boo
 */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "endpoint.h"

namespace EAR {
    namespace Communication {
	class Transmitter : public Endpoint {	    
	public:
	    /// default constructor
	    Transmitter();
	    /// destructor
	    virtual ~Transmitter();
	    /// function that send buffer to subscribers
	    /// @param [in] buf - buffer
	    /// @param [in] size - buffer size
	    /// @return true if buffer is sent to subscribers, otherwise false
	    bool send(void *buf, size_t &size);

	    virtual bool initialize(const Configuration &config) override;
	    virtual void shutdown() override;

	private:
	    /// socket
	    int m_sock = -1;
	    /// receiver address
	    struct sockaddr_in m_recv_addr;
	};
    }
}
