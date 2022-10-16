########################
# googletest for unit testing
########################
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(BINARY streets_vehicle_list_test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES} WORKING_DIRECTORY  ${PROJECT_SOURCE_DIR}/test)


add_executable(${BINARY} ${TEST_SOURCES}
            # src/models/vehicle_list.cpp
            # src/exceptions/status_intent_processing_exception.cpp
            # src/message_processors/signalized_status_intent_processor.cpp
            # src/message_processors/all_stop_status_intent_processor.cpp
            # src/message_processors/status_intent_processor.cpp
                )

target_compile_features(${BINARY}
  PRIVATE
    cxx_std_17
)

add_test(NAME ${BINARY} COMMAND ${BINARY})
target_include_directories(${BINARY} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${BINARY} PUBLIC
                spdlog::spdlog
                gtest
                streets_vehicle_list_lib
                )
