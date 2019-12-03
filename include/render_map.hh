#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ed
{

class RenderMap
{
public:
  static float WIDTH_OFFSET;
  static float HEIGHT_OFFSET;
  static float GRID_SIZE;
  static float SPRITE_SIZE;

  RenderMap(size_t w, size_t h)
    : width_{static_cast<float>(w)},
      height_{static_cast<float>(h)}
  {
    for (int i = 0; i <= width_; i++)
    {
      auto line = sf::RectangleShape{sf::Vector2f{line_width_, height_ * GRID_SIZE}};
      line.setPosition(WIDTH_OFFSET + i * GRID_SIZE, HEIGHT_OFFSET);
      lines_.push_back(line);
    }
    for (int i = 0; i <= height_; i++)
    {
      auto line = sf::RectangleShape{sf::Vector2f{width_ * GRID_SIZE, line_width_}};
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

  static constexpr float line_width_ = 3;
};

}