/**
 * @file itask.h
 * @brief task interface class that consists of synchronization mechanisms for derived classes
 * @author boo
 * @date
 * Time-stamp: <2024-08-18 15:03:15 boo>
 */

#pragma once

#include <pthread.h>
#include <chrono>
#include "spdlog/spdlog.h"

/// minimum period of task in usec
#define TASK_MIN_PERIOD (100000U)

namespace EAR {
  namespace Schedule {  
    /// task interface that is used by internal classes, not for developers
    class ITask {
      // scheduler uses task interface as friend, we do not open some functionalities to developers
      // the concern is not about privacy, just target to perform critical operations under the control
      friend class Scheduler;
      
    public:
      /// constructor
      /// @param [in] name - task name
      explicit ITask(const std::string &name);	    
      /// destructor
      virtual ~ITask();
      /// function that gets task id
      /// @return task id
      uint32_t getId(void) const;
      /// function that gets task name
      /// @return task name
      std::string getName(void) const;
      /// function that initializes task
      /// @return true if the initialization done successfully, otherwise false
      virtual bool initialize(void) = 0;	    
      /// function that performs one cycle of task
      /// @remark it is supposed to be implemented by task user
      virtual void cycle(void) = 0;

    protected:
      /// task period in usec
      std::chrono::microseconds m_period;
      /// task start offset in usec
      std::chrono::microseconds m_offset;
      /// run flag indicating state of the task
      bool m_is_running;
      /// start mutex used to give start to the task
      pthread_mutex_t m_start_mutex;
      /// start condition flag for the thread
      pthread_cond_t m_start_cond_var;
	
      /// function that sets period of the task
      /// @param [in] period - task period in usec
      void setPeriod(const std::chrono::microseconds period);	    
      /// function that sets offset of the task
      /// @param [in] offset - offset to sleep before execution
      void setOffset(const std::chrono::microseconds offset);	    
      /// function that starts task
      /// @return true if task is started, otherwise false
      bool start(void);	    
      /// function that stops task
      /// @return true if task is stopped, otherwise false
      bool stop(void);	    
      /// function that is execution body of the task, specific to task algorithm
      /// @remark it is supposed to be implemented by class based on task derived
      virtual void execute(void) = 0;

    private:
      /// task id
      uint32_t m_id;
      /// task name
      std::string m_name;

      // copyable and movable task interface prevented
      ITask(const ITask &task) = delete;
      ITask(const ITask &&task) = delete;
      ITask &operator=(const ITask &task) = delete;
    };
  }
}
