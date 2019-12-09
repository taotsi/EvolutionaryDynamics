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

  float move(MoveDir dir, Map &map)
  {
    static std::map<MoveDir, sf::Vector2f> dirs{
      {MoveDir::U, {0.f, -1.f}},
      {MoveDir::UR, {1.f, -1.f}},
      {MoveDir::R, {1.f, 0.f}},
      {MoveDir::DR, {1.f, 1.f}},
      {MoveDir::D, {0.f, 1.f}},
      {MoveDir::DL, {-1.f, 1.f}},
      {MoveDir::L, {-1.f, 0.f}},
      {MoveDir::UL, {-1.f, -1.f}},
    };

    auto future_pos = position_ + dirs[dir];

    float energy_consumed = 0.f;

    if(!map.is_obstacle(future_pos))
    {
      position(future_pos);
      if(dir == MoveDir::U || dir == MoveDir::D || dir == MoveDir::R || dir == MoveDir::L)
      {
        if(energy_left_ > 1.f) // TODO: hard code
        {
          consume_energy(1.f);
          energy_consumed = 1.f;
        }
      }
      else if(dir == MoveDir::UR || dir == MoveDir::DR || dir == MoveDir::DR || dir == MoveDir::UL)
      {
        if(energy_left_ > 1.414f)
        {
          consume_energy(1.414f);
          energy_consumed = 1.414f;
        }
      }
    }
    return energy_consumed;
  }

  sf::Vector2f position()
  {
    return position_;
  }

  float energy()
  {
    return energy_left_;
  }
  void consume_energy(float e)
  {
    energy_left_ -= e;
  }
  void restore_energy()
  {
    energy_left_ += 2.f; // TODO: hard code
    if(energy_left_ > 5.f)
    {
      energy_left_ = 5.f;
    }
  }

  const sf::RectangleShape& sprite() const
  {
    return sprite_;
  }

private:
  sf::Vector2f position_;
  sf::RectangleShape sprite_;
  float energy_left_ = 2.f;

  void position(sf::Vector2f pos)
  {
    position_ = pos;
    auto render_pos = pos * RenderMap::GRID_SIZE + sf::Vector2f{RenderMap::WIDTH_OFFSET + 5, RenderMap::HEIGHT_OFFSET + 7};
    sprite_.setPosition(render_pos);
  }
};

}