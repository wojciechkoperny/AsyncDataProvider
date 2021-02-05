#ifndef DATACACHE_HPP
#define DATACACHE_HPP

#include <optional>

template <class T>

class DataCache
{

public:
    std::optional<T> getData(T id)
    {
        std::cout << "cache hit\n";//cache hit
        return std::optional<T>{5};
        //return std::optional<T>.emplace
    }
};


#endif
