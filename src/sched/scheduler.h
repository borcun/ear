/**
 * @file scheduler.h
 * @brief task scheduler class that allocates memory for tasks, starts and stops them
 * @author boo
 * @copyright
 * Time-stamp: <2024-08-18 13:53:59 boo>
 */

#pragma once

#include <list>
#include "task.h"

namespace EAR {
  namespace Schedule {
    /// scheduler state
    enum State {
      // refers ot idle scheduler
      SCHEDULER_IDLE,
      // refers to scheduler run
      SCHEDULER_RUN
    };
	
    class Scheduler {
    public:
      /// constructor
      /// @param [in] name - scheduler name
      Scheduler(const std::string &name);	    
      /// destructor
      virtual ~Scheduler();
      /// function that gets scheduler name
      /// @return scheduler name
      std::string getName(void) const;	    
      /// function that allocate memory for task for scheduling
      /// @param [in] task - task pointer
      /// @param [in] period - task period in usec
      /// @param [in] offset - task start offset in usec
      /// @return true if the memory is allocated for task, otherwise false
      bool allocate(Task *task, const uint32_t period, const uint32_t offset);	    
      /// function that runs the scheduler
      /// @pre the scheduler must be initialized firstly
      /// @return true if the scheduler runs, otherwise false
      bool start(void);	    
      /// function that terminates the scheduler
      /// @pre the scheduler must be run earlier
      /// @return true if the scheduler is terminated, otherwise false
      bool stop(void);
	    
    private:
      /// scheduler name
      std::string m_name;	    
      /// task list
      std::list<Task *> m_tasks;	    
      /// state for state machine of the scheduler
      State m_state;

      // copyable and movable task interface prevented
      Scheduler(const Scheduler &scheduler) = delete;
      Scheduler(const Scheduler &&scheduler) = delete;
      Scheduler &operator=(const Scheduler &scheduler) = delete;
    };
  }
}
