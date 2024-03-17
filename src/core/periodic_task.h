/**
 * @file periodic_task.h
 * @brief
 * @author boo
 */

#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include "task.h"

namespace FACE {
    /// task interface
    class PeriodicTask : public Task {
    public:
	/// constructor
	/// @param [in] name - task name
	PeriodicTask(const std::string &name);
	/// destructor
	virtual ~PeriodicTask();
	/// function that restart task
	/// @remark it is forbidden for periodic task
	virtual bool restart() override;

    protected:
	/// function that executes service, and is scheduled by service task
	virtual void execute();
    };
}

#endif
