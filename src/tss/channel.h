/**
 * @file channel.h
 * @brief
 * @author boo
 */

#ifndef TRANSPORT_SERVICE_CHANNEL_H
#define TRANSPORT_SERVICE_CHANNEL_H

#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include "service_util.h"

namespace FACE {
    namespace TSS {
	/// channel state
	enum ChannelState {
	    CHS_CLOSED,
	    CHS_OPENED,
	    CHS_SUBSCRIBED
	};
	
	class Channel {
	public:
	    /// constructor
	    /// @param [in] name - channel name
	    explicit Channel(const std::string &name);
	    /// destructor
	    virtual ~Channel();
	    /// function that gets channel name
	    /// @return channel name
	    std::string getName() const;
	    /// function that opens channel
	    /// @return true if channel is opened, otherwise false
	    bool open();
	    /// function that closes channel already opened
	    void close();
	    /// function that subscribes the channel to source channel
	    /// @param [in] source - source channel
	    /// @return true if the channel is subscribed, otherwise false
	    bool subscribe(const Channel &source);
	    /// function that sends buffer to subscribers
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
	    /// channel name
	    std::string m_name;
	    /// publisher socket
	    nng_socket m_pub = NNG_SOCKET_INITIALIZER;
	    /// subscriber socket
	    nng_socket m_sub = NNG_SOCKET_INITIALIZER;
	    /// channel state
	    ChannelState m_state = CHS_CLOSED;
	};
    }
}

#endif
