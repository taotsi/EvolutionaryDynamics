#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "render_map.hh"

namespace ed
{

class Obstacle
{
public:
  Obstacle(sf::Vector2f pos)
    : position_{pos}, sprite_{{50, 50}}
  {
    sprite_.setFillColor({50, 50, 50});
    auto render_pos = pos * RenderMap::GRID_SIZE + sf::Vector2f{RenderMap::WIDTH_OFFSET + 5, RenderMap::HEIGHT_OFFSET + 7};
    sprite_.setPosition(render_pos);
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