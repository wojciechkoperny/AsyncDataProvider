#include "Dispatcher.hpp"
#include <future>


#include <iostream>
#include "TaskPool.hpp"
#include "Task.hpp"

namespace vanilla::threads
{
    Dispatcher::Dispatcher(): mDataCache(std::make_unique<DataCache>()), mTaskPool(std::make_unique<TaskPool>()) {}

    Dispatcher::~Dispatcher() {}

    std::future<std::vector<uint8_t>> Dispatcher::RequestDataById(const uint16_t id)
    {
        std::promise<std::vector<uint8_t>> promise;
        std::future<std::vector<uint8_t>> future = promise.get_future();
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
            //Task Task()
            mTaskPool->enqueTask(Task(std::move(promise),id));
        } 
        return future;
    }

} // namespace vanilla::threads