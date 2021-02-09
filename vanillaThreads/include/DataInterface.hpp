#ifndef VANILLATHREADS_INCLUDE_DATAINTERFACE
#define VANILLATHREADS_INCLUDE_DATAINTERFACE

#include <future>
#include <vector>
#include <memory>

namespace vanilla::threads
{
    /// Forward declaration of Dispatcher
    class Dispatcher;
    class DataCache;

    class DataInterface
    {
    public:
        DataInterface();
        virtual ~DataInterface();

        std::future<std::vector<uint8_t>> RequestDataById(const uint16_t id);

    private:
        std::unique_ptr<Dispatcher> mDispatcher;
        std::unique_ptr<DataCache> mDataCache;
    };

} // namespace vanilla::threads

#endif /* VANILLATHREADS_INCLUDE_DATAINTERFACE */
