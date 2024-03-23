/**
 * @file messenger.h
 * @brief class that provides communication infrastructure
 * @author boo
 */

#ifndef MESSENGER_H
#define MESSENGER_H

#include <string>
#include "spdlog/spdlog.h"
#include "util.h"

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
	/// @param [in] node - snode
	Messenger(const std::string &node);
	/// destructor
	virtual ~Messenger();
	/// function that gets messenger node name
	/// @return messenger node name
	const std::string &getNode() const;
	/// function that opens messenger
	/// @return true if messenger is opened, otherwise false
	virtual bool open() = 0;
	/// function that closes messenger already opened
	virtual void close() = 0;

    protected:
	/// messenger state
	MessengerState m_state = MESSENGER_CLOSED;

    private:
	/// messenger name
	std::string m_node;
    };
}

#endif
