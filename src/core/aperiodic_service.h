/**
 * @file aperiodic_service.h
 * @brief
 * @author boo
 */

#ifndef APERIODIC_SERVICE_H
#define APERIODIC_SERVICE_H

#include "service.h"
#include "task.h"

namespace FACE {
    /// service interface
    class APeriodicService : public Service, public Task {
    public:
	/// constructor
	/// @param [in] name - service name
	APeriodicService(const std::string &name);
	/// destructor
	virtual ~APeriodicService();

    protected:
	/// function that executes service, and is scheduled by service service
	virtual void execute();
    };
}

#endif
