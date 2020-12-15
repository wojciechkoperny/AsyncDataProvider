#ifndef VTHREADS_HPP
#define VTHREADS_HPP

#include <functional>

class Task
{
private:
    pthread_t m_threadID;
    std::function<void *(void *)> m_threadTask;

public:
    Task(std::function<void *(void *)> threadTask, void *arg);
    ~Task();

    void joinTask();

    void detachTask();

    void *run(void *arg);

    void print();
};

#endif

/*
-umiesc klase w innym pliku nazwana tak jak klsa
-doczytac functional
*/