#ifndef SERVICE_UTIL_H
#define SERVICE_UTIL_H

#include <cstdint>
#include <string>

#define SRV_INV_ID   (0U)
#define IOS_BASE_ID  (1000U)
#define PS_BASE_ID   (2000U)
#define TS_BASE_ID   (3000U)
#define PCS_BASE_ID  (4000U)

/// minimum period of platform service in usec
#define PS_MIN_PERIOD (100000U)
/// max tss queue size
#define TSS_MAX_QUEUE_SIZE (100) 

#endif
