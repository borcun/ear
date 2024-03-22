/**
 * @file periodic_task.h
 * @brief
 * @author boo
 */

#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include "task.h"

namespace EAR {
    /// task interface
    class PeriodicTask : public Task {
    public:
	/// constructor
	PeriodicTask();
	/// destructor
	virtual ~PeriodicTask();
	/// function that restart task
	/// @remark it is forbidden for periodic task
	virtual bool restart() override;

    protected:
	/// function that executes task, and is scheduled by task scheduler
	virtual void execute();
    };
}

#endif
