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
        void performThreadAction(uint8_t i);

    private:
        std::vector<Task> mTasksQueue;
        std::vector<std::thread> mWorkThreads; 
        std::atomic<bool> mThreadsActive;
        std::atomic<uint8_t> mThreadsState;
        std::mutex mMutexTaskQueue;
    };

}

#endif