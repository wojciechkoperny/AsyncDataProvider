#ifndef TASKPOOL_HPP
#define TASKPOOL_HPP

#include <vector>
#include "Task.hpp"

class TaskPool
{
private:
     std::vector<Task> m_queuedTask;
public:
    void enqueue_task(Task &task);
};

#endif
