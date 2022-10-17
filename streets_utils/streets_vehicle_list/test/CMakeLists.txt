add_executable(streets_vehicle_list_test
  test_main.cpp
  test_vehicle_list_signalized_status_intent_processor.cpp
  test_vehicle_list.cpp
)

target_compile_features(streets_vehicle_list_test
  PRIVATE
    cxx_std_17
)

target_link_libraries(streets_vehicle_list_test
  PRIVATE
    spdlog::spdlog
    GTest::GTest
    streets_vehicle_list_lib
)

# The CI system expects the test binary to be in the project's binary root directory
set_target_properties(streets_vehicle_list_test
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

gtest_discover_tests(streets_vehicle_list_test)
