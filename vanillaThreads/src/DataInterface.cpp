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

    std::future<std::vector<uint8_t>> DataInterface::RequestDataById(const uint16_t id)
    {
        return mDispatcher->RequestDataById(id);
    }

    std::future<uint16_t> DataInterface::EmplaceData(const std::vector<uint8_t>)
    {
        //return mDispatcher->RequestDataById(id);
    }

} // namespace vanilla::threads
