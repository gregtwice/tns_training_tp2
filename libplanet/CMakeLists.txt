
set(HEADER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Include/Sphere.h)

add_library(libplanet Point.cpp Sphere.cpp Position.cpp Astre.cpp)

target_include_directories(libplanet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_include_directories(libplanet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
