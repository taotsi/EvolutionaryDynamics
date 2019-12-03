#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <dbg_macro/dbg.h>
#include "map.hh"

namespace ed
{

class Minion
{
public:
  Minion(sf::Vector2f pos)
    : position_{pos}, sprite_{{SPRITE_SIZE, SPRITE_SIZE}}
  {
    sprite_.setFillColor({0, 0, 200});
    position(pos);
  }
  void position(sf::Vector2f pos)
  {
    position_ = pos;
    static float GRID_SIZE = 60;
    auto render_pos = pos * GRID_SIZE + sf::Vector2f{Map::WIDTH_OFFSET + 5, Map::HEIGHT_OFFSET + 7};
    sprite_.setPosition(render_pos);
  }
  sf::Vector2f position()
  {
    return position_;
  }

  const sf::RectangleShape& sprite() const
  {
    return sprite_;
  }

private:
  sf::Vector2f position_;
  sf::RectangleShape sprite_;
  static constexpr float SPRITE_SIZE = 50;
};

}