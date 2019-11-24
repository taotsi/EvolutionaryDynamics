# CMake generated Testfile for 
# Source directory: E:/EvolutionaryDynamics
# Build directory: E:/EvolutionaryDynamics/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_evolutionary_dynamics "E:/EvolutionaryDynamics/out/build/x64-Debug/test_evolutionary_dynamics.exe" "--success")
set_tests_properties(test_evolutionary_dynamics PROPERTIES  _BACKTRACE_TRIPLES "E:/EvolutionaryDynamics/CMakeLists.txt;16;add_test;E:/EvolutionaryDynamics/CMakeLists.txt;0;")
subdirs("src")
subdirs("tests")
