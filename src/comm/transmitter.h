/**
 * @file transmitter.h
 * @brief class that provides transmitting infrastructure for message transfer
 * @author boo
 */

#pragma once

#include <arpa/inet.h>
#include "endpoint.h"

namespace EAR {
    namespace Communication {
	class Transmitter : public Endpoint {	    
	public:
	    explicit Transmitter(const std::string &name);
	    virtual ~Transmitter();
	    virtual bool initialize(const Configuration &config) override;
	    virtual void shutdown() override;

	    /// function that send buffer to listener
	    /// @param [in] buf - buffer
	    /// @return length of data sent if succeed, otherwise errno
	    int32_t send(const std::string &buf);
	    
	    /// function that send buffer to listener
	    /// @param [in] buf - buffer
	    /// @param [in] size - buffer size
	    /// @return length of data sent if succeed, otherwise errno
	    int32_t send(const void *buf, size_t size);

	private:
	    /// socket
	    int m_sock = -1;
	    /// receiver address
	    struct sockaddr_in m_recv_addr;
	};
    }
}
