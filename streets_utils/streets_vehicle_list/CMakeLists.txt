cmake_minimum_required(VERSION 3.16)
project(streets_vehicle_list)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
# Required for shared_mutex
set(CMAKE_CXX_STANDARD 17)


find_package(spdlog REQUIRED)
add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

find_package(RapidJSON REQUIRED)
find_package(GTest REQUIRED)

add_library(streets_vehicle_list_lib
                src/models/vehicle_list.cpp
                src/exceptions/status_intent_processing_exception.cpp
                src/message_processors/signalized_status_intent_processor.cpp
                src/message_processors/all_stop_status_intent_processor.cpp
                src/message_processors/status_intent_processor.cpp
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
    cmake/streets_vehicle_list_libConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/streets_vehicle_list_libConfig.cmake
    INSTALL_DESTINATION  lib/streets_vehicle_list_lib/streets_vehicle_list_lib/ )
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/streets_vehicle_list_libConfig.cmake
    DESTINATION  lib/cmake/streets_vehicle_list_lib/
)

install(FILES ${files} DESTINATION include)

########################
# googletest for unit testing
########################
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(BINARY streets_vehicle_list_test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false test/*.h test/*.cpp)
set(SOURCES ${TEST_SOURCES} WORKING_DIRECTORY  ${PROJECT_SOURCE_DIR}/test)


add_executable(${BINARY} ${TEST_SOURCES}
            src/models/vehicle_list.cpp
            src/exceptions/status_intent_processing_exception.cpp
            src/message_processors/signalized_status_intent_processor.cpp
            src/message_processors/all_stop_status_intent_processor.cpp
            src/message_processors/status_intent_processor.cpp
                )

add_test(NAME ${BINARY} COMMAND ${BINARY})
target_include_directories(${BINARY} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${BINARY} PUBLIC
                spdlog::spdlog
                gtest
                streets_vehicle_list_lib
                )
