/**
 * @file service.h
 * @brief The base class for all kind of FACE services
 * @author boo
 * @copyright
 */

#ifndef FACE_SERVICE_H
#define FACE_SERVICE_H

#include <cstdint>
#include <string>

namespace FACE {
  /// Service that is base class for all FACE service
  /// @remark copying any FACE service is prevented
  class Service {  
  public:
    /// constructor
    /// @param name [in] - service name
    Service(const std::string &name);
  
    /// destructor
    virtual ~Service();

    /// function that gets service id
    /// @return service id
    uint32_t getId() const;

    /// function that gets service name
    /// @return service name
    std::string getName() const;

  protected:
    //! unique service id
    uint32_t m_id = 0;
    //! service name
    std::string m_name;

  private:
    // copyable and movable service prevented
    Service(const Service &service) = delete;
    Service(const Service &&service) = delete;
    Service &operator=(const Service &service) = delete;
  };
}

#endif
