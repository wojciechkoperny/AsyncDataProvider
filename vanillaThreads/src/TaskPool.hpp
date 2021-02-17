#ifndef VANILLATHREADS_SRC_TASK_POOL_HPP
#define VANILLATHREADS_SRC_TASK_POOL_HPP

#include <optional>
#include <vector>
#include <memory>
#include <map>
#include "Task.hpp"

namespace vanilla::threads
{
    class Task;
    class TaskPool
    {
    public:
        TaskPool();
        virtual ~TaskPool();

        void enqueTask(Task t);

    private:
        std::vector<Task> mTasksQueue;
    };

}

#endif