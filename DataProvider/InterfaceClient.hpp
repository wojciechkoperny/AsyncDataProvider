#ifndef INTERFACE_CLIENT_HPP
#define INTERFACE_CLIENT_HPP

#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

template <class T>

class Interface
{
    public:
    virtual std::promise<T> RequestDataById(T id) = 0;
};

#endif