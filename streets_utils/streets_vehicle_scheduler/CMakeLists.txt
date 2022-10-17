cmake_minimum_required(VERSION 3.16)
project(streets_vehicle_scheduler)
enable_testing()

include(dependencies.cmake)

add_subdirectory(src)

add_subdirectory(test)
