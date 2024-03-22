/**
 * @file messenger.h
 * @brief class that provides communication infrastructure
 * @author boo
 */

#ifndef MESSENGER_H
#define MESSENGER_H

#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include "core_util.h"

namespace EAR {
    /// messenger state
    enum MessengerState {
	MESSENGER_CLOSED,
	MESSENGER_OPENED,
	MESSENGER_SUBSCRIBED
    };
	
    class Messenger {	    
    public:
	/// constructor
	Messenger(const std::string &node);
	/// destructor
	virtual ~Messenger();
	/// function that gets messenger node name
	/// @return messenger node name
	const std::string &getNode() const;
	/// function that opens messenger
	/// @param [in] node - node name
	/// @return true if messenger is opened, otherwise false
	bool open(const std::string &node);
	/// function that closes messenger already opened
	void close();
	/// function that subscribes the messenger to source messenger
	/// @param [in] source - source messenger
	/// @param [in] timeout - timeout for receiving
	/// @return true if the messenger is subscribed, otherwise false
	bool subscribe(const Messenger *source, const int32_t timeout);
	/// function that send buffer to subscribers
	/// @param [in] buf - buffer
	/// @param [in] size - buffer size
	/// @return true if buffer is sent to subscribers, otherwise false
	bool send(void *buf, size_t size);
	/// function that receives buffer from publisher
	/// @param [in] buf - buffer
	/// @param [in|out] size - buffer size
	/// @return true if buffer is received from publisher, otherwise false
	bool receive(void *buf, size_t &size);

    private:
	/// messenger name
	std::string m_node;
	/// messenger state
	MessengerState m_state = MESSENGER_CLOSED;
	/// publisher socket
	nng_socket m_pub = NNG_SOCKET_INITIALIZER;
	/// subscriber socket
	nng_socket m_sub = NNG_SOCKET_INITIALIZER;
    };
}

#endif
