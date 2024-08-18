/**
 * @file device.h
 * @brief class that representing I/O device
 * @author boo
 * @date
 * Time-stamp: <2024-08-18 14:41:08 boo>
 */

#pragma once

#include <string>
#include "spdlog/spdlog.h"

namespace EAR {
  namespace IO {
    /// enum state for device
    enum State {
      /// none state for device
      DEV_NONE,
      /// refers to device shutdown
      DEV_SHUTDOWN,
      /// refers to device initialized
      DEV_INITIALIZED
    };

    /// base class for devices performing I/O operations
    class Device {
    public:
      /// constructor
      /// @param [in] name - device name
      /// @param [in] model - device model
      /// @param [in] version - device version
      Device(const std::string &name, const std::string &model, const std::string &version);  
      /// destructor
      virtual ~Device();	    
      /// function that gets name of device
      /// @return device name
      std::string getName(void) const;	    
      /// function that gets model of device
      /// @return device model
      std::string getModel(void) const;	    
      /// function that gets version of device
      /// @return device model
      std::string getVersion(void) const;	    
      /// function that gets state of device
      /// @return device state
      State getState(void) const;	    
      /// function that format device information as string
      /// @return device information
      std::string toString(void) const;
      /// function that opens io interface
      /// @return error code
      virtual int32_t initialize(void) = 0;
      /// function that closes io interface
      /// @return error code
      virtual int32_t shutdown(void) = 0;	    
      /// function that reads data from io interface
      /// @param [out] buf - output buffer read from io interface
      /// @param [in] size - buffer size
      /// @return error code
      virtual int32_t receive(void *buf, const uint32_t size) = 0;
      /// function that writes data from io interface
      /// @param [in] buf - input buffer written to io interface
      /// @param [in] size - buffer size
      /// @return error code
      virtual int32_t transmit(const void *buf, const uint32_t size) = 0;
      /// function that control io interface
      /// @param [in|out] target - target for io interface
      /// @param [in] op - type of operation that is applied to target
      /// @return error code
      virtual int32_t configure(void *target, const int32_t op) = 0;

    protected:
      /// io device state, explicitly open for manipulation by derived classes
      State m_state = DEV_NONE;

    private:
      /// io device name
      std::string m_name;
      /// io device model
      std::string m_model;
      /// io device version number/info
      std::string m_version;

      // copying or moving device prevented
      Device(const Device &dev) = delete;
      Device(const Device &&dev) = delete;
      Device &operator=(const Device &task) = delete;
    };
  }
}
