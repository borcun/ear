/**
 * @file network_manager.h
 * @brief one receiver to many transmitter network
 * @author boo
 * @copyright
 */

#pragma once

#include <list>
#include "receiver.h"
#include "transmitter.h"

namespace EAR {
    namespace Communication {
	class NetworkManager {
	public:
	    /// constructor
	    /// @param [in] name - network manager name
	    explicit NetworkManager(const std::string &name);
	    
	    /// destructor
	    virtual ~NetworkManager();

	    /// function that gets network manager name
	    /// @return name of network manager
	    std::string getName() const;

	    /// function that initializes network manager
	    /// @param [in] config - network manager configuration
	    /// @return true if initialization is done, false otherwise
	    virtual bool initialize(Configuration config);

	    /// function that gets network server/receiver
	    /// @return server
	    Receiver *getReceiver();

	    /// function that creates network client/transmitter
	    /// @return client
	    Transmitter *getTransmitter();

	    /// function that terminates network manager
	    virtual void terminate();

	protected:
	    /// initialization flag
	    bool m_is_init = false;
	    // one server (receiver) instance
	    Receiver *m_receiver = nullptr;
	    /// many client (transmitter) instance
	    std::list<Transmitter *> m_transmitters;
	    
	private:
	    /// network manager name
	    std::string m_name;
	    /// current configuration
	    Configuration m_config;
	    
	    // copyable and movable network manager prevented
	    NetworkManager(const NetworkManager &nm) = delete;
	    NetworkManager(const NetworkManager &&nm) = delete;
	    NetworkManager &operator=(const NetworkManager &nm) = delete;
	};
    }
}
