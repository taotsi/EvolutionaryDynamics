#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <map>
#include "obstacle.hh"

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

enum class Landform
{
  Land,
  Water
};

class Grid
{
public:
  Grid(){}
  Grid(Landform landform)
    : landform_{landform}
  {
    switch(landform)
    {
      case Landform::Land:
      {
        energy_to_pass_ = 1.f;
        break;
      }
      case Landform::Water:
      {
        energy_to_pass_ = 1000.f;
        break;
      }
      default:
      {
      }
    }
  }
  Landform landform()
  {
    return landform_;
  }
  float unit_energy_to_pass()
  {
    return energy_to_pass_;
  }
private:
  float energy_to_pass_ = 1.f;
  Landform landform_ = Landform::Land;
};

// TODO: use flyweight, when there's texture
class Map
{
public:
  Map(float width, float height)
    : width_{width}, height_{height}
  {
    std::vector<Grid> temp_column(height);
    for(float h = 0; h < width; h += 1.f)
    {
      grids_.push_back(temp_column);
    }
    for(float w = 0; w < width; w += 1.f)
    {
      obstacles_.emplace_back(sf::Vector2f{w, 0.f});
      obstacles_.emplace_back(sf::Vector2f{w, height -1.f});
      grids_[static_cast<size_t>(w)][0] = Grid{Landform::Water};
      grids_[static_cast<size_t>(w)][static_cast<size_t>(height-1)] = Grid{Landform::Water};
    }
    for(float h = 1; h < height_ - 1.f; h += 1.f)
    {
      obstacles_.emplace_back(sf::Vector2f{0.f, h});
      obstacles_.emplace_back(sf::Vector2f{width - 1.f, h});
      grids_[0][static_cast<size_t>(h)] = Grid{Landform::Water};
      grids_[static_cast<size_t>(width-1)][static_cast<size_t>(h)] = Grid{Landform::Water};
    }
  }
  const std::vector<Obstacle>& obstacles()
  {
    return obstacles_;
  }
  Grid grid(sf::Vector2f pos)
  {
    return grids_[static_cast<size_t>(pos.x)][static_cast<size_t>(pos.y)];
  }
  float energy_needed(sf::Vector2f origin, MoveDir dir)
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
    auto origin_energy = grid(origin).unit_energy_to_pass();
    auto destination_energy = grid(origin+dirs[dir]).unit_energy_to_pass();
    auto distance = sqrtf(powf(dirs[dir].x, 2) + powf(dirs[dir].y, 2));
    auto energy = (destination_energy + destination_energy) / 2.f * distance;
    return energy;
  }
private:
  float width_ = 1.f;
  float height_ = 1.f;
  std::vector<Obstacle> obstacles_; // TODO: deprecate it, use grids instead
  std::vector<std::vector<Grid>> grids_;
};

}