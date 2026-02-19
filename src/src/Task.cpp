#include <stdio.h>
#include <iostream>
#include <utility>
#include "Task.hpp"

namespace vanilla::threads
{
    Task::Task(std::promise<std::vector<uint8_t>> promise, uint16_t id, std::function<void(uint16_t, std::vector<uint8_t>&)> pf)
    {
        mPromise = std::move(promise);
        mId = id;
        mAddToCache = pf;
    }
    Task::~Task() {}

    Task::Task(Task &&t)noexcept
    {
        mId=t.mId;
        mPromise = std::move(t.mPromise);
        mAddToCache=t.mAddToCache;
    }
    Task& Task::operator=(Task&& t) noexcept
	{
		// Self-assignment detection
		if (&t == this)
        {
		    return *this;
        }
        mId = t.mId;
        mPromise = std::move(t.mPromise);
        mAddToCache = t.mAddToCache;
		return *this;
	}

    std::promise<std::vector<uint8_t>> Task::getPromise()
    {
        return std::move(mPromise);
    }

    uint16_t Task::getId()
    {
        return mId;
    }
    
}
