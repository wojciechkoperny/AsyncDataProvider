#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

void* task_run1 (void *arg)
{
    (void)arg;
    static int ilosc=0;
    while(1)
    {
        std::cout<<"\033[1;31mtask1\033[0m___"<<ilosc<<"\n";
        ilosc++;     
        sleep(1);
    }
}
void* task_run2 (void *arg)
{
    static int ilosc=0;
    while(1)
    {
        std::cout<<"task2___"<<ilosc<<"\n";
        ilosc++;
        sleep(*(static_cast<unsigned int*>(arg)));
    }
}


class Task
{
public:
    static pthread_t thread_fun1, thread_fun2;
    Task(int a = 2)
    {
        std::cout<<"hello from contructor\n";

        (void)pthread_create(&thread_fun1, NULL, &task_run1, NULL);
        (void)pthread_create(&thread_fun2, NULL, &task_run2, &a);

        (void)pthread_join(thread_fun1, NULL);
        (void)pthread_join(thread_fun2, NULL);

    }
    ~Task()
    {
        std::cout<<"Hello from destructor!\n";
        (void)pthread_cancel(thread_fun1);
        (void)pthread_cancel(thread_fun2);
    }
};

pthread_t Task::thread_fun1, Task::thread_fun2;

void SigintHandler(int a)
{
    std::cout<<"\nTERMINATION KEY DETECT: " <<a <<"\n";
    (void)pthread_cancel(Task::thread_fun1);
    (void)pthread_cancel(Task::thread_fun2);
} 


int main(int argc, char *argv[])
{
    int n = 2;
    if (argc >1)
    {
        n = atoi(argv[1]);
    }
    std::cout<<"Start\n";

    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SigintHandler;
    (void)sigaction(SIGINT, &sa, NULL);

    Task task{n};

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
*/
