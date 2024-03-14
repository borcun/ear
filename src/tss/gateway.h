/**
 * @file gateway.h
 * @brief
 * @author boo
 */

#ifndef GATEWAY_H
#define GATEWAY_H

#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include "service_util.h"

namespace FACE {
    namespace TSS {	
	/// gateway state
	enum GatewayState {
	    GATEWAY_CLOSED,
	    GATEWAY_OPENED,
	    GATEWAY_SUBSCRIBED
	};
	
	class Gateway {
	    friend class EdgeService;
	    
	public:
	    /// constructor
	    /// @param [in] name - gateway name
	    explicit Gateway(const std::string &name);
	    /// destructor
	    virtual ~Gateway();
	    /// function that gets gateway name
	    /// @return gateway name
	    std::string getName() const;
	    /// function that opens gateway
	    /// @return true if gateway is opened, otherwise false
	    bool open();
	    /// function that closes gateway already opened
	    void close();
	    
	private:
	    /// gateway name
	    std::string m_name;
	    /// publisher socket
	    nng_socket m_pub = NNG_SOCKET_INITIALIZER;
	    /// subscriber socket
	    nng_socket m_sub = NNG_SOCKET_INITIALIZER;
	    /// gateway state
	    GatewayState m_state = GATEWAY_CLOSED;

	    /// function that subscribes the gateway to source gateway
	    /// @param [in] source - source gateway
	    /// @return true if the gateway is subscribed, otherwise false
	    bool subscribe(const Gateway *source);
	    /// function that transmits buffer to subscribers
	    /// @param [in] buf - buffer
	    /// @param [in] size - buffer size
	    /// @return true if buffer is sent to subscribers, otherwise false
	    bool transmit(void *buf, size_t size);
	    /// function that receives buffer from publisher
	    /// @param [in] buf - buffer
	    /// @param [in|out] size - buffer size
	    /// @return true if buffer is received from publisher, otherwise false
	    bool receive(void *buf, size_t &size);
	};
    }
}

#endif
