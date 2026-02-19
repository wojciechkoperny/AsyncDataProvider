#ifndef VANILLATHREADS_SRC_DATACACHE_HPP
#define VANILLATHREADS_SRC_DATACACHE_HPP

#include <optional>
#include <vector>
#include <memory>
#include <map>

namespace vanilla::threads
{
    class DataCache
    {
    public:
        DataCache();
        virtual ~DataCache();
        std::optional<std::vector<uint8_t>> getData(uint16_t id);
        void putData(uint16_t id, std::vector<uint8_t> &Data);

    private:
        std::map<uint16_t, std::vector<uint8_t>> mMapCached;
    };

}

#endif
