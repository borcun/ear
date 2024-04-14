/**
 * @file subscriber.h
 * @brief class that provides subscriber infrastructure
 * @author boo
 */

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <nng/nng.h>
#include <nng/protocol/pubsub0/sub.h>
#include "messenger.h"

namespace EAR {
    class Subscriber : public Messenger {
    public:
	/// constructor
	/// @param [in] node - subscriber node
	Subscriber(const std::string &node);
	/// destructor
	virtual ~Subscriber();
	/// function that sets timeout of subscriber
	/// @remark default time is zero
	/// @param [in] timeout - subscriber receive timeout
	void setTimeout(const int32_t timeout);
	/// function that opens subscriber
	/// @return true if subscriber is opened, otherwise false
	virtual bool open() override;
	/// function that closes subscriber already opened
	virtual void close() override;
	/// function that subscribes the publisher
	/// @param [in] pub - publisher to be subscribed
	/// @return true if the subscription is done successfully, otherwise false
	bool subscribe(const Messenger *pub);
	/// function that receives buffer from the publisher
	/// @param [in] buf - buffer
	/// @param [in|out] size - buffer size
	/// @return true if buffer is received from the publisher, otherwise false
	bool receive(void *buf, size_t &size);

    private:
	/// subscriber socket
	nng_socket m_sub = NNG_SOCKET_INITIALIZER;
	/// receive timeout
	int32_t m_timeout = 0;
    };
}

#endif
