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
	class Channel {
	public:
	    explicit Channel(const std::string &name);
	    virtual ~Channel();
	    std::string getName() const;
	    bool init();
	    void destroy();
	    bool connect(const Channel &other);
	    bool send(void *buf, size_t size);
	    bool receive(void *buf, size_t size);
	    
	private:
	    std::string m_name;
	    nng_socket m_pub = NNG_SOCKET_INITIALIZER;
	    nng_socket m_sub = NNG_SOCKET_INITIALIZER;
	    bool m_is_initialized = false;
	    bool m_is_connected = false;
	};
    }
}

#endif
