#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <dbg_macro/dbg.h>
#include "nlohmann/json.hpp"
#include "map.hh"
#include "config.hh"

using json = nlohmann::json;

namespace ed
{

class World
{
public:
  World(Config &config)
    : config_{config}, map_{config.map_width, config.map_height, (config.resolution_width - Map::WIDTH_OFFSET) /config.map_width},
      test_circle_{50}
  {
    test_circle_.setFillColor(sf::Color(100, 250, 50));
  }
  void loop()
  {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // TODO: set after initializing window
    sf::RenderWindow window{sf::VideoMode(config_.resolution_width, config_.resolution_height), "Evolution Dynamics", sf::Style::Default, settings};
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    configure_imgui_style();

    sf::Clock render_clock;

    while (window.isOpen())
    {
      process_event(window);

      ImGui::SFML::Update(window, render_clock.restart());
      window.clear(sf::Color{20, 20, 20});

      ImGui::ShowDemoWindow();

      update(game_clock_);
      render(window);

      ImGui::SFML::Render(window);
      window.display();
    }

    ImGui::SFML::Shutdown();
  }

private:
  Config config_;
  Map map_;
  sf::Clock game_clock_;
  int turn_duration_ = 500; // ms // TODO: settable by user
  bool manual_turn_ = false; // TODO: user
  sf::CircleShape test_circle_;

  void configure_imgui_style()
  {
    auto &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("Monaco.ttf", 100.0f);
    io.FontDefault = io.Fonts->Fonts[0];
    io.FontDefault->Scale = 2.0f;

    ImGui::StyleColorsLight();
  }

  void process_event(sf::RenderWindow &window)
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      switch(event.type)
      {
        case sf::Event::Closed:
        {
          window.close();
          break;
        }
        case sf::Event::KeyPressed:
        {
          if(event.key.code == sf::Keyboard::Space)
          {
            if(manual_turn_ == false)
            {
              manual_turn_ = true;
            }
            else
            {
              manual_turn_ = false;
              game_clock_.restart();
            }
          }
        }
        default:
        {
          assert(false);
        }
      }
    }
  }
  void update(sf::Clock &clock)
  {
    if(!manual_turn_)
    {
      if(clock.getElapsedTime().asMilliseconds() >= turn_duration_)
      {
        auto p = test_circle_.getPosition();
        test_circle_.setPosition(p + sf::Vector2f{20, 10});
        clock.restart();
      }
    }
  }
  void render(sf::RenderWindow &window)
  {
    map_.render(window);
    window.draw(test_circle_);
  }
};

}