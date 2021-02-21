#ifndef VANILLATHREADS_SRC_DISPATCHER
#define VANILLATHREADS_SRC_DISPATCHER

#include <DataInterface.hpp>
#include <vector>
#include <memory>

#include "DataCache.hpp"
#include "TaskPool.hpp"
namespace vanilla::threads
{
    class DataCache;
    class Dispatcher
    {
    public:
        Dispatcher();
        virtual ~Dispatcher();
        std::future<std::vector<uint8_t>> RequestDataById(const uint16_t id);
    
    private:
    std::unique_ptr<DataCache> mDataCache;
    std::unique_ptr<TaskPool> mTaskPool;
    };

} // namespace vanilla::threads

#endif /* VANILLATHREADS_SRC_DISPATCHER */
