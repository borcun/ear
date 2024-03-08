#include <iostream>
#include <chrono>
#include <ctime>
#include "gps.h"

static FILE *fptr;
static int cycle = 1;

GPS::GPS(const std::string &name) : PlatformService(name) {
    fptr = fopen("gps.dat", "w+");
}

GPS::~GPS() {
    if (fptr) fclose(fptr);
}

void GPS::service() {
    fprintf(fptr, "%d %ul\n", cycle++, std::chrono::duration_cast<std::chrono::microseconds>
	    (std::chrono::system_clock::now().time_since_epoch()).count());
}
