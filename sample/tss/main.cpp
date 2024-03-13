#include <iostream>
#include <thread>
#include <unistd.h>
#include "channel.h"

void consumer(FACE::TSS::Channel *channel) {
    int i = 0;
    uint8_t buf[1];
    size_t size = 1;
    
    while (i < 10) {
	memset(buf, 0x00, size);
	
	if (channel->receive(buf, size)) {
	    ++i;
	    spdlog::info("{} received: {}", channel->getName(), (int) buf[0]);
	}
	else {
	    spdlog::error("{} receive failed", channel->getName());

	    if (i > 30) break;
	}

	usleep(100000);
    }

    for (int i = 0; i < 10; ++i) {
	std::string data = std::to_string(i);
	
	if (!channel->send((uint8_t *) data.c_str(), data.length())) {
	    spdlog::error("{} send failed", channel->getName());
	}
	else {
	    spdlog::info("{} sent", channel->getName());
	}

	usleep(100000);
    }

    return;
}

void producer(FACE::TSS::Channel *channel) {
    int i = 0;
    uint8_t buf[1];
    size_t size = 1;
    
    for (int i = 0; i < 10; ++i) {
	std::string data = std::to_string(i);
	
	if (!channel->send((uint8_t *) data.c_str(), data.length())) {
	    spdlog::error("{} send failed", channel->getName());
	}
	else {
	    spdlog::info("{} sent", channel->getName());
	}

	usleep(100000);
    }

    i = 0;
    
    while (i < 10) {
	memset(buf, 0x00, size);
	
	if (channel->receive(buf, size)) {
	    ++i;
	    spdlog::info("{} received: {}", channel->getName(), (int) buf[0]);
	}
	else {
	    spdlog::error("{} receive failed", channel->getName());

	    if (i > 30) break;
	}

	usleep(100000);
    }

    return;
}

int main() {
    FACE::TSS::Channel channel1("channel1");
    FACE::TSS::Channel channel2("channel2");

    if (!channel1.init() || !channel2.init()) {
	channel1.destroy();
	channel2.destroy();

	return -1;
    }
    
    if (!channel1.connect(channel2)) {
	return -1;
    }
    
    if (!channel2.connect(channel1)) {
	return -1;
    }

    std::thread prod(producer, &channel1);
    std::thread con(consumer, &channel2);

    prod.join();    
    con.join();

    channel1.destroy();
    channel2.destroy();
    
    return 0;
}
