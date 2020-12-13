#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <vThreads.hpp>

void Task::print()
{
    std::cout << "print z obiektu\n";
}

void Task::print2()
{
    std::cout << "ciagle zyje\n";
}
//*static_cast<std::function<void*()>*>(context);
Task::Task(std::function<void *(void *)> threadTask, void *arg)
{
    std::cout << "hello from contructor\n";
    m_threadTask = threadTask;

    typedef void *(*function_t)(void *); //http://www.cplusplus.com/forum/general/63552/
    function_t *fun_ptr = m_threadTask.target<function_t>();
    (void)pthread_create(&m_threadID, NULL, *fun_ptr, arg);
}

Task::~Task()
{
    //std::cout << "Hello from destructor!\n";
    //(void)pthread_cancel(thread_fun1);
    //(void)pthread_cancel(thread_fun2);
}

void Task::joinTask()
{
    (void)pthread_join(m_threadID, NULL);
}