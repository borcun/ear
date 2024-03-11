#ifndef SERVICE_UTIL_H
#define SERVICE_UTIL_H

#include <cstdint>
#include <string>
#include "spdlog/spdlog.h"

#define SRV_INV_ID   (0U)
#define IOS_BASE_ID  (1000U)
#define PS_BASE_ID   (2000U)
#define TS_BASE_ID   (3000U)
#define PCS_BASE_ID  (4000U)

/// minimum period of service in usec
#define SERVICE_MIN_PERIOD (100000U)
/// max ts queue size
#define TS_MAX_QUEUE_SIZE (100) 
/// max data size for ts message
#define TS_MAX_DATA_SIZE (256)

#endif
