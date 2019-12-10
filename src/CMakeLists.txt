add_subdirectory(imgui)

# ===== Library =====

add_library(lib_ed world.cc render_map.cc command.cc map.cc a_star.cc)

target_link_libraries(lib_ed lib_imgui)

target_include_directories(lib_ed PUBLIC ${include_dir})
target_include_directories(lib_ed PUBLIC ${extern_include_dir})
target_include_directories(lib_ed PUBLIC ${sfml_include_dir})
target_include_directories(lib_ed PUBLIC ${imgui_include_dir})

if(MSVC)
  add_definitions(-DSFML_STATIC)
  target_link_libraries(lib_ed winmm.lib)
  target_link_libraries(lib_ed opengl32.lib)
  target_link_libraries(lib_ed gdi32.lib)
  target_link_libraries(lib_ed ws2_32.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/ogg.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/vorbis.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/vorbisenc.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/vorbisfile.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/flac.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/freetype.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/sfml-system-s.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/sfml-network-s.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/sfml-window-s.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/sfml-audio-s.lib)
  target_link_libraries(lib_ed ${sfml_lib_dir}/sfml-graphics-s.lib)
else() # linux
  find_package(SFML 2.5 COMPONENTS system window graphics network audio)
  target_link_libraries(lib_ed sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
endif(MSVC)

if(MSVC)
  set_target_properties(lib_ed PROPERTIES ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR})
  set_target_properties(lib_ed PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
  set_target_properties(lib_ed PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR})
else()
  set_target_properties(lib_ed PROPERTIES ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR})
endif(MSVC)

# ===== Library =====

add_executable(ed main.cc)

target_link_libraries(ed PRIVATE lib_ed)

target_include_directories(ed PUBLIC ${include_dir})
target_include_directories(ed PUBLIC ${extern_include_dir})
target_include_directories(lib_ed PUBLIC ${sfml_include_dir})
target_include_directories(lib_ed PUBLIC ${imgui_include_dir})

if(MSVC)
  set_target_properties(ed PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
  set_target_properties(ed PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
  set_target_properties(ed PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR})
else()
  set_target_properties(ed PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif(MSVC)
