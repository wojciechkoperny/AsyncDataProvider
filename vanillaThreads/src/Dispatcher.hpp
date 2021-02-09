#ifndef VANILLATHREADS_SRC_DISPATCHER
#define VANILLATHREADS_SRC_DISPATCHER

#include <DataInterface.hpp>
#include <DataCache.hpp>
#include <vector>

namespace vanilla::threads
{
    class Dispatcher
    {
    public:
        Dispatcher();
        virtual ~Dispatcher();
        std::future<std::vector<uint8_t>> RequestDataById(const uint16_t id);
    };

} // namespace vanilla::threads

#endif /* VANILLATHREADS_SRC_DISPATCHER */
