#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ed
{

class Map
{
public:
  static constexpr float WIDTH_OFFSET = 10;
  static constexpr float HEIGHT_OFFSET = 10;
  float GRID_SIZE; // pixel
  Map(size_t w, size_t h, size_t size)
    : width_{static_cast<float>(w)},
      height_{static_cast<float>(h)},
      GRID_SIZE{static_cast<float>(size)}
  {
    for (int i = 0; i <= width_; i++)
    {
      auto line = sf::RectangleShape{sf::Vector2f{LINE_WIDTH, height_ * GRID_SIZE}};
      line.setPosition(WIDTH_OFFSET + i * GRID_SIZE, HEIGHT_OFFSET);
      lines_.push_back(line);
    }
    for (int i = 0; i <= height_; i++)
    {
      auto line = sf::RectangleShape{sf::Vector2f{width_ * GRID_SIZE, LINE_WIDTH}};
      line.setPosition(WIDTH_OFFSET, HEIGHT_OFFSET + i * GRID_SIZE);
      lines_.push_back(line);
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
  float width_ = 10;
  float height_ = 10;
  
  static constexpr float LINE_WIDTH = 3;
};

}