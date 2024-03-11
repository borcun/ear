#include <iostream>
#include <thread>
#include <unistd.h>
#include "ts.h"

void consumer(FACE::TSS::TransportService *ts) {
    FACE::TSS::TSMessage msg;
    int i = 0;
    
    while (i < 100) {
	if (ts->receive(msg)) {
	    ++i;
	    std::cout << msg.getData() << "[" << msg.getSize() << "]" << std::endl;
	}

	usleep(100000);
    }

    return;
}

void producer(FACE::TSS::TransportService *ts) {
    FACE::TSS::TSMessage msg;
    
    for (int i = 0; i < 100; ++i) {
	std::string data = std::to_string(i);
	msg.setData((uint8_t *) data.c_str(), data.length());
	
	do { usleep(5000); } while(!ts->send(msg));
	std::cout << "send : " << msg.getData() << std::endl;

	usleep(100000);
    }

    return;
}

int main() {
    FACE::TSS::TransportService ts("ts");
    std::thread prod(producer, &ts);
    std::thread con(consumer, &ts);

    prod.join();    
    con.join();
    
    return 0;
}
