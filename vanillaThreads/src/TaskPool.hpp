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

        void enqueGetTask(TaskGetData &&t);
        void enquePutTask(TaskPutData &&t);

        void performThreadAction();

    private:
        void removeTaskFromQueue(TaskType_t t);
        void addThread();
        std::vector<TaskType_t> mAllTasksQueue;
        std::vector<TaskGetData> mTasksGetQueue;
        std::vector<TaskPutData> mTasksPutQueue;
        std::vector<std::thread> mWorkThreads;
        std::atomic<uint32_t> mThreadsNo;
        std::atomic<uint32_t> mThreadsClose;
        std::mutex mMutexTaskQueue;
    };

}

#endif