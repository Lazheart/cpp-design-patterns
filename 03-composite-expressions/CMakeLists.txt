add_library(expr STATIC
  src/constant.cpp
  src/variable.cpp
  src/binary_operation.cpp
  src/add.cpp
  src/multiply.cpp
  src/power.cpp
  src/unary_function.cpp
  src/sin.cpp
  src/cos.cpp
)
target_include_directories(expr PUBLIC include)
set_project_warnings(expr)

add_executable(expr_demo app/main.cpp)
target_link_libraries(expr_demo PRIVATE expr)
set_project_warnings(expr_demo)

add_executable(expr_tests tests/expression_test.cpp)
target_link_libraries(expr_tests PRIVATE expr GTest::gtest_main)
set_project_warnings(expr_tests)
gtest_discover_tests(expr_tests)
