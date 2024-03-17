#ifndef CORE_UTIL_H
#define CORE_UTIL_H

#include <cstdint>
#include <string>
#include "spdlog/spdlog.h"

#define SRV_INV_ID   (0U)

/// minimum period of task in usec
#define TASK_MIN_PERIOD (100000U)
/// max ts queue size
#define TS_MAX_QUEUE_SIZE (100) 
/// max data size for ts message
#define TS_MAX_DATA_SIZE (256)

#endif
