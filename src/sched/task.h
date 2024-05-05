/**
 * @file task.h
 * @brief concrete task class that extends task interface, and implements execute function
 * @author boo
 */

#pragma once

#include "itask.h"

namespace EAR {
    namespace Schedule {
	/// function that makes parallel execution of the task
	/// @param [in] args - task instance reference
	/// @return nullptr
	void *__makeParallel(void *args);

	/// class Task implements Task interface
	class Task : public ITask {
	    friend void *__makeParallel(void *args);
	    
	public:
	    explicit Task(const std::string &name);
	    virtual ~Task();

	protected:
	    virtual void execute() override;

	private:
	    /// thread instance
	    pthread_t m_task;
	};
    }
}
