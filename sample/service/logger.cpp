#include <iostream>
#include <ctime>
#include "logger.h"

static FILE *fptr;
static int cycle = 1;

Logger::Logger(const std::string &name) : PlatformService(name) {
    fptr = fopen("logger.dat", "w+");
}

Logger::~Logger() {
    if (fptr) fclose(fptr);
}

void Logger::service() {
    fprintf(fptr, "%d %ul\n", cycle++, std::chrono::duration_cast<std::chrono::microseconds>
	    (std::chrono::system_clock::now().time_since_epoch()).count());
}
