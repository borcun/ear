/**
 * @file network_manager.h
 * @brief one listener to many transmitter network
 * @author boo
 * @copyright
 */

#pragma once

#include <list>
#include "listener.h"
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
	    /// @return true if initialization is done, false otherwise
	    virtual bool initialize();
	    /// function that gets network server
	    /// @return server
	    Listener *getServer();
	    /// function that creates network client
	    /// @return client
	    Transmitter *getClient();
	    /// function that terminates network manager
	    virtual void terminate();

	protected:
	    Listener *m_server = nullptr;
	    std::list<Transmitter *> m_clients;
	    bool m_is_init = false;
	    
	private:
	    std::string m_name;
	    NetworkManager(const NetworkManager &nm) = delete;
	    NetworkManager(const NetworkManager &&nm) = delete;
	    NetworkManager &operator=(const NetworkManager &nm) = delete;
	};
    }
}
