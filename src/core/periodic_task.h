/**
 * @file periodic_task.h
 * @brief
 * @author boo
 */

#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include "task.h"

namespace EAR {
    class PeriodicTask : public Task {
    public:
	PeriodicTask();
	virtual ~PeriodicTask();
	// ignored for periodic task
	virtual bool restart() override;

    protected:
	virtual void execute() override;
    };
}

#endif
