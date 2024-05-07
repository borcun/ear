/**
 * @file receiver.h
 * @brief class that provides receiving infrastructure for message transfer
 * @author boo
 */

#pragma once

#include <arpa/inet.h>
#include "endpoint.h"

namespace EAR {
    namespace Communication {
	/// class Receiver
	class Receiver : public Endpoint {
	public:
	    explicit Receiver(const std::string &name);
	    virtual ~Receiver();
	    virtual bool initialize(const Configuration &config) override;
	    virtual void shutdown() override;
	    
	    /// function that receives buffer from the publisher
	    /// @param [in] buf - buffer
	    /// @param [in|out] size - buffer size
	    /// @return size of data received if succeed, otherwise errno
	    int32_t receive(void *buf, size_t &size);

	private:
	    /// socket
	    int m_sock = -1;
	    /// client address 
	    struct sockaddr_in m_client_addr;
	    /// size of client address
	    socklen_t m_client_addr_len;
	};
    }
}
