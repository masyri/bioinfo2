# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/164/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/164/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/masy00001/Documents/bioinfo2/Bioinfo_UB02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug

# Include any dependencies generated for this target.
include tests/CMakeFiles/TestSuite1_tests.dir/depend.make
# Include the progress variables for this target.
include tests/CMakeFiles/TestSuite1_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/TestSuite1_tests.dir/flags.make

tests/CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.o: tests/CMakeFiles/TestSuite1_tests.dir/flags.make
tests/CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.o: ../tests/TestSuite1_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.o"
	cd /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/tests/TestSuite1_tests.cpp

tests/CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.i"
	cd /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/tests/TestSuite1_tests.cpp > CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.i

tests/CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.s"
	cd /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/tests/TestSuite1_tests.cpp -o CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.s

# Object files for target TestSuite1_tests
TestSuite1_tests_OBJECTS = \
"CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.o"

# External object files for target TestSuite1_tests
TestSuite1_tests_EXTERNAL_OBJECTS =

tests/TestSuite1_tests: tests/CMakeFiles/TestSuite1_tests.dir/TestSuite1_tests.cpp.o
tests/TestSuite1_tests: tests/CMakeFiles/TestSuite1_tests.dir/build.make
tests/TestSuite1_tests: lib/libgtestd.a
tests/TestSuite1_tests: lib/libgtest_maind.a
tests/TestSuite1_tests: tests/libtest_driver.a
tests/TestSuite1_tests: /usr/lib/libBALL.so.1.5
tests/TestSuite1_tests: lib/libgtestd.a
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.12.8
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libQt5Xml.so.5.12.8
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
tests/TestSuite1_tests: /usr/lib/x86_64-linux-gnu/libpython2.7.so
tests/TestSuite1_tests: tests/CMakeFiles/TestSuite1_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestSuite1_tests"
	cd /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestSuite1_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/TestSuite1_tests.dir/build: tests/TestSuite1_tests
.PHONY : tests/CMakeFiles/TestSuite1_tests.dir/build

tests/CMakeFiles/TestSuite1_tests.dir/clean:
	cd /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/TestSuite1_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/TestSuite1_tests.dir/clean

tests/CMakeFiles/TestSuite1_tests.dir/depend:
	cd /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/masy00001/Documents/bioinfo2/Bioinfo_UB02 /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/tests /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/tests /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/tests/CMakeFiles/TestSuite1_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/TestSuite1_tests.dir/depend

