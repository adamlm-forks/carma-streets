include(CMakeFindDependencyMacro)

find_dependency(spdlog REQUIRED)
find_dependency(RapidJSON REQUIRED)
find_dependency(GTest REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/streets_vehicle_list_libTargets.cmake)
