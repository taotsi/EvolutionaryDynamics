#include <catch2/catch.hpp>
#include <SFML/System/Vector2.hpp>
#include "command.hh"
#include "a_star.hh"
#include "map.hh"

using namespace ed;

TEST_CASE("path finding", "A*")
{
  sf::Vector2f origin{5, 5}, destination{20, 20};
  Map map{100, 100};
}