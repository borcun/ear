/**
 * @file endpoint.h
 * @brief base class that provides communication endpoint
 * Time-stamp: <2024-09-01 21:01:55 boo>
 */

#pragma once

#include <string>
#include "spdlog/spdlog.h"
#include "message.h"

namespace EAR {
  namespace Communication {
    /// communication state
    enum State {
      /// communication closed, which is default state
      COMM_CLOSED,
      /// open communication
      COMM_OPENED
    };

    /// configuration class storing endpoint attributes
    class Configuration {
    public:
      /// IP address
      std::string ip = "";
      /// port number
      uint16_t port = 0U;
      /// blocking type
      bool is_blocked = false;
      /// timeout in msec for blocking configuration
      uint32_t timeout = 0U;
    };

    /// class Endpoint that refers to receiver or transmitter
    class Endpoint {
    public:
      /// constructor
      /// @param [in] name - endpoint name
      explicit Endpoint(const std::string &name);	    
      /// destructor
      virtual ~Endpoint();	    
      /// function tht gets endpoint name
      /// @return name of endpoint
      std::string getName(void) const;	    
      /// function that gets endpoint state
      /// @return endpoint state
      State getState(void) const;	    
      /// function that initializes endpoint
      /// @param [in] config - endpoint configuration
      /// @return true if endpoint is initialized, otherwise false
      virtual bool initialize(const Configuration &config) = 0;	    
      /// function that shutdowns endpoint
      virtual void shutdown(void) = 0;
	    
    protected:
      /// endpoint state
      State m_state = COMM_CLOSED;

      /// function that checks whether IP addres is valid
      /// @param [in] addr - IP address
      /// @return true if IP address is valid, otherwise false
      bool isValidAddress(std::string addr);
	    
    private:
      /// endpoint name
      std::string m_name;
    };
  }
}
