cmake_minimum_required(VERSION 3.0.0)
project(planets VERSION 0.1.0)

add_executable(planets main.cpp)


set(LIBS "libplanet" "mycollections")


foreach(DIR ${LIBS})
    add_subdirectory(${DIR})
    target_link_libraries(planets PRIVATE ${DIR})
    target_include_directories(planets PUBLIC ${PROJECT_SOURCE_DIR}/${DIR}/Include)
endforeach()




# for vs code
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)