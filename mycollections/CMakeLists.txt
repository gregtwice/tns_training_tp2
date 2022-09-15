add_library(mycollections ${CMAKE_CURRENT_SOURCE_DIR}/src/MyArray.cpp)

target_include_directories(mycollections PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)