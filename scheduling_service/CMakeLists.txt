cmake_minimum_required(VERSION 3.10.2)
project(scheduling_service)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wno-unused-variable")
set(CMAKE_CXX_STANDARD 17)

link_directories("/usr/lib"  "/usr/local/lib" )

find_package(Boost COMPONENTS thread filesystem system REQUIRED)
find_package(spdlog REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(streets_service_base_lib COMPONENTS streets_service_base_lib REQUIRED)
find_package(streets_vehicle_list_lib REQUIRED)
find_package(streets_vehicle_scheduler_lib REQUIRED)
find_package(streets_signal_phase_and_timing_lib REQUIRED)

add_definitions(-DRAPIDJSON_HAS_STDSTRING=1)
add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

include_directories("/usr/local/include")

add_executable(${PROJECT_NAME}  src/main.cpp
                                src/intersection_client.cpp
                                src/scheduling_service.cpp
                                src/scheduling_worker.cpp)
                                
target_include_directories( ${PROJECT_NAME} PUBLIC
                            ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    kafka_clients_lib 
    rdkafka++ 
    Boost::system Boost::filesystem 
    Boost::thread spdlog::spdlog 
    intersection_client_api_lib 
    streets_service_base_lib::streets_service_base_lib 
    streets_vehicle_list_lib::streets_vehicle_list_lib 
    streets_vehicle_scheduler_lib::streets_vehicle_scheduler_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network )


########################
# googletest for unit testing
########################
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(BINARY ${PROJECT_NAME}_test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false test/*.h test/*.cpp)
set(SOURCES ${TEST_SOURCES} WORKING_DIRECTORY  ${PROJECT_SOURCE_DIR}/test)
add_executable(${BINARY} ${TEST_SOURCES}
                        src/intersection_client.cpp
                        src/scheduling_service.cpp
                        src/scheduling_worker.cpp )
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_include_directories(${BINARY} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${BINARY} PUBLIC  Boost::system Boost::filesystem kafka_clients_lib rdkafka++ Boost::thread spdlog::spdlog gtest intersection_client_api_lib Qt5::Core Qt5::Network streets_service_base_lib::streets_service_base_lib streets_vehicle_list_lib::streets_vehicle_list_lib streets_vehicle_scheduler_lib::streets_vehicle_scheduler_lib streets_signal_phase_and_timing_lib::streets_signal_phase_and_timing_lib)    