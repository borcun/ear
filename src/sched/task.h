/**
 * @file task.h
 * @brief concrete task class that extends task interface, and implements execute function
 * @author boo
 * @date
 * Time-stamp: <2024-08-18 15:08:48 boo>
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
      /// function that implements execution body of task, it calls cycle() according to timing parameter
      /// @remark developer is thoroughly responsible for any deadline of the task, it should be guaranteed
      /// that the task performs its one cycle within period. The offset parameter is used to sleep the task
      /// once before it starts execution, there is no more usage for the offset for another sleep operation
      virtual void execute(void) override;

    private:
      /// thread instance
      pthread_t m_task;
    };
  }
}
