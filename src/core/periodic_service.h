/**
 * @file periodic_service.h
 * @brief
 * @author boo
 */

#ifndef PERIODIC_SERVICE_H
#define PERIODIC_SERVICE_H

#include "service.h"
#include "task.h"

namespace FACE {
    /// service interface
    class PeriodicService : public Service, public Task {
    public:
	/// constructor
	/// @param [in] name - service name
	PeriodicService(const std::string &name);
	/// destructor
	virtual ~PeriodicService();
	/// function that restart service
	/// @remark it is forbidden for periodic service
	virtual bool restart() override;

    protected:
	/// function that executes service, and is scheduled by service service
	virtual void execute();
    };
}

#endif
