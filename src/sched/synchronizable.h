/**
 * @file synchronizable.h
 * @brief synchronizable interface class that consists of synchronization mechanisms
 * Time-stamp: <2024-09-01 21:48:43 boo>
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
    class Synchronizable {
      // scheduler uses task interface as friend, we do not open some functionalities to developers
      // the concern is not about privacy, just target to perform critical operations under the control
      friend class Scheduler;
      
    public:
      /// constructor
      /// @param [in] name - task name
      explicit Synchronizable(const std::string &name);	    
      /// destructor
      virtual ~Synchronizable();
      /// function that gets task id
      /// @return task id
      uint32_t getId(void) const;
      /// function that gets task name
      /// @return task name
      std::string getName(void) const;

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
      Synchronizable(const Synchronizable &task) = delete;
      Synchronizable(const Synchronizable &&task) = delete;
      Synchronizable &operator=(const Synchronizable &task) = delete;
      Synchronizable &operator=(const Synchronizable &&task) = delete;
    };
  }
}
