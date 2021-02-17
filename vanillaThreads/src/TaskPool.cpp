#include <stdio.h>
#include <iostream>
#include <utility>
#include "TaskPool.hpp"

namespace vanilla::threads
{
    TaskPool::TaskPool() {}
    TaskPool::~TaskPool() {}

    void TaskPool::enqueTask(Task t)
    {
       mTasksQueue.push_back(std::move(t));
    }
}
