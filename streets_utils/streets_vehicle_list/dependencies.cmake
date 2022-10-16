find_package(spdlog REQUIRED)
find_package(RapidJSON REQUIRED)

if(STREETSVEHICLELIST_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  find_package(GTest REQUIRED)
endif()
