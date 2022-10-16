cmake_minimum_required(VERSION 3.16)
project(streets_signal_phase_and_timing)
enable_testing()

# In CMake 3.21, PROJECT_IS_TOP_LEVEL is provided, so if block can be removed when the
# project upgrades to that CMake version
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(PROJECT_IS_TOP_LEVEL TRUE CACHE INTERNAL "")
else()
  set(PROJECT_IS_TOP_LEVEL FALSE CACHE INTERNAL "")
endif()

option(STREETSSIGNALPHASEANDTIMING_ENABLE_TESTING "Enable unit tests for streets_vehicle_list" ${PROJECT_IS_TOP_LEVEL})

include(dependencies.cmake)

add_subdirectory(src)

if(STREETSSIGNALPHASEANDTIMING_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
