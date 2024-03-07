#ifndef LOGGER_H
#define LOGGER_H

#include "pss.h"

class Logger : public FACE::PSSS::PlatformService {
 public:
    Logger(const std::string &name);
    virtual ~Logger();
    virtual void process() override;
};

#endif
