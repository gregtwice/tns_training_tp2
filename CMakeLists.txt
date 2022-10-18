cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME planets_sim)

project(${EXECUTABLE_NAME} VERSION 0.1.0)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

#Libraries

set(LIBS "planets" "mycollections" "cli" "utils")

add_subdirectory(Source)

foreach(DIR ${LIBS})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${DIR})
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include/${DIR})
endforeach()

# for vs code
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

#testing
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

set(TEST_DIR "test")

add_executable(
  hello_test
  ${TEST_DIR}/test1_test.cpp
  ${TEST_DIR}/Vec3_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  planets
)

target_include_directories(hello_test 
PUBLIC ${PROJECT_SOURCE_DIR}/Include/planets}
)

include(GoogleTest)
gtest_discover_tests(hello_test)