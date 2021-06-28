cmake_minimum_required(VERSION 3.19)
project("LRL")

set(CMAKE_CXX_STANDARD 17)

if (TESTS_ONLY)
  add_subdirectory("Tests")
endif()