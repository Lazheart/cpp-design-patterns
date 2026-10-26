find_package(Threads REQUIRED)

add_library(txn STATIC
  src/account.cpp
  src/transaction_manager.cpp
)
target_include_directories(txn PUBLIC include)
target_link_libraries(txn PUBLIC Threads::Threads)
set_project_warnings(txn)

add_executable(singleton_demo app/main.cpp)
target_link_libraries(singleton_demo PRIVATE txn)
set_project_warnings(singleton_demo)

add_executable(txn_tests tests/transaction_manager_test.cpp)
target_link_libraries(txn_tests PRIVATE txn GTest::gtest_main)
set_project_warnings(txn_tests)
gtest_discover_tests(txn_tests)
