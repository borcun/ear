/**
 * @file eth_service.h
 * @brief
 * @author boo
 * @copyright
 */

#ifndef ETH_SERVICE_H
#define ETH_SERVICE_H

#include "ios.h"

class EthernetService : public FACE::IOSS::IOService {
 public:
  /// constructor
  /// @param [in] name - io service name
  EthernetService(const std::string &name);

  /// destructor
  virtual ~EthernetService();

  /// function that opens io interface
  /// @return error code
  virtual int32_t open();

  /// function that closes io interface
  /// @return error code
  virtual int32_t close();

  /// function that reads data from io interface
  /// @param [out] buf - output buffer read from io interface
  /// @param [in] size - buffer size
  /// @return error code
  virtual int32_t read(uint8_t *buf, const uint32_t size);

  /// function that writes data from io interface
  /// @param [in] buf - input buffer written to io interface
  /// @param [in] size - buffer size
  /// @return error code
  virtual int32_t write(const uint8_t *buf, const uint32_t size);

  /// function that control io interface
  /// @param [in|out] target - target for io interface
  /// @param [in] op - type of operation that is applied to target
  /// @return error code
  virtual int32_t ioctl(void *target, const int32_t op);
};

#endif
