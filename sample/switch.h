#ifndef SWITCH_H
#define SWITCH_H

#include "ps.h"

class Switch : public FACE::PSSS::PlatformService {
 public:
    explicit Switch(const std::string &name);
    virtual ~Switch();
    virtual void service() override;
};

#endif
