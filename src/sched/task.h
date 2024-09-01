/**
 * @file task.h
 * @brief base task class that extends synchronizable interface
 * Time-stamp: <2024-09-01 21:48:04 boo>
 */

#pragma once

#include "synchronizable.h"

namespace EAR {
  namespace Schedule {
    /// function that makes parallel execution of the task
    /// @param [in] args - task instance reference
    /// @return nullptr
    void *__makeParallel(void *args);

    /// class Task implements Task interface
    class Task : public Synchronizable {
      friend void *__makeParallel(void *args);
	    
    public:
      /// constructor
      /// @param [in] name - task name
      explicit Task(const std::string &name);
      /// destructor
      virtual ~Task();
      /// function that overload equality operator for class instance
      /// @remark equality check is done according to task name
      /// @param [in] other - right operand of equality operator
      /// @return true if this is equal to other, otherwise false
      bool operator==(const Task &other) const;
      /// function that overload not equal operator for class instance
      /// @param [in] other - right operand of equality operator
      /// @return true if this is not equal to other, otherwise false
      bool operator!=(const Task &other) const;
      /// function that initializes task
      /// @return true if the initialization done successfully, otherwise false
      virtual bool initialize(void) = 0;	    
      /// function that performs one cycle of task
      /// @remark it is supposed to be implemented by task user
      virtual void cycle(void) = 0;

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
