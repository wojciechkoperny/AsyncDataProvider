#include <stdio.h>
#include <iostream>
#include <utility>
#include "Task.hpp"

namespace vanilla::threads
{
    Task::Task(std::promise<std::vector<uint8_t>> promise, uint16_t id)
    {
        mPromise = std::move(promise);
        mId = id;
    }
    Task::~Task() {}

    Task::Task(Task &&t)noexcept
    {
        mId=t.mId;
        mPromise = std::move(t.mPromise);
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
		return *this;
	}

}
