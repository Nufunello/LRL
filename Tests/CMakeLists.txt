cmake_minimum_required(VERSION 3.19)
project(LRTLTests)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

#Adding dependencies
set(DEPENDENCIES_FOLDER "Dependencies")

add_subdirectory("${DEPENDENCIES_FOLDER}/googletest")

#Configuring Tests
set(TARGET ${PROJECT_NAME})
set(SOURCE_FOLDER "src")

add_executable(
  ${TARGET}
  "${SOURCE_FOLDER}/main.cpp"
)

#Configuring GTest
enable_testing()

target_link_libraries(
  ${TARGET}
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET})