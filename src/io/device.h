/**
 * @file device.h
 * @brief
 * @author boo
 * @copyright
 */

#pragma once

#include <string>

namespace EAR {
    namespace IO {
	class Device {
	public:
	    /// default constructor
	    Device();
	    /// destructor
	    virtual ~Device();
	    /// function that gets model of io device
	    /// @return model
	    std::string getModel() const;
	    /// function that gets version of io device
	    /// @return model
	    std::string getVersion() const;
	    /// function that opens io interface
	    /// @return error code
	    virtual int32_t initialize();
	    /// function that closes io interface
	    /// @return error code
	    virtual int32_t shutdown();
	    /// function that reads data from io interface
	    /// @param [out] buf - output buffer read from io interface
	    /// @param [in] size - buffer size
	    /// @return error code
	    virtual int32_t receive(void *buf, const uint32_t size);
	    /// function that writes data from io interface
	    /// @param [in] buf - input buffer written to io interface
	    /// @param [in] size - buffer size
	    /// @return error code
	    virtual int32_t transmit(const void *buf, const uint32_t size);
	    /// function that control io interface
	    /// @param [in|out] target - target for io interface
	    /// @param [in] op - type of operation that is applied to target
	    /// @return error code
	    virtual int32_t configure(void *target, const int32_t op);
  
	protected:
	    /// io hardware model
	    std::string m_model;
	    /// io hardware version
	    std::string m_version;
	};
    }
}
