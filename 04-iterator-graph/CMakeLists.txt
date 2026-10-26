add_library(graph STATIC
  src/graph.cpp
  src/bfs_iterator.cpp
  src/dfs_iterator.cpp
)
target_include_directories(graph PUBLIC include)
set_project_warnings(graph)

add_executable(graph_demo app/main.cpp)
target_link_libraries(graph_demo PRIVATE graph)
set_project_warnings(graph_demo)

add_executable(graph_tests tests/graph_test.cpp)
target_link_libraries(graph_tests PRIVATE graph GTest::gtest_main)
set_project_warnings(graph_tests)
gtest_discover_tests(graph_tests)
