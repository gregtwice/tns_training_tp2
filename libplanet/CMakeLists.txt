add_library(libplanet Point.cpp Sphere.cpp Position.cpp)

target_include_directories(libplanet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
