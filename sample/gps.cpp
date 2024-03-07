#include <iostream>
#include <chrono>
#include <ctime>
#include "gps.h"

GPS::GPS(const std::string &name) : PlatformService(name) {

}

GPS::~GPS() {

}

void GPS::process() {
    std::cout << "G: " << std::chrono::duration_cast<std::chrono::microseconds>
	(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
}
