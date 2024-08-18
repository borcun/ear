/**
 * @file task.h
 * @brief concrete task class that extends task interface, and implements execute function
 * @author boo
 * @copyright
 * Time-stamp: <2024-08-18 13:52:26 boo>
 */

#pragma once

#include "itask.h"

namespace EAR {
  namespace Schedule {
    /// function that makes parallel execution of the task
    /// @param [in] args - task instance reference
    /// @return nullptr
    void *__makeParallel(void *args);

    /// class Task implements Task interface
    class Task : public ITask {
      friend void *__makeParallel(void *args);
	    
    public:
      /// constructor
      /// @param [in] name - task name
      explicit Task(const std::string &name);
      /// destructor
      virtual ~Task();

    protected:
      virtual void execute(void) override;

    private:
      /// thread instance
      pthread_t m_task;
    };
  }
}
