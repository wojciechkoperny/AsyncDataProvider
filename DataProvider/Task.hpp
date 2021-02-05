#ifndef TASK_HPP
#define TASK_HPP
#include <future>

template <class T>
class Task
{
private:
std::promise<T> m_promise

public:
    Task(std::promise<T> promise):m_promise{promise}
    {
    }

    startTask()
    {
        
    }
};

#endif
