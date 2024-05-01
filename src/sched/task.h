/**
 * @file task.h
 * @brief
 * @author boo
 */

#pragma once

#include "itask.h"

namespace EAR {
    namespace Schedule {
	void *makeParallel(void *args);
	
	class Task : public ITask {
	    friend void *makeParallel(void *args);
	    
	public:
	    Task(const std::string &name);
	    virtual ~Task();

	protected:
	    virtual void execute() override;

	private:
	    pthread_t m_task;
	};
    }
}
