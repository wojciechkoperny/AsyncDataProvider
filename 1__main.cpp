#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <vThreads.hpp>
#include <main.hpp>

struct sigaction sa;
std::mutex mtx1, mtx2;
std::condition_variable cv;

volatile bool run = true;

void *printerFunction1(void *a)
{
    //int ilosc(10);
    std::unique_lock<std::mutex> lck(mtx1);
    cv.wait(lck);
    while (run)
    {
        std::cout << "\nprinterFunction1: " << *(int *)a << "\n";
        sleep(1);
        // ilosc--;
    }
}
void *printerFunction2(void *a)
{
    //int ilosc(10);
    std::unique_lock<std::mutex> lck(mtx2);
    cv.wait(lck);
    while (run)
    {
        std::cout << "\nprinterFunction2: " << *(int *)a << "\n";
        sleep(1);
        // ilosc--;
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
    int runTask;
    int numberOfTasks{2};
    if (argc > 1)
    {
        numberOfTasks = atoi(argv[1]);
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SigintHandler;
    (void)sigaction(SIGINT, &sa, NULL);

    std::vector<worker_t> workerDescr;
    std::vector<Task> workerTasks;
    std::vector<std::function<void *(void *)>> workerFunction;
    std::vector<int> workerFunctionArguments;
    workerFunction.push_back(printerFunction1); //jakos ladniej zapisac?
    workerFunction.push_back(printerFunction2);
    for (int i = 0; i < numberOfTasks; i++)
    {
        worker_t a;
        workerDescr.push_back(a);
    }
    workerDescr[0].Function = printerFunction1;
    workerDescr[1].Function = printerFunction2;
    for (int i = 0; i < numberOfTasks; i++)
    {
        workerDescr[i].FunctionArgs = i;
        workerTasks.push_back(Task{workerDescr[i].Function, (void *)&workerDescr[i].FunctionArgs});
        //workerTasks[i].joinTask();
    }

    std::cout << "Jedziem?\n";
    std::cin >> runTask;
    if (runTask)
    {
        std::cout << "go!\n";
        cv.notify_all();
    }
    workerTasks[0].joinTask();
    workerTasks[1].joinTask();
    /*  
    Task task1{std::function<void()>{printerFunction}};
    Task task2{std::function<void()>{printerFunction}};

    workerTasks.push_back(task1);
    workerTasks.push_back(task2);
 */
    //sleep(10);

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
