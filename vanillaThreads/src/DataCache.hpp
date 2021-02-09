#ifndef DATACACHE_HPP
#define DATACACHE_HPP

#include <optional>


namespace vanilla::threads
{
    class DataCache
    {
        public:
        DataCache();
        virtual ~DataCache();
       // std::optional<std::vector<uint8_t>> getData(uint16_t id);
    };

}

#endif
