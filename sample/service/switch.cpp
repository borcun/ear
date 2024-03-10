#include <iostream>
#include <chrono>
#include <ctime>
#include "switch.h"

static FILE *fptr;
static int cycle = 1;

Switch::Switch(const std::string &name) : PlatformService(name) {
    fptr = fopen("switch.dat", "w+");
}

Switch::~Switch() {
    if (fptr) fclose(fptr);
}

void Switch::service() {
    fprintf(fptr, "%d %ul\n", cycle++, std::chrono::duration_cast<std::chrono::microseconds>
	    (std::chrono::system_clock::now().time_since_epoch()).count());
}
