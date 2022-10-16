include(GNUInstallDirs)

set(STREETSVEHICLELIST_SPDLOG_LEVEL SPDLOG_LEVEL_WARN CACHE STRING "Logging level for spdlog")
set_property(CACHE STREETSVEHICLELIST_SPDLOG_LEVEL PROPERTY STRINGS
  SPDLOG_LEVEL_TRACE
  SPDLOG_LEVEL_DEBUG
  SPDLOG_LEVEL_INFO
  SPDLOG_LEVEL_WARN
  SPDLOG_LEVEL_ERROR
  SPDLOG_LEVEL_CRITICAL
  SPDLOG_LEVEL_OFF
)

add_library(streets_vehicle_list_lib
  models/vehicle_list.cpp
  exceptions/status_intent_processing_exception.cpp
  message_processors/signalized_status_intent_processor.cpp
  message_processors/all_stop_status_intent_processor.cpp
  message_processors/status_intent_processor.cpp
)

add_library(streets_vehicle_list_lib::streets_vehicle_list_lib ALIAS streets_vehicle_list_lib)

target_compile_features(streets_vehicle_list_lib
  PRIVATE
    cxx_std_17 # Required for shared_mutex
)

target_compile_definitions(streets_vehicle_list_lib
  PUBLIC
    SPDLOG_ACTIVE_LEVEL=${STREETSVEHICLELIST_SPDLOG_LEVEL}
)

target_compile_options(streets_vehicle_list_lib
  PRIVATE
    -fPIC
)

target_include_directories(streets_vehicle_list_lib
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(streets_vehicle_list_lib
  PUBLIC
    spdlog::spdlog
    rapidjson
)

install(TARGETS streets_vehicle_list_lib
  EXPORT streets_vehicle_list_libTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT streets_vehicle_list_libTargets
  FILE streets_vehicle_list_libTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/streets_vehicle_list_lib
  NAMESPACE streets_vehicle_list_lib::
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/streets_vehicle_list_libConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/streets_vehicle_list_libConfig.cmake
  INSTALL_DESTINATION  lib/streets_vehicle_list_lib/streets_vehicle_list_lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/streets_vehicle_list_libConfig.cmake
  DESTINATION  ${CMAKE_INSTALL_LIBDIR}/cmake/streets_vehicle_list_lib/
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN *.h
)
