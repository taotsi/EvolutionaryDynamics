cmake_minimum_required(VERSION 3.15)

project("Evolutionary Dynamics" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(include_dir ${PROJECT_SOURCE_DIR}/include)
set(extern_include_dir ${PROJECT_SOURCE_DIR}/extern)
set(imgui_include_dir ${PROJECT_SOURCE_DIR}/extern/imgui)

if(MSVC)
  set(sfml_include_dir ${PROJECT_SOURCE_DIR}/extern/SFML/SFML-2.5.1-win/include/)
  set(sfml_lib_dir ${PROJECT_SOURCE_DIR}/extern/SFML/SFML-2.5.1-win/lib)
else()
  set(sfml_include_dir ${PROJECT_SOURCE_DIR}/extern/SFML/SFML-2.5.1-linux/include/)
  set(sfml_lib_dir ${PROJECT_SOURCE_DIR}/extern/SFML/SFML-2.5.1-win/lib)
endif(MSVC)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(
  NAME test_evolutionary_dynamics
  COMMAND $<TARGET_FILE:test_evolutionary_dynamics> --success
)