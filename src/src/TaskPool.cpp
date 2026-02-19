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
        mThreadsActive = 1;
        mThreadsState = 0;
        for (uint8_t i = 0; i < NO_OF_THREADS; i++)
        {
            mWorkThreads.push_back(std::thread(&TaskPool::performThreadAction, this, i));   
            mWorkThreads[i].detach();
        }
    }
    TaskPool::~TaskPool() 
    {
        using namespace std::chrono_literals;
        mThreadsActive = 0;
        while(NO_OF_THREADS!=mThreadsState)
        {
             std::cout << "wait for threads to finish!\n";
             std::this_thread::sleep_for(10ms);
        }
        std::cout << "task pool destroyed!\n";;
    }

    void TaskPool::enqueTask(Task t)
    {
        std::lock_guard<std::mutex> lckTask (mMutexTaskQueue);  
        mTasksQueue.push_back(std::move(t));
    }

    void TaskPool::performThreadAction(uint8_t thrdNo)
    {
        (void)thrdNo;
        Database database;

        while(mThreadsActive)
        {
        std::unique_lock<std::mutex> lckTask (mMutexTaskQueue,std::defer_lock);  
            if ((true == lckTask.try_lock()) && (!mTasksQueue.empty()))
            {
                Task task = std::move(*mTasksQueue.begin());
                mTasksQueue.erase(mTasksQueue.begin());
                lckTask.unlock();

                std::vector<uint8_t> acquiredData {database.getData(task.getId())};
                //IS LOCK RESOURCE NEEDED HERE TO ADD TO CACHE?
                task.mAddToCache(task.getId(),acquiredData);
                (task.getPromise()).set_value(acquiredData);
            }
        }
        mThreadsState++;
        //std::cerr << static_cast<int>(thrdNo) <<"\n";
    }


}
