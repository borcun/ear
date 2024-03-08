#include <iostream>
#include <chrono>
#include <ctime>
#include "imu.h"

static FILE *fptr;
static int cycle = 1;

IMU::IMU(const std::string &name) : PlatformService(name) {
    fptr = fopen("imu.dat", "w+");
}

IMU::~IMU() {
    if (fptr) fclose(fptr);
}

void IMU::service() {
    fprintf(fptr, "%d %ul\n", cycle++, std::chrono::duration_cast<std::chrono::microseconds>
	    (std::chrono::system_clock::now().time_since_epoch()).count());
}
