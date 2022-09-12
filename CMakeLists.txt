cmake_minimum_required(VERSION 3.0.0)
project(planets VERSION 0.1.0)

add_executable(planets main.cpp)

add_subdirectory(libplanet)
target_link_libraries(planets PRIVATE libplanet)

target_include_directories(planets PUBLIC ${PROJECT_SOURCE_DIR}/libplanet/src)
target_include_directories(planets PUBLIC ${PROJECT_SOURCE_DIR}/libplanet/Include)

# for vs code
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)