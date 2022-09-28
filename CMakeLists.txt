cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME planets)

project(${EXECUTABLE_NAME} VERSION 0.1.0)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

#Libraries

set(LIBS "libplanet" "mycollections" "cli" "utils")

# add_subdirectory(src)

foreach(DIR ${LIBS})
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/${DIR})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${DIR})
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src/${DIR}/Include)
endforeach()

# for vs code
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)