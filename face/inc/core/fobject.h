/**
 * @file fmodule.h
 * @brief The base class for all kind of FACE modules
 * @author boo
 * @copyright
 */

#ifndef FACE_MODULE_H
#define FACE_MODULE_H

#include <cstdint>
#include <string>

//! initial module id
#define FMODULE_INITIAL_ID (1)

/**
 * @class FModule that is base class for each FACE module
 * @remark copying any FACE module is prevented
 */
class FModule {  
public:
  /**
   * @brief constructor
   * @param name [in] - module name
   */
  FModule(const std::string &name);
  
  /**
   * @brief destructor
   */
  virtual ~FModule();

  /**
   * @brief function that gets module id
   * @return module id
   */
  uint32_t getId() const;

  /**
   * @brief function that gets module name
   * @return module name
   */
  std::string getName() const;

private:
  //! unique module id
  static uint32_t m_id;
  //! module name
  std::string m_name;

  // copyable and movable module prevented
  FModule(const FModule &module) = delete;
  FModule(const FModule &&module) = delete;
  FModule &operator=(const FModule &module) = delete;
};

#endif
