
add_library(libplanet 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Point.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sphere.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Position.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Astre.cpp )

target_include_directories(libplanet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
# target_include_directories(libplanet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
