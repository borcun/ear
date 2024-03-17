#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include "periodic_service.h"
#include "node.h"
#include "position.h"

class Localization : public FACE::PeriodicService, public FACE::Node {
public:
    explicit Localization(const std::string &name);
    virtual ~Localization();
    virtual void process() override;
};

#endif
