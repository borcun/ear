#include <iostream>
#include "ps_sched.h"

FACE::PSSS::PSScheduler *FACE::PSSS::PSScheduler::m_instance = nullptr;

FACE::PSSS::PSScheduler *FACE::PSSS::PSScheduler::getInstance() {
    return nullptr == m_instance ? m_instance = new PSScheduler() : m_instance;
}

FACE::PSSS::PSScheduler::PSScheduler() {
    m_state = SS_IDLE;
    pthread_cond_init(&m_cond_var, NULL);
}

FACE::PSSS::PSScheduler::~PSScheduler() {
    pthread_cond_destroy(&m_cond_var);
}

bool FACE::PSSS::PSScheduler::addService(PlatformService *ps) {
    if (SS_IDLE != m_state ||  nullptr == ps) {
	return false;
    }
    
    auto it = m_pservices.find(ps->getId());

    if (m_pservices.end() != it) {
	return false;
    }
    
    m_pservices.insert({ps->getId(), ps});
    
    return true;
}

bool FACE::PSSS::PSScheduler::init() {
    if (SS_IDLE != m_state || 0 == m_pservices.size()) {
	return false;
    }
    
    for (auto it = m_pservices.begin(); it != m_pservices.end(); ++it) {
	if (!it->second->start(&m_cond_var)) {
	    std::cerr << "Could not start " << it->second->getName() << ":" << it->second->getId() << std::endl;
	}
	else {
	    /// @todo wait some because of duration of thread create
	    std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
    }

    m_state = SS_INITIALIZED;    
    return true;
}

bool FACE::PSSS::PSScheduler::run() {
    if (SS_INITIALIZED != m_state) {
	return false;
    }

    pthread_cond_broadcast(&m_cond_var);
    m_state = SS_RUN;

    return true;
}

bool FACE::PSSS::PSScheduler::terminate() {
    if (SS_RUN != m_state) {
	return false;
    }
    
    for (auto it = m_pservices.begin(); it != m_pservices.end(); ++it) {
	if (!it->second->stop()) {
	    std::cerr << "Could not stop " << it->second->getName() << ":" << it->second->getId() << std::endl;
	}
    }

    m_state = SS_IDLE;
    return true;
}
