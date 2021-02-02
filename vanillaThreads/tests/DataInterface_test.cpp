#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

TEST_CASE("Dummy test")
{
    CHECK(2 + 2 == 4);
}

TEST_CASE("Failing test")
{
    CHECK(2 + 2 * 2 == 8);
}