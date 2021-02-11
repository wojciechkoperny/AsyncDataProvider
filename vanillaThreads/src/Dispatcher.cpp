#include "Dispatcher.hpp"
#include <future>


#include <iostream>

namespace vanilla::threads
{
    Dispatcher::Dispatcher(): mDataCache(std::make_unique<DataCache>()) {}

    Dispatcher::~Dispatcher() {}

    std::future<std::vector<uint8_t>> Dispatcher::RequestDataById(const uint16_t id)
    {
        std::promise<std::vector<uint8_t>> promise;
        if (id > 123u)
        {
            promise.set_exception(std::make_exception_ptr(std::runtime_error{"Invalid id, must be <= 123"}));
        } 
        //(void)id;
        //std::cout << "witam z dispachera KURLA\n";

        //DataCache<T> m_dataCache;
        // //std::promise<T> m_promised;
        // if (m_valueCached) 
        // {
        //     m_promised.set_value(m_valueCached.value());
        // }
        // else
        // {
        //     //create new queued task
        // }
        //mDataCache->


        std::optional<std::vector<uint8_t>> m_valueCached (mDataCache->getData(id));
        if (m_valueCached) 
        {
            promise.set_value(m_valueCached.value());
        }
        else
        {
            //create new taks;
            //enque task
        }
        
        
        return promise.get_future();
    }

} // namespace vanilla::threads