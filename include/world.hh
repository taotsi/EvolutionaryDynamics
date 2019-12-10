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
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include "render_map.hh"
#include "config.hh"
#include "minion.hh"
#include "obstacle.hh"
#include "command.hh"
#include "map.hh"

using namespace std::chrono_literals;

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
    spawn_minions();

    // TEMP:
    for(float w = 0; w < config.map_width; w += 1.f)
    {
      map_.set_grid({w, 0.f}, Landform::Water);
      map_.set_grid({w, config.map_height - 1.f}, Landform::Water);
    }
    for(float h = 1; h < config.map_height - 1.f; h += 1.f)
    {
      map_.set_grid({0.f, h}, Landform::Water);
      map_.set_grid({config.map_width - 1.f, h}, Landform::Water);
    }
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
  int turn_duration_ = 250; // ms // TODO: settable by user
  bool manual_turn_ = true;
  bool next_turn_ = false;
  std::vector<Minion> minions_;
  std::vector<std::queue<std::shared_ptr<Command>>> commands_;

  void spawn_minions()
  {
    size_t population = 2;
    commands_.resize(population);
    for(size_t i = 0; i < population; i++)
    {
      minions_.emplace_back(sf::Vector2f{static_cast<float>(10+i), static_cast<float>(10+i)});
      emit_command<CmdMoveRight>(i);
      emit_command<CmdMoveRight>(i);
      emit_command<CmdMoveRight>(i);
      emit_command<CmdMoveRight>(i);
      emit_command<CmdMoveRight>(i);
    }
  }

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
            // TODO: how about two keys pressed at the same time?
            case sf::Keyboard::Right:
            {
              emit_command<CmdMoveRight>(0);
              break;
            }
            case sf::Keyboard::Left:
            {
              emit_command<CmdMoveLeft>(0);
              break;
            }
            case sf::Keyboard::Up:
            {
              emit_command<CmdMoveUp>(0);
              break;
            }
            case sf::Keyboard::Down:
            {
              emit_command<CmdMoveDown>(0);
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
  void emit_command(size_t minion_id)
  {
    commands_[minion_id].push(std::make_shared<C>());
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
  }

  void next_turn()
  {
    auto n_minion = minions_.size();
    for (size_t i = 0; i < n_minion; i++)
    {
      if(commands_[i].empty())
      {
        continue;
      }
      while(!commands_[i].empty())
      {
        auto energy_consumed = commands_[i].back()->execute(minions_[i], map_);
        commands_[i].pop();
        if(energy_consumed != 0)
        {
          minions_[i].consume_energy(energy_consumed);
        }
        else
        {
          break;
          // TODO: execution failed, handle commands afterwards
        }
      }
      minions_[i].restore_energy();
    }
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
