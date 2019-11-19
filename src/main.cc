#include "argparse/argparse.hpp"
#include "dbg-marco/dbg.h"

int main(int argc, char** argv)
{
  argparse::ArgumentParser program("Evolutionary Dynamics");
  program.add_argument("-v")
    .help("Print version")
    .default_value(false)
    .implicit_value(true);

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    exit(0);
  }

  if (program["-v"] == true) {
    std::cout << "Version: 0.1\n";
  }
  int x = 42;
  dbg(x == 42);
  return 0;
}