#include <stdio.h>
#include <iostream>
#include <utility>
#include <thread>
#include <unistd.h>
#include "TaskPool.hpp"
#include "Database.hpp"

#define NO_OF_THREADS 4

namespace vanilla::threads
{
    TaskPool::TaskPool()
    {
        unsigned int n = std::thread::hardware_concurrency();
        std::cout << n << " concurrent threads are supported.\n";
        mThreadsNo = 0;
    }
    TaskPool::~TaskPool()
    {
        std::cout << "task pool destroyed!\n";
    }

    void TaskPool::enqueGetTask(TaskGetData t)
    {
        std::lock_guard<std::mutex> lckTask(mMutexTaskQueue);
        mTasksGetQueue.push_back(std::move(t));
        mAllTasksQueue.push_back(TypeGetData);
        addThread();
    }

    void TaskPool::enquePutTask(TaskPutData t)
    {
        std::lock_guard<std::mutex> lckTask(mMutexTaskQueue);
        mTasksPutQueue.push_back(std::move(t));
        mAllTasksQueue.push_back(TypePutData);
        addThread();
    }

    void TaskPool::addThread()
    {
        if (mThreadsNo < NO_OF_THREADS) //std::thread::hardware_concurrency())
        {
            mWorkThreads.push_back(std::thread(&TaskPool::performThreadAction, this));
            mWorkThreads[mThreadsNo].detach();
            mThreadsNo++;
        }
        std::cout << mThreadsNo << ": Numver of thread\n";
    }

    void TaskPool::removeTaskFromQueue(TaskType_t t)
    {
        if (TypeGetData == t)
        {
            mAllTasksQueue.erase(mAllTasksQueue.begin());
            mTasksGetQueue.erase(mTasksGetQueue.begin());
        }
        else
        {
            mAllTasksQueue.erase(mAllTasksQueue.begin());
            mTasksPutQueue.erase(mTasksPutQueue.begin());
        }
        std::cout << mThreadsNo << ": Number of thread after remove\n";
    }

    void TaskPool::performThreadAction()
    {
        //(void)thrdNo;
        Database database;

        // while (!mTasksQueue.empty())
        // {
        //     std::unique_lock<std::mutex> lckTask(mMutexTaskQueue, std::defer_lock);
        //     lckTask.lock();

        while (!mAllTasksQueue.empty())
        {
            std::unique_lock<std::mutex> lckTask(mMutexTaskQueue, std::try_to_lock);
            if (lckTask.owns_lock())
            {
                switch (mAllTasksQueue.front())
                //switch ((*mTasksQueue.begin())->getType())
                {
                case TypeGetData:
                {
                    TaskGetData task = std::move(*mTasksGetQueue.begin());
                    removeTaskFromQueue(TypeGetData);
                    lckTask.unlock();

                    std::vector<uint8_t> acquiredData{database.getData(task.getId())};
                    task.mAddToCache(task.getId(), acquiredData);
                    task.getPromise().set_value(acquiredData);
                    break;
                }
                case TypePutData:
                {
                    TaskPutData task = std::move(*mTasksPutQueue.begin());
                    removeTaskFromQueue(TypePutData);
                    lckTask.unlock();

                    uint16_t acquiredId{database.putData(task.getVector())};
                    task.mAddToCache(acquiredId, task.getVector());
                    //task.mAddToCache(task.getVector(), acquiredId);
                    task.getPromise().set_value(acquiredId);
                    break;
                }
                default:
                    std::cerr << " Task has default work\n";
                    break;
                }
            }
        }
        std::cout << mThreadsNo << ": Number of thread after end\n";
        mThreadsNo--;
        //std::cerr << static_cast<int>(thrdNo) <<"\n";
    }
}
