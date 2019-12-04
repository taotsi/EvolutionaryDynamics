#pragma once
#include <map>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <dbg_macro/dbg.h>
#include <little-utility/utility.hh>
#include "render_map.hh"
#include "map.hh"

using namespace taotsi;

namespace ed
{

enum class MoveDir
{
  U,
  UR,
  R,
  DR,
  D,
  DL,
  L,
  UL,
  Random
};

class Minion
{
public:
  Minion(sf::Vector2f pos)
    : position_{pos}, sprite_{{RenderMap::SPRITE_SIZE, RenderMap::SPRITE_SIZE}}
  {
    sprite_.setFillColor({0, 0, 180});
    position(pos);
  }

   void move(MoveDir dir, Map &map)
  {
    static std::map<MoveDir, sf::Vector2f> dirs{
      {MoveDir::U, {0.f, 1.f}},
      {MoveDir::UR, {1.f, 1.f}},
      {MoveDir::R, {1.f, 0.f}},
      {MoveDir::DR, {1.f, -1.f}},
      {MoveDir::D, {0.f, -1.f}},
      {MoveDir::DL, {-1.f, -1.f}},
      {MoveDir::L, {-1.f, 0.f}},
      {MoveDir::UL, {-1.f, 1.f}},
    };
    sf::Vector2f future_pos;
    if(dir != MoveDir::Random)
    {
      future_pos = position_ + dirs[dir];
    }
    else
    {
      auto r = Rand::int_random_dice(0, 7);
      auto dir = dirs.begin();
      std::advance(dir, r());
      future_pos = position_ + dir->second;
    }

    if(!map.is_obstacle(future_pos))
    {
      position(future_pos);
    }
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

  void position(sf::Vector2f pos)
  {
    position_ = pos;
    auto render_pos = pos * RenderMap::GRID_SIZE + sf::Vector2f{RenderMap::WIDTH_OFFSET + 5, RenderMap::HEIGHT_OFFSET + 7};
    sprite_.setPosition(render_pos);
  }
};

}