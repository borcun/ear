#ifndef PS_SCHEDULER_H
#define PS_SCHEDULER_H

#include <map>
#include "ps.h"

namespace FACE {
    namespace PSSS {
	/// scheduler states
	enum SchedulerState {
	    SS_IDLE,
	    SS_INITIALIZED,
	    SS_RUN
	};
	
	class PSScheduler {
	public:
	    /// function that gets instance of the class
	    /// @return PSScheduler pointer
	    static PSScheduler *getInstance();
	    /// destructor
	    virtual ~PSScheduler();
	    /// function that adds a platform service into the scheduler
	    /// @param [in] ps - platform service pointer
	    /// @return true if the service is added, otherwise false
	    bool addService(PlatformService *ps);
	    /// function that initializes the scheduler
	    /// @return true if the scheduler is initialized, otherwise false
	    bool init();
	    /// function that runs the scheduler
	    /// @pre the scheduler must be initialized
	    /// @return true if the scheduler runs, otherwise false
	    bool run();
	    /// function that terminates the scheduler
	    /// @pre the scheduler must be run
	    /// @return true if the scheduler is terminated, otherwise false
	    bool terminate();
	    
	private:
	    /// service scheduler
	    static PSScheduler *m_instance;
	    /// platform specific services
	    std::map<uint32_t, PlatformService *> m_pservices;
	    /// condition variable to synchronize all platform services
	    pthread_cond_t m_cond_var;
	    /// initialization flag
	    SchedulerState m_state;

	    /// constructor
	    PSScheduler();
	};
    }
}

#endif
