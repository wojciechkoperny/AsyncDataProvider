#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

class Task
{
private:
    pthread_t thread_fun1, thread_fun2;
public:
    Task(/* args */)
    {
        std::cout<<"hello from contructor\n";
    }
    ~Task()
    {
        //(void)pthread_cancel(thread_fun1);
        //(void)pthread_cancel(thread_fun2);
        std::cout<<"Bye World!\n";
    }


};



int main()
{
    std::cout<<"Hello World\n";

    Task task;

    return 0;
}
