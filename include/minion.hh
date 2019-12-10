#pragma once
#include <map>
#include <iostream>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <dbg_macro/dbg.h>
#include <little-utility/utility.hh>
#include "render_map.hh"
#include "map.hh"

using namespace taotsi;

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

  float move(MoveDir dir, Map &map)
  {
    // TODO: duplicated code, within map.hh
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

    if(map.grid(future_pos).landform() != Landform::Water)
    {
      if(dir != MoveDir::Random)
      {
        auto energy_consumed = map.energy_needed(position_, dir);
        if(energy_left_ >= energy_consumed)
        {
          position(future_pos);
          consume_energy(energy_consumed);
          return energy_consumed;
        }
      }
    }
    return 0.f;
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