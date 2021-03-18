#include "Dispatcher.hpp"
#include <future>
#include <functional>

#include <iostream>
#include "TaskPool.hpp"
#include "Task.hpp"

namespace vanilla::threads
{
    Dispatcher::Dispatcher() : mDataCache(std::make_shared<DataCache>()), mTaskPool(std::make_unique<TaskPool>()) {}

    Dispatcher::~Dispatcher() {}

    std::future<std::vector<uint8_t>> Dispatcher::RequestDataById(const uint16_t id)
    {
        std::promise<std::vector<uint8_t>> promise;
        std::future<std::vector<uint8_t>> future = promise.get_future();
        if (id > 123u)
        {
            promise.set_exception(std::make_exception_ptr(std::runtime_error{"Invalid id, must be <= 123"}));
        }

        std::optional<std::vector<uint8_t>> m_valueCached(mDataCache->getData(id));
        if (m_valueCached)
        {
            promise.set_value(m_valueCached.value());
        }
        else
        {
            //CREATE NEW TASK AND STORE IT IN TASK POOL
            std::function<void(uint16_t, std::vector<uint8_t> &)> memberOfDataCache = std::bind(&DataCache::putData, mDataCache, std::placeholders::_1, std::placeholders::_2);
            mTaskPool->enqueGetTask(TaskGetData(std::move(promise), id, memberOfDataCache));
        }
        return future;
    }

    std::future<uint16_t> Dispatcher::EmplaceData(const std::vector<uint8_t> v)
    {
        //(void)v;
        std::promise<uint16_t> promise;
        std::future<uint16_t> future = promise.get_future();
        std::function<void(uint16_t, std::vector<uint8_t> &)> memberOfDataCache = std::bind(&DataCache::putData, mDataCache, std::placeholders::_1, std::placeholders::_2);
        mTaskPool->enquePutTask(TaskPutData(std::move(promise), v, memberOfDataCache));
        //CREATE NEW TASK AND STORE IT IN TASK POOL
        //std::function<void(uint16_t, std::vector<uint8_t> &)> memberOfDataCache = std::bind(&DataCache::putData, mDataCache, std::placeholders::_1, std::placeholders::_2);
        //mTaskPool->enqueTask(Task(std::move(promise), id, memberOfDataCache));
        return future;
    }
} // namespace vanilla::threads