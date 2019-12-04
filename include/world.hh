#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <dbg_macro/dbg.h>
#include <nlohmann/json.hpp>
#include <queue>
#include <memory>
#include "render_map.hh"
#include "config.hh"
#include "minion.hh"
#include "obstacle.hh"
#include "command.hh"
#include "map.hh"

namespace ed
{

class World
{
public:
  World(Config &config)
    : config_{config},
      render_map_{config.map_width, config.map_height},
      map_{config.map_width, config.map_height}
  {
    minions_.emplace_back(sf::Vector2f{10, 10});
    
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
      window.clear(sf::Color{200, 200, 200});

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
  RenderMap render_map_;
  Map map_;
  sf::Clock game_clock_;
  int turn_duration_ = 500; // ms // TODO: settable by user
  bool manual_turn_ = false;
  bool next_turn_ = false;
  std::vector<Minion> minions_;

  std::queue<std::shared_ptr<Command>> commands_;

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
          switch(event.key.code)
          {
            case sf::Keyboard::Space:
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
              break;
            }
            case sf::Keyboard::Enter:
            {
              if(!next_turn_)
              {
                next_turn_ = true;
              }
              break;
            }
            case sf::Keyboard::Right:
            {
              std::cout << "move right, nothing for now\n";
              // emit_command(CmdMoveRight{});
              break;
            }
            case sf::Keyboard::R:
            {
              emit_command<CmdMoveRandom>();
              break;
            }
            default:
            {
              std::cout << "a key is pressed, but nothing happened\n";
            }
          }
          break;
        }
        default:
        {
          assert(false);
        }
      }
    }
  }

  template<typename C>
  void emit_command()
  {
    commands_.push(std::make_shared<C>());
  }

  void update(sf::Clock &clock)
  {
    if(!manual_turn_)
    {
      if(clock.getElapsedTime().asMilliseconds() >= turn_duration_)
      {
        next_turn();
        clock.restart();
      }
    }
    else
    {
      if(next_turn_)
      {
        next_turn();
        next_turn_ = false;
      }
    }
    while(!commands_.empty())
    {
      commands_.front()->execute(minions_[0]);
      commands_.pop();
    }
  }

  void next_turn()
  {
    emit_command<CmdMoveRandom>();
  }
  void render(sf::RenderWindow &window)
  {
    render_map_.render(window);
    for(const auto &o : map_.obstacles())
    {
      window.draw(o.sprite());
    }
    for(const auto &m : minions_)
    {
      window.draw(m.sprite());
    }
  }
};

}