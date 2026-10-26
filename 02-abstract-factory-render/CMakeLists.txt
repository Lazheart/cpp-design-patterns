add_library(render STATIC
  src/opengl_factory.cpp
  src/vulkan_factory.cpp
  src/factory_registry.cpp
)
target_include_directories(render PUBLIC include)
set_project_warnings(render)

add_executable(render_demo app/main.cpp)
target_link_libraries(render_demo PRIVATE render)
set_project_warnings(render_demo)

add_executable(render_tests tests/render_test.cpp)
target_link_libraries(render_tests PRIVATE render GTest::gtest_main)
set_project_warnings(render_tests)
gtest_discover_tests(render_tests)
