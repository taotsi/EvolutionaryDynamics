#include "argparse/argparse.hpp"
#include "dbg_macro/dbg.h"
#include "world.hh"
#include "config.hh"

int main(int argc, char** argv)
{
  ed::Config config{"../config.json"};
  ed::World world{config};
  world.loop();

  return 0;
}
