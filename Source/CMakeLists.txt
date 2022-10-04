set(LIBS "planets" "mycollections" "cli" "utils")


foreach(DIR ${LIBS})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${DIR})
    # target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${DIR})
    # target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src/${DIR}/Include)
endforeach()