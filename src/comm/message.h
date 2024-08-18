/**
 * @file message.h
 * @brief message type sharing between receiver and transmitter endpoints
 * @author boo
 * @date
 * Time-stamp: <2024-08-18 14:44:30 boo>
 */

#pragma once

#include <cstdint>

namespace EAR {
  namespace Communication {
    /// Message type
    struct Message {
      /// source id of message
      uint32_t src = 0U;
      /// length of message
      uint32_t len = 0U;
      /// message data
      uint8_t *buf = nullptr;
      /// checksum for message
      uint16_t crc = 0U;
    };
  }
}
