#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ed
{

class Map
{
public:
  Map(float w, float h, float size)
    : width_{w}, height_{h}, grid_size_{size}
  {
    for (int i = 0; i <= width_; i++)
    {
      auto line = sf::RectangleShape{sf::Vector2f{LINE_WIDTH, height_ * grid_size_}};
      line.setPosition(width_offset + i * grid_size_, height_offset);
      lines_.emplace_back(line);
    }
    for (int i = 0; i < height_; i++)
    {
      
    }
  }
  void render(sf::RenderWindow &window)
  {
    for(const auto &l : lines_)
    {
      window.draw(l);
    }
  }
private:
  std::vector<sf::RectangleShape> lines_;
  float width_offset = 20;
  float height_offset = 20;
  float width_ = 10;
  float height_ = 5;
  float grid_size_ = 5; // pixel
  static constexpr float LINE_WIDTH = 10;
};

}