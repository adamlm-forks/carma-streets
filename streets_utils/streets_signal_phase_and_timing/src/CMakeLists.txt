include(GNUInstallDirs)

set(STREETSSIGNALPHASEANDTIMING_SDPLOG_LEVEL  SPDLOG_LEVEL_WARN CACHE STRING "Logging level for spdlog")
set_property(CACHE STREETSSIGNALPHASEANDTIMING_SDPLOG_LEVEL PROPERTY STRINGS
  SPDLOG_LEVEL_TRACE
  SPDLOG_LEVEL_DEBUG
  SPDLOG_LEVEL_INFO
  SPDLOG_LEVEL_WARN
  SPDLOG_LEVEL_ERROR
  SPDLOG_LEVEL_CRITICAL
  SPDLOG_LEVEL_OFF
)

add_library(streets_signal_phase_and_timing_lib
  models/connection_maneuver_assist.cpp
  models/movement_state.cpp
  models/movement_event.cpp
  models/advisory_speed.cpp
  models/time_change_details.cpp
  models/intersection_state.cpp
  models/ntcip_1202_ext.cpp
  models/ntcip_1202_ext_phasetime.cpp
  models/spat.cpp
  exceptions/signal_phase_and_timing_exception.cpp
)

add_library(streets_signal_phase_and_timing_lib::streets_signal_phase_and_timing_lib ALIAS streets_signal_phase_and_timing_lib)

target_compile_definitions(streets_signal_phase_and_timing_lib
  PUBLIC
    SPDLOG_ACTIVE_LEVEL=${STREETSSIGNALPHASEANDTIMING_SDPLOG_LEVEL}
  PRIVATE
    RAPIDJSON_HAS_STDSTRING=1 # Needed for rapidjson to include std::string
)

target_compile_options(streets_signal_phase_and_timing_lib
  PRIVATE
    -fPIC
)

target_include_directories(streets_signal_phase_and_timing_lib
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(streets_signal_phase_and_timing_lib
  PUBLIC
    spdlog::spdlog
    rapidjson
)

install(TARGETS streets_signal_phase_and_timing_lib
  EXPORT streets_signal_phase_and_timing_libTargets
  INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT streets_signal_phase_and_timing_libTargets
  FILE streets_signal_phase_and_timing_libTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/streets_signal_phase_and_timing_lib
  NAMESPACE streets_signal_phase_and_timing_lib::
)

install(FILES ${PROJECT_SOURCE_DIR}/cmake/streets_signal_phase_and_timing_libConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/streets_signal_phase_and_timing_lib
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN *.h
)
