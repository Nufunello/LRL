cmake_minimum_required(VERSION 3.19)
project("LRL")

if (LRLTests)
	#Adding tests to lib cmake
	add_subdirectory("Tests")
	
	#Adding lrl include to tests
	target_include_directories(LRLTests PUBLIC "include")
	
	#Features min cpp standard
	target_compile_features(LRLTests PUBLIC cxx_std_17)
endif()
