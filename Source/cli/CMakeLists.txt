set(MODULE_NAME cli)

add_library(${MODULE_NAME} 
    "${CMAKE_CURRENT_SOURCE_DIR}/UserInterface.cpp"
)

target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Include/${MODULE_NAME})
target_link_libraries(${MODULE_NAME} mycollections planets)
if (UNIX)
    target_link_libraries(${MODULE_NAME} pthread)
endif (UNIX)