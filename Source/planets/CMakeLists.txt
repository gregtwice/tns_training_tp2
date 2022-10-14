set(MODULE_NAME planets)
add_library(${MODULE_NAME} 
    "${CMAKE_CURRENT_SOURCE_DIR}/Vec3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Point.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Position.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Sphere.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Astre.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asteroid.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SolarSystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Planet.cpp"
)

target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Include/${MODULE_NAME})
target_link_libraries(${MODULE_NAME} utils)
target_link_libraries(${MODULE_NAME} mycollections)
target_link_libraries(${MODULE_NAME} cli)
