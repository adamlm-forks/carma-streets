set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
# Required for shared_mutex
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

add_library(streets_vehicle_list_lib
                models/vehicle_list.cpp
                exceptions/status_intent_processing_exception.cpp
                message_processors/signalized_status_intent_processor.cpp
                message_processors/all_stop_status_intent_processor.cpp
                message_processors/status_intent_processor.cpp
                )

target_link_libraries(streets_vehicle_list_lib PUBLIC spdlog::spdlog rapidjson)
target_include_directories(streets_vehicle_list_lib PUBLIC
                            $<INSTALL_INTERFACE:include>
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                            PRIVATE
                            ${CMAKE_CURRENT_SOURCE_DIR}/src)
########################################################
# Install streets_vehicle_list_lib package.
########################################################
file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

install(
    TARGETS streets_vehicle_list_lib
    EXPORT streets_vehicle_list_libTargets
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include
    ARCHIVE DESTINATION lib
)
install(
    EXPORT streets_vehicle_list_libTargets
    FILE streets_vehicle_list_libTargets.cmake
    DESTINATION lib/cmake/streets_vehicle_list_lib/
    NAMESPACE streets_vehicle_list_lib::
)
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/streets_vehicle_list_libConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/streets_vehicle_list_libConfig.cmake
    INSTALL_DESTINATION  lib/streets_vehicle_list_lib/streets_vehicle_list_lib/ )
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/streets_vehicle_list_libConfig.cmake
    DESTINATION  lib/cmake/streets_vehicle_list_lib/
)

install(FILES ${files} DESTINATION include)
