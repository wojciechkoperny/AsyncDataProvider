#include "Dispatcher.hpp"
#include <future>


#include <iostream>
#include "TaskPool.hpp"

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

        std::optional<std::vector<uint8_t>> m_valueCached (mDataCache->getData(id));
        if (m_valueCached) 
        {
            promise.set_value(m_valueCached.value());
        }
        else
        {
            //CREATE NEW TASK AND STORE IT IN TASK POOL
            //but where to store this task pool instance? in dispacher as unique pointer? 
        }
        
        
        return promise.get_future();
    }

} // namespace vanilla::threads