#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <main.hpp>

struct sigaction sa;

void *printerFunction(void *a)
{
    (void)a;
    std::cout << "\nprinterFunction1: \n";
}
void Task::print()
{
    std::cout << "print z obiektu\n";
}

void Task::print2()
{
    std::cout << "ciagle zyje\n";
}

Task::Task(std::function<void *(void *)> threadTask)
{
    int a(5);
    threadTask;
    std::cout << "hello from contructor\n";
    m_threadTask = threadTask;
    m_threadTask(&a);
    //(void)pthread_create(&m_threadID, NULL, threadTask.target, NULL);
    //(void)pthread_create(&thread_fun2, NULL, &task_run2, &a);
    //(void)pthread_join(thread_fun2, NULL);
}

Task::~Task()
{
    //std::cout << "Hello from destructor!\n";
    //(void)pthread_cancel(thread_fun1);
    //(void)pthread_cancel(thread_fun2);
}

void SigintHandler(int a)
{
    std::cout << "\nTERMINATION KEY DETECT: " << a << "\n";
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
        workerTasks.push_back(Task{std::function<void *(void *)>{printerFunction}});
        workerTasks[i].print();
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
