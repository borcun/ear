/**
 * @file listener.h
 * @brief class that provides receiving/listening infrastructure for message transfer
 * @author boo
 */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "endpoint.h"

namespace EAR {
    namespace Communication {
	/// class Listener
	class Listener : public Endpoint {
	public:
	    /// constructor
	    /// @param [in] name - endpoint name
	    explicit Listener(const std::string &name);
	    /// destructor
	    virtual ~Listener();
	    /// function that receives buffer from the publisher
	    /// @param [in] buf - buffer
	    /// @param [in|out] size - buffer size
	    /// @return size of data received if succeed, otherwise errno
	    int32_t receive(void *buf, size_t &size);

	    virtual bool initialize(const Configuration &config) override;
	    virtual void shutdown() override;

	private:
	    /// socket
	    int m_sock = -1;
	};
    }
}
