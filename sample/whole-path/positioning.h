#ifndef POSITIONING_H
#define POSITIONING_H

#include "position.h"
#include "ps.h"

class Positioning : public FACE::PSSS::PlatformService {
 public:
    explicit Positioning(const std::string &name);
    virtual ~Positioning();
    virtual void service() override;
};

#endif
