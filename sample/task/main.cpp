#include "periodic_task.h"
#include "aperiodic_task.h"
#include "scheduler.h"
#include <unistd.h>

class DCU : public FACE::PeriodicTask {
public:
    DCU(const std::string &name) : FACE::PeriodicTask(name) {}
    virtual ~DCU() {}
    virtual void process() override {
	spdlog::info("{}", getName());
    }
};

class BIT : public FACE::PeriodicTask {
public:
    BIT(const std::string &name) : FACE::PeriodicTask(name) {}
    virtual ~BIT() {}
    virtual void process() override {
	spdlog::info("{}", getName());
    }
};

class CS : public FACE::APeriodicTask {
public:
    CS(const std::string &name) : FACE::APeriodicTask(name) {}
    virtual ~CS() {}
    virtual void process() override {
	spdlog::info("{}", getName());
    }
};

class HMS : public FACE::APeriodicTask {
public:
    HMS(const std::string &name) : FACE::APeriodicTask(name) {}
    virtual ~HMS() {}
    virtual void process() override {
	spdlog::info("{}", getName());
    }
};

int main() {
    FACE::Scheduler per_sch;
    FACE::Scheduler aper_sch;
    DCU dcu("DCU Task");
    BIT bit("BIT Task");
    CS cs("CS Task");
    HMS hms("HMS Task");

    per_sch.add(&dcu, 400000);
    per_sch.add(&bit, 500000);
    aper_sch.add(&cs,  300000);
    aper_sch.add(&hms, 100000);

    per_sch.start();
    aper_sch.start();
    sleep(1);
    aper_sch.restart();
    sleep(2);
    aper_sch.restart();
    sleep(1);
    per_sch.stop();
    aper_sch.stop();
    
    return 0;
}
