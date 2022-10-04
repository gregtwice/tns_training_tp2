set(MODULE_NAME mycollections)

add_library(${MODULE_NAME} 
    "${CMAKE_CURRENT_SOURCE_DIR}/MyStaticArray.cpp"
)

target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Include/${MODULE_NAME})