/**
 * @file aperiodic_task.h
 * @brief
 * @author boo
 */

#ifndef APERIODIC_TASK_H
#define APERIODIC_TASK_H

#include "task.h"

namespace EAR {
    /// task interface
    class APeriodicTask : public Task {
    public:
	/// constructor
	APeriodicTask();
	/// destructor
	virtual ~APeriodicTask();

    protected:
	/// function that executes task, and is scheduled by task scheduler
	virtual void execute();
    };
}

#endif
