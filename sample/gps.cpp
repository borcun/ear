#include <iostream>
#include "gps.h"

GPS::GPS(const std::string &name) : PlatformService(name) {

}

GPS::~GPS() {

}

void GPS::process() {
    std::cout << __FUNCTION__ << std::endl;
}
