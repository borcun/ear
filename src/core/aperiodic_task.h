/**
 * @file aperiodic_task.h
 * @brief
 * @author boo
 */

#ifndef APERIODIC_TASK_H
#define APERIODIC_TASK_H

#include "task.h"

namespace FACE {
    /// task interface
    class APeriodicTask : public Task {
    public:
	/// constructor
	APeriodicTask(const std::string &name);
	/// destructor
	virtual ~APeriodicTask();

    protected:
	/// function that executes service, and is scheduled by service task
	virtual void execute();
    };
}

#endif
