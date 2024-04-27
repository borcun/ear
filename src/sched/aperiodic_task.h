/**
 * @file aperiodic_task.h
 * @brief
 * @author boo
 */

#pragma once

#include "task.h"

namespace EAR {
    namespace Schedule {
	class AperiodicTask : public Task {
	public:
	    AperiodicTask();
	    virtual ~AperiodicTask();

	protected:
	    virtual void execute() override;
	};
    }
}
