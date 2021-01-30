#include <DataInterface.hpp>

#include <Dispatcher.hpp>

namespace vanilla::threads
{
    DataInterface::DataInterface() : mDispatcher(std::make_unique<Dispatcher>()) {}

    DataInterface::~DataInterface() {}

    std::future<std::vector<uint8_t>> DataInterface::RequestDataById(const uint16_t id)
    {
        std::promise<std::vector<uint8_t>> promise;

        if (id <= 123u)
        {
            promise.set_value(std::vector<uint8_t>{1u, 2u, 3u});
        }
        else
        {
            promise.set_exception(std::make_exception_ptr(std::runtime_error{"Invalid id, must be <= 123"}));
        }

        return promise.get_future();
    }

} // namespace vanilla::threads
