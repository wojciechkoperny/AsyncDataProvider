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
        //Auto_ptr4(Auto_ptr4&& a) noexcept;
        //std::optional<std::vector<uint8_t>> getData(uint16_t id);
        //void putData(uint16_t id, std::vector<uint8_t> &Data);

    private:
        std::promise<std::vector<uint8_t>> mPromise;
        uint16_t mId;
    };

}

#endif