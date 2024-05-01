/**
 * @file itask.h
 * @brief task interface class
 * @author boo
 */

#pragma once

#include <pthread.h>
#include <chrono>
#include "spdlog/spdlog.h"

/// minimum period of task in usec
#define TASK_MIN_PERIOD (100000U)

namespace EAR {
    namespace Schedule {  
	/// task interface class
	class ITask {
	    // scheduler uses task interface
	    friend class Scheduler;
      
	public:
	    /// default constructor
	    ITask(const std::string &name);
	    /// destructor
	    virtual ~ITask();
	    /// function that gets task id
	    /// @return task id
	    uint32_t getId() const;
	    /// function that gets task id
	    /// @return task id
	    std::string getName() const;
	    /// function that initializes task
	    virtual bool initialize() = 0;
	    /// function that is supposed to be implemented by task user
	    virtual void cycle() = 0;

	protected:
	    /// task period in usec
	    std::chrono::microseconds m_period;
	    /// task start offset in usec
	    std::chrono::microseconds m_offset;
	    /// run flag indicating state of the task
	    bool m_is_running;
	    /// start mutex used to give start to the task
	    pthread_mutex_t m_start_mutex;
	    /// progress mutex used to control progress of the task
	    pthread_mutex_t m_progress_mutex;
	    /// start condition flag for the thread
	    pthread_cond_t m_start_cond_var;
	    /// progress condition flag for the thread
	    pthread_cond_t m_progress_cond_var;
	
	    /// function that sets period of the task
	    /// @param [in] period - task period in usec
	    void setPeriod(const std::chrono::microseconds period);
	    /// function that sets offset of the task
	    /// @param [in] offset - offset to sleep before execution
	    void setOffset(const std::chrono::microseconds offset);	
	    /// function that starts task
	    /// @return true if task is started, otherwise false
	    bool start();
	    /// function that stops task
	    /// @return true if task is stopped, otherwise false
	    bool stop();
	    
	    /// function that is execution body of the task, specific to task algorithm
	    /// @remark it is supposed to be implemented by class based on task derived
	    virtual void execute() = 0;

	private:
	    /// task id
	    uint32_t m_id;
	    /// task name
	    std::string m_name;

	    // copyable and movable task interface prevented
	    ITask(const ITask &task) = delete;
	    ITask(const ITask &&task) = delete;
	    ITask &operator=(const ITask &task) = delete;
	};
    }
}
