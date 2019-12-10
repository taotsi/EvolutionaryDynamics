#include <catch2/catch.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "map.hh"

using namespace ed;

TEST_CASE("set grid", "map")
{

}

TEST_CASE("energy to consume", "map")
{
  ed::Map map{100, 100};
  sf::Vector2f origin{10, 10};
  REQUIRE(map.energy_needed(origin, MoveDir::U) == 1.f);
  REQUIRE(map.energy_needed(origin, MoveDir::UR) == sqrtf(2));
}