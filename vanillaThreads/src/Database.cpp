#include "Database.hpp"
#include <unistd.h>

namespace vanilla::threads
{
    Database::Database() : mDataMap{{0, {'w', 'a', 'r'}}, {1, {'w', 'a', 'r'}}, {2, {'n', 'e', 'v', 'e', 'r'}}, {3, {'c', 'h', 'a', 'n', 'g', 'e', 's'}}, {4, {'a', 'l', 'a'}}, {5, {'m', 'a'}}, {6, {'k', 'o', 't', 'a'}}, {7, {'a', 'a'}}, {8, {'o', 'n'}}, {9, {'j', 'a'}}, {10, {'t', 'e', 's', 't'}}} {}
    Database::~Database() {}

    std::vector<uint8_t> Database::getData(const uint16_t id)
    {
        sleep(2);
        if (id < mDataMap.size())
        {
            return mDataMap[id];
        }
        else
        {
            return mDataMap[10];
        }
    }

    uint16_t Database::putData(std::vector<uint8_t> v)
    {
        //std::cout << "Add to Cache!\n";
        // mDataMap.size();
        //mDataMap.emplace_hint(it, i, 'b');
        mDataMap.try_emplace(static_cast<uint16_t>(mDataMap.size() + 1), v);
        sleep(2);
        return static_cast<uint16_t>(mDataMap.size());
    }

}