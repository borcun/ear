#ifndef IMU_H
#define IMU_H

#include "ps.h"

class IMU : public FACE::PSSS::PlatformService {
 public:
    explicit IMU(const std::string &name);
    virtual ~IMU();
    virtual void service() override;
};

#endif
