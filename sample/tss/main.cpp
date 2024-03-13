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
    FACE::TSS::Channel channel_1("channel-1");
    FACE::TSS::Channel channel_2("channel-2");

    if (!(channel_1.open() && channel_2.open())) { return -1; }
    if (!channel_1.subscribe(channel_2)) { return -1; }
    if (!channel_2.subscribe(channel_1)) { return -1; }

    std::thread prod(producer, &channel_1);
    std::thread con(consumer, &channel_2);

    prod.join();    
    con.join();

    channel_1.close();
    channel_2.close();
    
    return 0;
}
