add_executable(streets_signal_phase_and_timing_test
  test_main.cpp
  test_intersection_state.cpp
  test_ntcip_to_spat.cpp
  test_spat_to_json.cpp
  test_time_change_detail.cpp
)

target_link_libraries(streets_signal_phase_and_timing_test
  PRIVATE
    spdlog::spdlog
    gtest
    rapidjson
    streets_signal_phase_and_timing_lib
)

# The CI system expects the test binary to be in the project's binary root directory
set_target_properties(streets_signal_phase_and_timing_test
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

gtest_discover_tests(streets_signal_phase_and_timing_test)
