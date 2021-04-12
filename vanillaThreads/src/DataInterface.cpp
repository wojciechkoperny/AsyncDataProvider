#include <DataInterface.hpp>
#include <Dispatcher.hpp>

namespace vanilla::threads
{
    DataInterface::DataInterface() : mDispatcher(std::make_unique<Dispatcher>()) {}

    DataInterface::~DataInterface() {}

    std::future<std::vector<uint8_t>> DataInterface::RequestDataById(const uint16_t id)
    {
        return mDispatcher->RequestDataById(id);
    }

    std::future<uint16_t> DataInterface::EmplaceData(const std::vector<uint8_t> &v)
    {
        // (void)v;
        // return mDispatcher->RequestDataById(5);
        return mDispatcher->EmplaceData(v);
    }

} // namespace vanilla::threads
