#include <iostream>
#include <chrono>
#include <ctime>
#include "logger.h"

Logger::Logger(const std::string &name) : PlatformService(name) {

}

Logger::~Logger() {

}

void Logger::process() {
    std::cout << "L: " << std::chrono::duration_cast<std::chrono::microseconds>
	(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
}
