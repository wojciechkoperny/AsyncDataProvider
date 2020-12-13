#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <vThreads.hpp>

struct sigaction sa;
std::mutex mtx;
std::condition_variable cv;

volatile bool run = true;

void *printerFunction(void *a)
{
    // while (run)
    {
        std::cout << "\nprinterFunction: " << *(int *)a << "\n";
        sleep(1);
    }
}
//*static_cast<std::function<void*()>*>(context);

void SigintHandler(int a)
{
    std::cout << "\nTERMINATION KEY DETECT: " << a << "\n";
    run = false;
    //(void)pthread_cancel(Task::thread_fun1);
    //(void)pthread_cancel(Task::thread_fun2);
}

int main(int argc, char *argv[])
{

    int numberOfTasks{2};
    if (argc > 1)
    {
        numberOfTasks = atoi(argv[1]);
    }
    std::cout << "Start\n";

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SigintHandler;
    (void)sigaction(SIGINT, &sa, NULL);

    std::vector<Task> workerTasks;

    for (int i = 0; i < numberOfTasks; i++)
    {
        workerTasks.push_back(Task{std::function<void *(void *)>{printerFunction}, (void *)&i});
        workerTasks[i].joinTask();
    }

    /*  
    Task task1{std::function<void()>{printerFunction}};
    Task task2{std::function<void()>{printerFunction}};

    workerTasks.push_back(task1);
    workerTasks.push_back(task2);
 */

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
