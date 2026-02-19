#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include "DataInterface.hpp"
#include <Dispatcher.hpp>

/* class Mock
{
public:
  //MAKE_MOCK2(foo, bool(int, std::string&),override);
  //MAKE_MOCK1(bar, bool(int),override);
  MAKE_MOCK1(RequestDataById, std::future<std::vector<uint8_t>>(const uint16_t id));
  //MAKE_MOCK0(Data, void()); // not from Interface
}; */

TEST_CASE("Dummy test")
{
    CHECK(2 + 2 == 4);
}

/* TEST_CASE("Failing test111")
{
    CHECK(2 + 2 * 2 == 8);
}

TEST_CASE("elo nowy test")
{
    CHECK(2*2 == 2);
} */
TEST_CASE("feature valid?")
{
    vanilla::threads::DataInterface dataInterface{};
    
/*     REQUIRE_CALL(dataInterface, DataInterface(ANY(int)))     // expect call to m.bar(int)
    .LR_SIDE_EFFECT(local_var = _1)  // set captured variable to value of param
    .RETURN(_1 > 0)                  // return value depending on param value
    .TIMES(AT_LEAST(1));             // can be called several times */
    auto retFuture = dataInterface.RequestDataById(0);
    REQUIRE(retFuture.valid());
}

TEST_CASE("feature valid with id 100?")
{
    vanilla::threads::DataInterface dataInterface{};
    
/*     REQUIRE_CALL(dataInterface, DataInterface(ANY(int)))     // expect call to m.bar(int)
    .LR_SIDE_EFFECT(local_var = _1)  // set captured variable to value of param
    .RETURN(_1 > 0)                  // return value depending on param value
    .TIMES(AT_LEAST(1));             // can be called several times */
    auto retFuture = dataInterface.RequestDataById(100);
    REQUIRE(retFuture.valid());
}

TEST_CASE("feature valid with id 150?")
{
    vanilla::threads::DataInterface dataInterface{};
    auto retFuture = dataInterface.RequestDataById(150);
    REQUIRE(retFuture.valid());
}
