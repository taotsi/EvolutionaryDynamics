#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <dbg_macro/dbg.h>
#include "render_map.hh"

namespace ed
{

class Minion
{
public:
  Minion(sf::Vector2f pos)
    : position_{pos}, sprite_{{RenderMap::SPRITE_SIZE, RenderMap::SPRITE_SIZE}}
  {
    sprite_.setFillColor({0, 0, 180});
    position(pos);
  }
  void position(sf::Vector2f pos)
  {
    position_ = pos;
    auto render_pos = pos * RenderMap::GRID_SIZE + sf::Vector2f{RenderMap::WIDTH_OFFSET + 5, RenderMap::HEIGHT_OFFSET + 7};
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
};

}