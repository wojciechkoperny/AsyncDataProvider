#include <DataInterface.hpp>
#include <Dispatcher.hpp>
#include <DataCache.hpp>

namespace vanilla::threads
{
    DataInterface::DataInterface() : mDispatcher(std::make_unique<Dispatcher>()), mDataCache(std::make_unique<DataCache>()) {}

    DataInterface::~DataInterface() {}

    std::future<std::vector<uint8_t>> DataInterface::RequestDataById(const uint16_t id)
    {
        return  mDispatcher->RequestDataById(id);
    }

} // namespace vanilla::threads
