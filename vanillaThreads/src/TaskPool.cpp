#include <stdio.h>
#include <iostream>
#include <utility>
#include <thread>
#include <unistd.h>
#include "TaskPool.hpp"
#include "Database.hpp"


namespace vanilla::threads
{
    TaskPool::TaskPool() 
    {
        std::cout << "task pool created!\n";
        mThreadsActive = 1;
        for (uint8_t i = 0; i < 4; i++)
        {
            mWorkThreads.push_back(std::thread(&TaskPool::performThreadAction, this, i));   
            mWorkThreads[i].detach();
        }
    }
    TaskPool::~TaskPool() 
    {
        mThreadsActive = 0;
        std::cout << "task pool destroyed!\n";
    }

    void TaskPool::enqueTask(Task t)
    {
        //POSSIBLY BETTER TO CREATE HERE THREADS WHEN WE ADD NEW TASK 
       mTasksQueue.push_back(std::move(t));
    }

    void TaskPool::performThreadAction(uint8_t thrdNo)
    {
        Database database;

        while(mThreadsActive)
        {
            std::unique_lock<std::mutex> lck (mMutexTaskQueue,std::defer_lock);  
            if ((true == lck.try_lock()) && (!mTasksQueue.empty()))
            {
                Task task = std::move(*mTasksQueue.begin());
                mTasksQueue.erase(mTasksQueue.begin());
                lck.unlock();

                std::vector<uint8_t> acquiredData {database.getData(task.getId())};

                std::cout << "\nthread: "<< static_cast<int>(thrdNo) << "\n";
                (task.getPromise()).set_value(acquiredData);
                //IS LOCK RESOURCE NEEDED HERE TO ADD TO CACHE?
                task.mAddToCache(task.getId(),acquiredData);
            }
        }
        std::cerr << "BYE thread: "<< static_cast<int>(thrdNo) <<"\n";
    }


}
