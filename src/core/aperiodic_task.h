/**
 * @file aperiodic_task.h
 * @brief
 * @author boo
 */

#ifndef APERIODIC_TASK_H
#define APERIODIC_TASK_H

#include "task.h"

namespace EAR {
    class APeriodicTask : public Task {
    public:
	APeriodicTask();
	virtual ~APeriodicTask();

    protected:
	virtual void execute();
    };
}

#endif
