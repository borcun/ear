#ifndef LOGGER_H
#define LOGGER_H

#include "ps.h"

class Logger : public FACE::PSSS::PlatformService {
 public:
    Logger(const std::string &name);
    virtual ~Logger();
    virtual void service() override;
};

#endif
