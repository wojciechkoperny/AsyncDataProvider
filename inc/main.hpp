#ifndef MAIN_HPP
#define MAIN_HPP
 
class Task
{
public:
    static pthread_t thread_fun1, thread_fun2;

    Task(int a);
    ~Task();
};
 
#endif