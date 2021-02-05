#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <vThreads.hpp>
#include <Dispacher.hpp>
#include <main.hpp>
#include <atomic>
#include <future>

struct sigaction sa;
std::mutex mtx1, mtx2, mtx3;
std::condition_variable cv;

std::atomic<bool> run{true};
//volatile bool run = true;


void *printerFunction1(void *a)
{
    std::unique_lock<std::mutex> lck(mtx1);
    cv.wait(lck);
    while (run)
    {
        //static_cast<(int *)>
        std::cout << "\nprinterFunction1: " << *static_cast<int *>(a) << "\n";
        sleep(1);
    }
    return NULL;
}
void *printerFunction2(void *a)
{
    std::unique_lock<std::mutex> lck(mtx2);
    cv.wait(lck);
    while (run)
    {
        std::cout << "\nprinterFunction2: " << *static_cast<int *>(a) << "\n";
        sleep(1);
    }
    return NULL;
}

void SigintHandler(int a)
{
    std::cout << "\nTERMINATION KEY DETECT: " << a << "\n";
    run = false;
}

int main(int argc, char *argv[])
{
    int runTask;
    int numberOfTasks{2};
    if (argc > 1)
    {
        numberOfTasks = atoi(argv[1]);
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SigintHandler;
    (void)sigaction(SIGINT, &sa, NULL);

    //////////////////////TEST DISPACHER SECTION//////////////////

    Dispacher<int> dispach;
    std::promise<int> test{dispach.RequestDataById(2)};
    
    std::cout << "result=" << (test.get_future()).get() << '\n';

    //////////////////////TEST DISPACHER SECTION//////////////////
 /*
    std::vector<workerDescr_t> workerDescr;
    std::vector<Task> workerTasks;

    for (int i = 0; i < numberOfTasks; i++)
    {
        workerDescr_t a; //jakos ladniej zapisac?
        workerDescr.push_back(a);
        workerDescr[static_cast<long unsigned int>(i)].FunctionArgs = i;
    }

    mtx3.lock();
    std::cout << "lock!\n";
    mtx3.unlock();

    workerDescr[0].Function = printerFunction1; //jakos ladniej zapisac?
    workerDescr[1].Function = printerFunction2;

    for (int i = 0; i < numberOfTasks; i++)
    {
        workerTasks.push_back(Task{workerDescr[static_cast<long unsigned int>(i)].Function, static_cast<void *>(&workerDescr[static_cast<long unsigned int>(i)].FunctionArgs)});
    }

    std::cout << "Start?\n";
    std::cin >> runTask;
    if (runTask)
    {
        std::cout << "go!\n";
        cv.notify_all();
    }

    workerTasks[0].joinTask();
    workerTasks[1].joinTask(); */

    // sleep(3);
    //pthread_exit(NULL);
    return 0;
}

/*
cmake 
RAII 

-dopisac klase runnable
w srodku klasy ^ jako member ptread
w konstruktorze ptcreate
w destruktorze pt delete
std::thread


2####
przenies implementacje do task.cpp
utpwrzyc w biblioteke dodac tam wszystko co potrzebyjemy
i potem dodac do projektu ta biblioteke.
    //condition varialbe http://www.cplusplus.com/reference/condition_variable/condition_variable/
    (void)pthread_join(thread_fun1, NULL); //doczytac co to robi

*/
