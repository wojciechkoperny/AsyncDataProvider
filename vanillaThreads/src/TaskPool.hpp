#ifndef VANILLATHREADS_SRC_TASK_POOL_HPP
#define VANILLATHREADS_SRC_TASK_POOL_HPP

#include <optional>
#include <vector>
#include <memory>
#include <map>
#include <thread>
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
        void performThreadSupervisorAction(int i);

    private:
        std::vector<Task> mTasksQueue;
        std::vector<std::thread> mWorkThreads; 
        std::atomic<bool> mThreadsActive;

    };

}

#endif