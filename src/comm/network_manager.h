#pragma once

#include <list>
#include "listener.h"
#include "transmitter.h"

namespace EAR {
    namespace Communication {
	class NetworkManager {
	public:
	    /// default constructor
	    NetworkManager();
	    /// destructor
	    virtual ~NetworkManager();
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
	    NetworkManager(const NetworkManager &nm);
	    NetworkManager(const NetworkManager &&nm);
	};
    }
}
