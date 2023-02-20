add_executable(unit_tests connection_base_test.cpp)

target_link_libraries(unit_tests PRIVATE server_lib gtest_main)

include(Coverage)
AddCoverage(unit_tests)

include(GoogleTest)
gtest_discover_tests(unit_tests)
