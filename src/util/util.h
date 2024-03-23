#ifndef CORE_UTIL_H
#define CORE_UTIL_H

#include <cstdint>

/// minimum period of task in usec
#define TASK_MIN_PERIOD (100000U)
/// maximum message length
#define MAX_MSG_LEN (256U)
/// pubsub node location
#define NODE_DIR ((const char *) "ipc:///tmp/")

#endif
