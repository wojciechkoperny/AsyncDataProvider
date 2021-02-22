#ifndef VANILLATHREADS_SRC_TASK_HPP
#define VANILLATHREADS_SRC_TASK_HPP

#include <optional>
#include <vector>

#include <future>

namespace vanilla::threads
{
    class Task
    {
    public:
        Task(std::promise<std::vector<uint8_t>> promise, uint16_t id);
        virtual ~Task();
        Task(Task &&t)noexcept;
        Task& operator=(Task&& t) noexcept;

        std::promise<std::vector<uint8_t>> getPromise();
        uint16_t getId();

    private:
        std::promise<std::vector<uint8_t>> mPromise;
        uint16_t mId;
    };

}

#endif