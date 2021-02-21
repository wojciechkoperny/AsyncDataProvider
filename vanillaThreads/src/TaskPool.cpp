#include <stdio.h>
#include <iostream>
#include <utility>
#include <thread>
#include "TaskPool.hpp"
#include <unistd.h>


namespace vanilla::threads
{
    TaskPool::TaskPool() 
    {
        std::cout << "task pool created!\n";
        mThreadsActive = 1;
        for (uint8_t i = 0; i < 1; i++)
        {
            mWorkThreads.push_back(std::thread(&TaskPool::performThreadSupervisorAction, this, i));   
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
       mTasksQueue.push_back(std::move(t));
    }

    void TaskPool::performThreadSupervisorAction(int i)
    {
        while(mThreadsActive)
        {
            std::unique_lock<std::mutex> lck (mMutexTaskQueue,std::defer_lock);
            lck.lock();
            Task task = std::move(*mTasksQueue.begin());
            mTasksQueue.erase(mTasksQueue.begin());
            lck.unlock();


            std::cerr << "hello thread: "<< i << " id task :"<< task.mId<< "\n";


            
            std::this_thread::sleep_for(std::chrono::seconds(2));
            //mTasksQueue[0].
        }
        std::cerr << "BYE thread: "<< i <<"\n";
    }


}
