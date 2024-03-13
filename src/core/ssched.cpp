#include "ssched.h"

FACE::ServiceScheduler::ServiceScheduler() {
    m_state = SS_IDLE;
    pthread_cond_init(&m_cond_var, NULL);
}

FACE::ServiceScheduler::~ServiceScheduler() {
    pthread_cond_destroy(&m_cond_var);
}

bool FACE::ServiceScheduler::addService(PortableService *pserv) {
    if (nullptr == pserv) {
	spdlog::error("could not add invalid portable service");
	return false;
    }

    if (SS_IDLE != m_state) {
	spdlog::error("could not add portable service [service: {}]", pserv->getName());
	return false;
    }

    auto it = m_services.find(pserv->getId());

    if (m_services.end() != it) {
	spdlog::error("portable service already added [service: {}]", pserv->getName());
	return false;
    }
    
    m_services.insert({pserv->getId(), pserv});
    
    return true;
}

bool FACE::ServiceScheduler::init() {
    if (SS_IDLE != m_state || 0 == m_services.size()) {
	spdlog::error("could not initialize the portable service scheduler");
	return false;
    }
    
    for (auto it = m_services.begin(); it != m_services.end(); ++it) {
	if (!it->second->start(&m_cond_var)) {
	    spdlog::critical("could not start portable service [service: {}]", it->second->getName());
	}
	else {
	    /// @todo wait some because of duration of thread create, solve it!!!
	    std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
    }

    m_state = SS_INIT;    
    return true;
}

bool FACE::ServiceScheduler::run() {
    if (SS_INIT != m_state) {
	spdlog::error("could not run the portable service scheduler");
	return false;
    }

    pthread_cond_broadcast(&m_cond_var);
    m_state = SS_RUN;

    return true;
}

bool FACE::ServiceScheduler::terminate() {
    if (SS_RUN != m_state) {
	spdlog::error("could not terminate the portable service scheduler");
	return false;
    }
    
    for (auto it = m_services.begin(); it != m_services.end(); ++it) {
	if (!it->second->stop()) {
	    spdlog::critical("could not stop portable service [service: {}]", it->second->getName());
	}
    }

    m_state = SS_IDLE;
    return true;
}
