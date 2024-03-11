#include "ts.h"

FACE::TSS::TransportService::TransportService(const std::string &name) : Service(name) {

}

FACE::TSS::TransportService::~TransportService() {

}

bool FACE::TSS::TransportService::send(const TSMessage &message) {
    bool is_pushed = false;
    
    m_mutex.lock();
    
    if (TS_MAX_QUEUE_SIZE > m_queue.size()) {
	m_queue.push(message);
	is_pushed = true;
    }

    m_mutex.unlock();
    
    return is_pushed;
}

bool FACE::TSS::TransportService::receive(TSMessage &message) {
    bool is_popped = false;
    
    m_mutex.lock();
    
    if (!m_queue.empty()) {
	message = m_queue.front();
	m_queue.pop();
	is_popped = true;
    }

    m_mutex.unlock();
    
    return is_popped;
}
