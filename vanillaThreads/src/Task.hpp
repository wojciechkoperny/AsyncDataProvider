#ifndef VANILLATHREADS_SRC_TASK_HPP
#define VANILLATHREADS_SRC_TASK_HPP

#include <optional>
#include <vector>
#include <future>
#include <functional>

namespace vanilla::threads
{
    typedef enum
    {
        TypeBase,
        TypeGetData,
        TypePutData
    } TaskType_t;

    class Task
    {
    public:
        Task();
        virtual ~Task();
        TaskType_t getType();

    protected:
        TaskType_t mTaskType;
    };

    class TaskGetData : public Task
    {
    public:
        TaskGetData(std::promise<std::vector<uint8_t>> promise, uint16_t id, std::function<void(uint16_t, std::vector<uint8_t> &)> pf);
        virtual ~TaskGetData();
        TaskGetData(TaskGetData &&t) noexcept;
        TaskGetData &operator=(TaskGetData &&t) noexcept;

        std::promise<std::vector<uint8_t>> getPromise();
        uint16_t getId();

    private:
        std::promise<std::vector<uint8_t>> mPromise;
        uint16_t mId;

    public:
        std::function<void(uint16_t, std::vector<uint8_t> &)> mAddToCache;
    };

    class TaskPutData : public Task
    {
    public:
        TaskPutData(std::promise<uint16_t> promise, std::vector<uint8_t> v, std::function<void(uint16_t, std::vector<uint8_t> &)> pf);
        virtual ~TaskPutData();
        TaskPutData(TaskPutData &&t) noexcept;
        TaskPutData &operator=(TaskPutData &&t) noexcept;

        std::promise<std::vector<uint8_t>> getPromise();
        uint16_t getVector();

    private:
        std::promise<uint16_t> mPromise;
        std::vector<uint8_t> mVector;

    public:
        std::function<void(uint16_t, std::vector<uint8_t> &)> mAddToCache;
    };

}

#endif