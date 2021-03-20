#include <stdio.h>
#include <iostream>
#include <utility>
#include "Task.hpp"

namespace vanilla::threads
{
    Task::Task()
    {
        mTaskType = TypeBase;
    }
    Task::~Task() {}
    TaskType_t Task::getType()
    {
        return mTaskType;
    }

    TaskGetData::TaskGetData(std::promise<std::vector<uint8_t>> promise, uint16_t id, std::function<void(uint16_t, std::vector<uint8_t> &)> pf)
    {
        mPromise = std::move(promise);
        mId = id;
        mAddToCache = pf;
        mTaskType = TypeGetData;
    }
    TaskGetData::~TaskGetData() {}

    TaskGetData::TaskGetData(TaskGetData &&t) noexcept
    {
        mId = t.mId;
        mPromise = std::move(t.mPromise);
        mAddToCache = t.mAddToCache;
        mTaskType = TypeGetData;
    }
    TaskGetData &TaskGetData::operator=(TaskGetData &&t) noexcept
    {
        // Self-assignment detection
        if (&t == this)
        {
            return *this;
        }
        mId = t.mId;
        mPromise = std::move(t.mPromise);
        mAddToCache = t.mAddToCache;
        mTaskType = TypeGetData;
        return *this;
    }

    std::promise<std::vector<uint8_t>> TaskGetData::getPromise()
    {
        return std::move(mPromise);
    }

    uint16_t TaskGetData::getId()
    {
        return mId;
    }

    TaskPutData::TaskPutData(std::promise<uint16_t> promise, std::vector<uint8_t> v, std::function<void(uint16_t, std::vector<uint8_t>)> pf)
    {
        mPromise = std::move(promise);
        mVector = v;
        mAddToCache = pf;
        mTaskType = TypePutData;
    }
    TaskPutData::~TaskPutData() {}

    TaskPutData::TaskPutData(TaskPutData &&t) noexcept
    {
        mVector = t.mVector;
        mPromise = std::move(t.mPromise);
        mAddToCache = t.mAddToCache;
        mTaskType = TypePutData;
    }
    TaskPutData &TaskPutData::operator=(TaskPutData &&t) noexcept
    {
        // Self-assignment detection
        if (&t == this)
        {
            return *this;
        }
        mVector = t.mVector;
        mPromise = std::move(t.mPromise);
        mAddToCache = t.mAddToCache;
        mTaskType = TypePutData;
        return *this;
    }

    std::promise<uint16_t> TaskPutData::getPromise()
    {
        return std::move(mPromise);
    }

    std::vector<uint8_t> TaskPutData::getVector()
    {
        return mVector;
    }
}
