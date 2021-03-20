#ifndef DATABASE_SRC_DISPATCHER
#define DATABASE_SRC_DISPATCHER

#include <vector>
#include <memory>

#include "DataCache.hpp"
#include "TaskPool.hpp"
namespace vanilla::threads
{
    class Database
    {
    public:
        Database();
        virtual ~Database();
        std::vector<uint8_t> getData(const uint16_t id);
        uint16_t putData(std::vector<uint8_t> v);

    private:
        std::map<uint16_t, std::vector<uint8_t>> mDataMap;
        };

} // namespace vanilla::threads

#endif /* DATABASE_SRC_DISPATCHER */
