add_library(mycollections ${CMAKE_CURRENT_SOURCE_DIR}/src/MyStaticArray.cpp)

target_include_directories(mycollections PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)