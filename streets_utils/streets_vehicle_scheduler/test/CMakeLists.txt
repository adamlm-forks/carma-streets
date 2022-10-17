add_executable(streets_vehicle_scheduler_test
  test_main.cpp
  test_all_stop_json_csv_schedule.cpp
  test_all_stop_scenario.cpp
  test_all_stop_scheduler.cpp
  test_signalized_json_csv_schedule.cpp
  test_signalized_scenario.cpp
  test_signalized_scheduler.cpp
)

target_link_libraries(streets_vehicle_scheduler_test
  PRIVATE
    spdlog::spdlog
    GTest::GTest
    streets_vehicle_scheduler_lib
)

set_target_properties(streets_vehicle_scheduler_test
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

gtest_discover_tests(streets_vehicle_scheduler_test)
