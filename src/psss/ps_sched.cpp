#include "ps_sched.h"
#include "spdlog/spdlog.h"

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
    if (nullptr == ps) {
	spdlog::error("invalid platform service");
	return -1;
    }

    if (SS_IDLE != m_state) {
	spdlog::error("could not add platform service [service: {}]", ps->getName());
	return false;
    }

    auto it = m_pservices.find(ps->getId());

    if (m_pservices.end() != it) {
	spdlog::error("platform service already added [service: {}]", ps->getName());
	return false;
    }
    
    m_pservices.insert({ps->getId(), ps});
    
    return true;
}

bool FACE::PSSS::PSScheduler::init() {
    if (SS_IDLE != m_state || 0 == m_pservices.size()) {
	spdlog::error("could not initialize the platform service scheduler");
	return false;
    }
    
    for (auto it = m_pservices.begin(); it != m_pservices.end(); ++it) {
	if (!it->second->start(&m_cond_var)) {
	    spdlog::critical("could not start platform service [service: {}]", it->second->getName());
	}
	else {
	    /// @todo wait some because of duration of thread create, solve it!!!
	    std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
    }

    m_state = SS_INITIALIZED;    
    return true;
}

bool FACE::PSSS::PSScheduler::run() {
    if (SS_INITIALIZED != m_state) {
	spdlog::error("could not run the platform service scheduler");
	return false;
    }

    pthread_cond_broadcast(&m_cond_var);
    m_state = SS_RUN;

    return true;
}

bool FACE::PSSS::PSScheduler::terminate() {
    if (SS_RUN != m_state) {
	spdlog::error("could not terminate the platform service scheduler");
	return false;
    }
    
    for (auto it = m_pservices.begin(); it != m_pservices.end(); ++it) {
	if (!it->second->stop()) {
	    spdlog::critical("could not stop platform service [service: {}]", it->second->getName());
	}
    }

    m_state = SS_IDLE;
    return true;
}
