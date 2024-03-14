#ifndef POSITIONING_H
#define POSITIONING_H

#include "position.h"
#include "pcs.h"

class Positioning : public FACE::PCSS::PortableComponentService {
public:
    explicit Positioning(const std::string &name);
    virtual ~Positioning();
    virtual void process() override;
};

#endif
