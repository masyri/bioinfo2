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
include CMakeFiles/dssp.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/dssp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dssp.dir/flags.make

CMakeFiles/dssp.dir/Main.cpp.o: CMakeFiles/dssp.dir/flags.make
CMakeFiles/dssp.dir/Main.cpp.o: ../Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dssp.dir/Main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssp.dir/Main.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Main.cpp

CMakeFiles/dssp.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssp.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Main.cpp > CMakeFiles/dssp.dir/Main.cpp.i

CMakeFiles/dssp.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssp.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Main.cpp -o CMakeFiles/dssp.dir/Main.cpp.s

CMakeFiles/dssp.dir/DSSPbonds.cpp.o: CMakeFiles/dssp.dir/flags.make
CMakeFiles/dssp.dir/DSSPbonds.cpp.o: ../DSSPbonds.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/dssp.dir/DSSPbonds.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssp.dir/DSSPbonds.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/DSSPbonds.cpp

CMakeFiles/dssp.dir/DSSPbonds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssp.dir/DSSPbonds.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/DSSPbonds.cpp > CMakeFiles/dssp.dir/DSSPbonds.cpp.i

CMakeFiles/dssp.dir/DSSPbonds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssp.dir/DSSPbonds.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/DSSPbonds.cpp -o CMakeFiles/dssp.dir/DSSPbonds.cpp.s

CMakeFiles/dssp.dir/DSSPcreate.cpp.o: CMakeFiles/dssp.dir/flags.make
CMakeFiles/dssp.dir/DSSPcreate.cpp.o: ../DSSPcreate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/dssp.dir/DSSPcreate.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssp.dir/DSSPcreate.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/DSSPcreate.cpp

CMakeFiles/dssp.dir/DSSPcreate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssp.dir/DSSPcreate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/DSSPcreate.cpp > CMakeFiles/dssp.dir/DSSPcreate.cpp.i

CMakeFiles/dssp.dir/DSSPcreate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssp.dir/DSSPcreate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/DSSPcreate.cpp -o CMakeFiles/dssp.dir/DSSPcreate.cpp.s

CMakeFiles/dssp.dir/console/console.cpp.o: CMakeFiles/dssp.dir/flags.make
CMakeFiles/dssp.dir/console/console.cpp.o: ../console/console.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/dssp.dir/console/console.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssp.dir/console/console.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/console/console.cpp

CMakeFiles/dssp.dir/console/console.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssp.dir/console/console.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/console/console.cpp > CMakeFiles/dssp.dir/console/console.cpp.i

CMakeFiles/dssp.dir/console/console.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssp.dir/console/console.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/console/console.cpp -o CMakeFiles/dssp.dir/console/console.cpp.s

CMakeFiles/dssp.dir/console/Color.cpp.o: CMakeFiles/dssp.dir/flags.make
CMakeFiles/dssp.dir/console/Color.cpp.o: ../console/Color.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/dssp.dir/console/Color.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssp.dir/console/Color.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/console/Color.cpp

CMakeFiles/dssp.dir/console/Color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssp.dir/console/Color.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/console/Color.cpp > CMakeFiles/dssp.dir/console/Color.cpp.i

CMakeFiles/dssp.dir/console/Color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssp.dir/console/Color.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/console/Color.cpp -o CMakeFiles/dssp.dir/console/Color.cpp.s

CMakeFiles/dssp.dir/Groups.cpp.o: CMakeFiles/dssp.dir/flags.make
CMakeFiles/dssp.dir/Groups.cpp.o: ../Groups.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/dssp.dir/Groups.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssp.dir/Groups.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Groups.cpp

CMakeFiles/dssp.dir/Groups.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssp.dir/Groups.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Groups.cpp > CMakeFiles/dssp.dir/Groups.cpp.i

CMakeFiles/dssp.dir/Groups.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssp.dir/Groups.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Groups.cpp -o CMakeFiles/dssp.dir/Groups.cpp.s

CMakeFiles/dssp.dir/Space3D.cpp.o: CMakeFiles/dssp.dir/flags.make
CMakeFiles/dssp.dir/Space3D.cpp.o: ../Space3D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/dssp.dir/Space3D.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dssp.dir/Space3D.cpp.o -c /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Space3D.cpp

CMakeFiles/dssp.dir/Space3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dssp.dir/Space3D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Space3D.cpp > CMakeFiles/dssp.dir/Space3D.cpp.i

CMakeFiles/dssp.dir/Space3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dssp.dir/Space3D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/Space3D.cpp -o CMakeFiles/dssp.dir/Space3D.cpp.s

# Object files for target dssp
dssp_OBJECTS = \
"CMakeFiles/dssp.dir/Main.cpp.o" \
"CMakeFiles/dssp.dir/DSSPbonds.cpp.o" \
"CMakeFiles/dssp.dir/DSSPcreate.cpp.o" \
"CMakeFiles/dssp.dir/console/console.cpp.o" \
"CMakeFiles/dssp.dir/console/Color.cpp.o" \
"CMakeFiles/dssp.dir/Groups.cpp.o" \
"CMakeFiles/dssp.dir/Space3D.cpp.o"

# External object files for target dssp
dssp_EXTERNAL_OBJECTS =

dssp: CMakeFiles/dssp.dir/Main.cpp.o
dssp: CMakeFiles/dssp.dir/DSSPbonds.cpp.o
dssp: CMakeFiles/dssp.dir/DSSPcreate.cpp.o
dssp: CMakeFiles/dssp.dir/console/console.cpp.o
dssp: CMakeFiles/dssp.dir/console/Color.cpp.o
dssp: CMakeFiles/dssp.dir/Groups.cpp.o
dssp: CMakeFiles/dssp.dir/Space3D.cpp.o
dssp: CMakeFiles/dssp.dir/build.make
dssp: /usr/lib/libBALL.so.1.5
dssp: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
dssp: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.12.8
dssp: /usr/lib/x86_64-linux-gnu/libQt5Xml.so.5.12.8
dssp: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
dssp: /usr/lib/x86_64-linux-gnu/libpython2.7.so
dssp: CMakeFiles/dssp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable dssp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dssp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dssp.dir/build: dssp
.PHONY : CMakeFiles/dssp.dir/build

CMakeFiles/dssp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dssp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dssp.dir/clean

CMakeFiles/dssp.dir/depend:
	cd /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/masy00001/Documents/bioinfo2/Bioinfo_UB02 /home/masy00001/Documents/bioinfo2/Bioinfo_UB02 /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug /home/masy00001/Documents/bioinfo2/Bioinfo_UB02/cmake-build-debug/CMakeFiles/dssp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dssp.dir/depend

