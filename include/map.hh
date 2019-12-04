#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "obstacle.hh"

namespace ed
{

struct GridState
{
  bool is_obstacle = false;
};

// TODO: use flyweight, when there's texture
class Map
{
public:
  Map(float width, float height)
    : width_{width}, height_{height}
  {
    std::vector<GridState> temp_column(height);
    for(float h = 0; h < width; h += 1.f)
    {
      grids_.push_back(temp_column);
    }
    for(float w = 0; w < width; w += 1.f)
    {
      obstacles_.emplace_back(sf::Vector2f{w, 0.f});
      obstacles_.emplace_back(sf::Vector2f{w, height -1.f});
      grids_[static_cast<size_t>(w)][0].is_obstacle = true;
      grids_[static_cast<size_t>(w)][static_cast<size_t>(height-1)].is_obstacle = true;
    }
    for(float h = 1; h < height_ - 1.f; h += 1.f)
    {
      obstacles_.emplace_back(sf::Vector2f{0.f, h});
      obstacles_.emplace_back(sf::Vector2f{width - 1.f, h});
      grids_[0][static_cast<size_t>(h)].is_obstacle = true;
      grids_[static_cast<size_t>(width-1)][static_cast<size_t>(h)].is_obstacle = true;
    }
  }
  const std::vector<Obstacle>& obstacles()
  {
    return obstacles_;
  }
  bool is_obstacle(sf::Vector2f pos)
  {
    return grids_[static_cast<size_t>(pos.x)][static_cast<size_t>(pos.y)].is_obstacle;
  }
private:
  float width_ = 1.f;
  float height_ = 1.f;
  std::vector<Obstacle> obstacles_;
  std::vector<std::vector<GridState>> grids_;
};

}