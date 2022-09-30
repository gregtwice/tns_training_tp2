add_library(cli src/UserInterface.cpp)


target_include_directories(cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_include_directories(cli PRIVATE ../mycollections/Include)
target_include_directories(cli PRIVATE ../libplanet/Include)
target_include_directories(cli PRIVATE ../utils/Include)


target_link_libraries(cli libplanet mycollections)