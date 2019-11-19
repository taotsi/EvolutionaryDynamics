cmake_minimum_required(VERSION 3.16)

project("Evolutionary Dynamics" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(include_dir ${PROJECT_SOURCE_DIR}/include)
set(extern_include_dir ${PROJECT_SOURCE_DIR}/extern)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(
  NAME test_evolutionary_dynamics
  COMMAND $<TARGET_FILE:test_evolutionary_dynamics> --success
)