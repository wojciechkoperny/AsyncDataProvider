#ifndef DISPACHER_HPP
#define DISPACHER_HPP

#include <thread>
#include <future>
#include "InterfaceClient.hpp"
#include "DataCache.hpp"

template <class T>

class Dispacher : public Interface<T>
{
private:

public:
    
    std::promise<T> RequestDataById(T id)
    {
        DataCache<T> m_dataCache;
        std::optional<T> m_valueCached (m_dataCache.getData(id));
        std::promise<T> m_promised;
        if (m_valueCached) 
        {
            m_promised.set_value(m_valueCached.value());
        }
        else
        {
            //create new queued task
        }
        
        return m_promised;
    }
}; 
#endif