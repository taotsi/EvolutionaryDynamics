#include "argparse/argparse.hpp"
#include "dbg_macro/dbg.h"
#include "world.hh"

int main(int argc, char** argv)
{
  ed::World world;
  world.loop();

  return 0;
}
