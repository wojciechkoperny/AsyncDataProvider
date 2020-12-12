#ifndef MAIN_HPP
#define MAIN_HPP

#include <functional>

class Task
{
private:
    pthread_t m_threadID;
    std::function<void *(void *)> m_threadTask;

public:
    Task(std::function<void *(void *)> threadTask);
    ~Task();

    void *run(void *arg);

    void print();

    void print2();
};

#endif

/*
-umiesc klase w innym pliku nazwana tak jak klsa
-doczytac functional
*/