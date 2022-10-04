set(MODULE_NAME utils)

add_library(${MODULE_NAME} 
    "${CMAKE_CURRENT_SOURCE_DIR}/Validator.cpp"
)
message(${CMAKE_SOURCE_DIR}/Include/${MODULE_NAME})
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Include/${MODULE_NAME})