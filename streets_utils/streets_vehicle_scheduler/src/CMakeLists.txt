include(GNUInstallDirs)

set(STREETSVEHICLESCHEDULER_SPDLOG_LEVEL SPDLOG_LEVEL_WARN CACHE STRING "Logging level for spdlog")
set_property(CACHE STREETSVEHICLESCHEDULER_SPDLOG_LEVEL PROPERTY STRINGS
  SPDLOG_LEVEL_TRACE
  SPDLOG_LEVEL_DEBUG
  SPDLOG_LEVEL_INFO
  SPDLOG_LEVEL_WARN
  SPDLOG_LEVEL_ERROR
  SPDLOG_LEVEL_CRITICAL
  SPDLOG_LEVEL_OFF
)

add_library(streets_vehicle_scheduler_lib
  scheduling_exception.cpp
  vehicle_sorting.cpp
  all_stop_intersection_schedule.cpp
  signalized_intersection_schedule.cpp
  vehicle_scheduler.cpp
  all_stop_vehicle_scheduler.cpp
  signalized_vehicle_scheduler.cpp
)

add_library(streets_vehicle_scheduler_lib::streets_vehicle_scheduler_lib ALIAS streets_vehicle_scheduler_lib)

target_compile_features(streets_vehicle_scheduler_lib
  PUBLIC
    cxx_std_17 # Required for shared_mutex
)

target_compile_definitions(streets_vehicle_scheduler_lib
  PUBLIC
    SPDLOG_ACTIVE_LEVEL=${STREETSVEHICLESCHEDULER_SPDLOG_LEVEL}
  PRIVATE
    RAPIDJSON_HAS_STDSTRING=1
)

target_compile_options(streets_vehicle_scheduler_lib
  PRIVATE
    -fPIC
)

target_include_directories(streets_vehicle_scheduler_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(streets_vehicle_scheduler_lib
  PUBLIC
    spdlog::spdlog
    rapidjson
    Qt5::Core
    Qt5::Network
    intersection_client_api_lib
    streets_service_base_lib::streets_service_base_lib
    streets_vehicle_list_lib
    streets_signal_phase_and_timing_lib
)

install(TARGETS streets_vehicle_scheduler_lib
  EXPORT streets_vehicle_scheduler_libTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT streets_vehicle_scheduler_libTargets
  FILE streets_vehicle_scheduler_libTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/streets_vehicle_scheduler_lib
  NAMESPACE streets_vehicle_scheduler_lib::
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/streets_vehicle_scheduler_libConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/streets_vehicle_scheduler_libConfig.cmake
    INSTALL_DESTINATION  ${CMAKE_INSTALL_LIBDIR}/streets_vehicle_scheduler_lib/streets_vehicle_scheduler_lib/ )

install(FILES ${PROJECT_BINARY_DIR}/streets_vehicle_scheduler_libConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/streets_vehicle_scheduler_lib
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN *.h
)
