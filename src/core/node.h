/**
 * @file node.h
 * @brief class that provides communication infrastructure
 * @author boo
 */

#ifndef NODE_H
#define NODE_H

#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include "core_util.h"

namespace FACE {
    /// node state
    enum NodeState {
	NODE_CLOSED,
	NODE_OPENED,
	NODE_SUBSCRIBED
    };
	
    class Node {	    
    public:
	/// constructor
	Node(const std::string &url);
	/// destructor
	virtual ~Node();
	/// function that gets node name
	/// @return node name
	const std::string &getURL() const;
	/// function that opens node
	/// @return true if node is opened, otherwise false
	bool open();
	/// function that closes node already opened
	void close();
	/// function that subscribes the node to source node
	/// @param [in] source - source node
	/// @param [in] timeout - timeout for receiving
	/// @return true if the node is subscribed, otherwise false
	bool subscribe(const Node *source, const int32_t timeout);
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
	/// node name
	std::string m_url;
	/// node state
	NodeState m_state = NODE_CLOSED;
	/// publisher socket
	nng_socket m_pub = NNG_SOCKET_INITIALIZER;
	/// subscriber socket
	nng_socket m_sub = NNG_SOCKET_INITIALIZER;
    };
}

#endif
