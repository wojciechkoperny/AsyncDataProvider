#include "DataCache.hpp"
#include <stdio.h>
#include <iostream>

namespace vanilla::threads
{
    DataCache::DataCache():mMapCached{ {0,{'q'}}, {1,{'w','a','r'}}, {2,{'n','e','v','e','r'}}, {3,{'c','h','a','n','g','e','s'}} } {}  //just for testing
    DataCache::~DataCache() {}

    std::optional<std::vector<uint8_t>> DataCache::getData(uint16_t id)
    {
        auto search = mMapCached.find(id);
        if (search != mMapCached.end())
        {
            std::cout << "Cache Hit: " << search->first << "! \n";
            return std::optional<std::vector<uint8_t>>{search->second};
        }
        else
        {
            std::cout << "Cache Miss!\n";
            return std::nullopt;
        }
    }

    void DataCache::putData(uint16_t id, std::vector<uint8_t> &Data)
    {
        std::cout << "Add to Cache!\n";
        mMapCached.try_emplace(id, Data);
    }

}
