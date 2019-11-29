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
    : config_{config}, map_{config.map_width, config.map_height, (config.resolution_width - Map::WIDTH_OFFSET) /config.map_width}
  {
    //
  }
  void loop()
  {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // TODO: set after initializing window
    sf::RenderWindow window(sf::VideoMode(config_.resolution_width, config_.resolution_height), "Evolution Dynamics", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    configure_imgui_style();

    sf::Clock deltaClock;
    while (window.isOpen())
    {
      process_input_event(window);

      ImGui::SFML::Update(window, deltaClock.restart());
      window.clear(sf::Color{20, 20, 20});

      ImGui::ShowDemoWindow();

      map_.render(window);

      ImGui::SFML::Render(window);
      window.display();
    }

    ImGui::SFML::Shutdown();
  }

private:
  Map map_;
  Config config_;

  void configure_imgui_style()
  {
    auto &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("Monaco.ttf", 100.0f);
    io.FontDefault = io.Fonts->Fonts[0];
    io.FontDefault->Scale = 2.0f;

    ImGui::StyleColorsLight();
  }

  void process_input_event(sf::RenderWindow &window)
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed)
      {
          window.close();
      }
    }
  }
};

}