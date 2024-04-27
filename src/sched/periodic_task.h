/**
 * @file periodic_task.h
 * @brief
 * @author boo
 */

#pragma once

#include "task.h"

namespace EAR {
    namespace Schedule {
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
}
