/**
 * @file task.h
 * @brief
 * @author boo
 */

#pragma once

#include "itask.h"

namespace EAR {
    namespace Schedule {
	/// function that makes parallel execution of the task
	/// @param [in] args - task instance reference
	/// @return nullptr
	void *makeParallel(void *args);

	/// class Task implements Task interface
	class Task : public ITask {
	    friend void *makeParallel(void *args);
	    
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
