LRL - Less Routine Library provides with syntax sugar for trivial routines to reduce code amount when it's not necessary

TESTS:
To run tests you need specify LRLTests=TRUE while doing cmaking

Purposes of tests:
	1. Correctness
	2. Zero-cost: same binary code for code with and without library syntax sugar

Tested environments(CMake):
	* Win 10, MinGW 64 (x86_64-8.1.0-win32-seh-rt_v6-rev0)
	* Debian, GCC 8.3.0, G++ 8.3.0, native make
	//Hoping this list will include much more envs
