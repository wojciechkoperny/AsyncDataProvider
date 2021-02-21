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
        for (uint8_t i = 0; i < 4; i++)
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
            std::cerr << "hello thread: "<< i <<"\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cerr << "BYE thread: "<< i <<"\n";
    }


}
