#pragma once
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace ed
{

struct Config
{
  Config(std::string path) // TODO: use std::path
  {
    std::ifstream ifs{path};
    json conf;
    ifs >> conf;
    resolution_width = conf["resolution"]["width"];
    resolution_height = conf["resolution"]["height"];
    map_width = conf["map_size"]["width"];
    map_height = conf["map_size"]["height"];
  }

  size_t resolution_width;
  size_t resolution_height;
  size_t map_width;
  size_t map_height;
};

}