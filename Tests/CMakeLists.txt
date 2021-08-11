cmake_minimum_required(VERSION 3.19)
project(LRLTests)

#Adding dependencies
set(DEPENDENCIES_FOLDER "Dependencies")

add_subdirectory("${DEPENDENCIES_FOLDER}/googletest")

#Configuring Tests
set(TARGET ${PROJECT_NAME})
set(SOURCE_FOLDER "src")

add_executable(
  ${TARGET}
  "${SOURCE_FOLDER}/main.cpp"

  "${SOURCE_FOLDER}/iterators/begin_end.cpp"
)

#Configuring GTest
enable_testing()

target_link_libraries(
  ${TARGET}
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET})

# GoogleTest requires at least C++11
target_compile_features(${TARGET} PUBLIC cxx_std_11)