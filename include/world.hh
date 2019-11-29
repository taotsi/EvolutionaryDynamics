#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <dbg_macro/dbg.h>
#include "map.hh"

namespace ed
{

class World
{
public:
  World(float w, float h)
    : map_{w, h, 2560/w}
  {
    //
  }
  void loop()
  {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    // TODO: user config resolution
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "Evolution Dynamics", sf::Style::Default, settings);
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

      sf::CircleShape shape(200, 100);
      shape.setFillColor(sf::Color(150, 50, 250));
      shape.setPosition({200.f, 200.f});
      window.draw(shape);

      map_.render(window);

      ImGui::SFML::Render(window);
      window.display();
    }

    ImGui::SFML::Shutdown();
  }

private:
  Map map_;

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