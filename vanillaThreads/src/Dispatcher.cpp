#include "Dispatcher.hpp"
#include <future>


#include <iostream>

namespace vanilla::threads
{
    Dispatcher::Dispatcher() {}

    Dispatcher::~Dispatcher() {}

    std::future<std::vector<uint8_t>> Dispatcher::RequestDataById(const uint16_t id)
    {
        std::promise<std::vector<uint8_t>> promise;
        (void)id;
        //std::cout << "witam z dispachera KURLA\n";
        if (id <= 123u)
        {
            
            promise.set_value(std::vector<uint8_t>{'a', 'b', 'c'});
        }
        else
        {
            promise.set_exception(std::make_exception_ptr(std::runtime_error{"Invalid id, must be <= 123"}));
        } 
        return promise.get_future();
    }

} // namespace vanilla::threads