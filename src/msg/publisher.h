/**
 * @file publisher.h
 * @brief class that provides publisher infrastructure
 * @author boo
 */

#pragma once

#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include "messenger.h"

namespace EAR {	
    class Publisher : public Messenger {	    
    public:
	/// constructor
	/// @param [in] node - publisher node
	Publisher(const std::string &node);
	/// destructor
	virtual ~Publisher();
	/// function that opens publisher
	/// @return true if publisher is opened, otherwise false
	virtual bool open() override;
	/// function that closes publisher already opened
	virtual void close() override;
	/// function that send buffer to subscribers
	/// @param [in] buf - buffer
	/// @param [in] size - buffer size
	/// @return true if buffer is sent to subscribers, otherwise false
	bool send(void *buf, size_t size);

    private:
	/// publisher socket
	nng_socket m_pub = NNG_SOCKET_INITIALIZER;
    };
}
