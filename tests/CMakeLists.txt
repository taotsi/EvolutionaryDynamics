add_executable(test_evolutionary_dynamics test_main.cc)

target_include_directories(test_evolutionary_dynamics PUBLIC ${include_dir})
target_include_directories(test_evolutionary_dynamics PUBLIC ${extern_include_dir})

target_link_libraries(test_evolutionary_dynamics PRIVATE lib_evolutionary_dynamics)

if(MSVC)
  set_target_properties(test_evolutionary_dynamics PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
  set_target_properties(test_evolutionary_dynamics PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
  set_target_properties(test_evolutionary_dynamics PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR})
else()
  set_target_properties(test_evolutionary_dynamics PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif(MSVC)
