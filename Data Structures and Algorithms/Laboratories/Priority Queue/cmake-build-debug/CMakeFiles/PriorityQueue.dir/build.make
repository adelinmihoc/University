# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/adelin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/adelin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adelin/CLionProjects/PriorityQueue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adelin/CLionProjects/PriorityQueue/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PriorityQueue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PriorityQueue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PriorityQueue.dir/flags.make

CMakeFiles/PriorityQueue.dir/App.cpp.o: CMakeFiles/PriorityQueue.dir/flags.make
CMakeFiles/PriorityQueue.dir/App.cpp.o: ../App.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adelin/CLionProjects/PriorityQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PriorityQueue.dir/App.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PriorityQueue.dir/App.cpp.o -c /home/adelin/CLionProjects/PriorityQueue/App.cpp

CMakeFiles/PriorityQueue.dir/App.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PriorityQueue.dir/App.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adelin/CLionProjects/PriorityQueue/App.cpp > CMakeFiles/PriorityQueue.dir/App.cpp.i

CMakeFiles/PriorityQueue.dir/App.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PriorityQueue.dir/App.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adelin/CLionProjects/PriorityQueue/App.cpp -o CMakeFiles/PriorityQueue.dir/App.cpp.s

CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.o: CMakeFiles/PriorityQueue.dir/flags.make
CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.o: ../ExtendedTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adelin/CLionProjects/PriorityQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.o -c /home/adelin/CLionProjects/PriorityQueue/ExtendedTest.cpp

CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adelin/CLionProjects/PriorityQueue/ExtendedTest.cpp > CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.i

CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adelin/CLionProjects/PriorityQueue/ExtendedTest.cpp -o CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.s

CMakeFiles/PriorityQueue.dir/ShortTest.cpp.o: CMakeFiles/PriorityQueue.dir/flags.make
CMakeFiles/PriorityQueue.dir/ShortTest.cpp.o: ../ShortTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adelin/CLionProjects/PriorityQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PriorityQueue.dir/ShortTest.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PriorityQueue.dir/ShortTest.cpp.o -c /home/adelin/CLionProjects/PriorityQueue/ShortTest.cpp

CMakeFiles/PriorityQueue.dir/ShortTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PriorityQueue.dir/ShortTest.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adelin/CLionProjects/PriorityQueue/ShortTest.cpp > CMakeFiles/PriorityQueue.dir/ShortTest.cpp.i

CMakeFiles/PriorityQueue.dir/ShortTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PriorityQueue.dir/ShortTest.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adelin/CLionProjects/PriorityQueue/ShortTest.cpp -o CMakeFiles/PriorityQueue.dir/ShortTest.cpp.s

CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.o: CMakeFiles/PriorityQueue.dir/flags.make
CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.o: ../PriorityQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adelin/CLionProjects/PriorityQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.o -c /home/adelin/CLionProjects/PriorityQueue/PriorityQueue.cpp

CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adelin/CLionProjects/PriorityQueue/PriorityQueue.cpp > CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.i

CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adelin/CLionProjects/PriorityQueue/PriorityQueue.cpp -o CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.s

# Object files for target PriorityQueue
PriorityQueue_OBJECTS = \
"CMakeFiles/PriorityQueue.dir/App.cpp.o" \
"CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.o" \
"CMakeFiles/PriorityQueue.dir/ShortTest.cpp.o" \
"CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.o"

# External object files for target PriorityQueue
PriorityQueue_EXTERNAL_OBJECTS =

PriorityQueue: CMakeFiles/PriorityQueue.dir/App.cpp.o
PriorityQueue: CMakeFiles/PriorityQueue.dir/ExtendedTest.cpp.o
PriorityQueue: CMakeFiles/PriorityQueue.dir/ShortTest.cpp.o
PriorityQueue: CMakeFiles/PriorityQueue.dir/PriorityQueue.cpp.o
PriorityQueue: CMakeFiles/PriorityQueue.dir/build.make
PriorityQueue: CMakeFiles/PriorityQueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adelin/CLionProjects/PriorityQueue/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable PriorityQueue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PriorityQueue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PriorityQueue.dir/build: PriorityQueue

.PHONY : CMakeFiles/PriorityQueue.dir/build

CMakeFiles/PriorityQueue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PriorityQueue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PriorityQueue.dir/clean

CMakeFiles/PriorityQueue.dir/depend:
	cd /home/adelin/CLionProjects/PriorityQueue/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adelin/CLionProjects/PriorityQueue /home/adelin/CLionProjects/PriorityQueue /home/adelin/CLionProjects/PriorityQueue/cmake-build-debug /home/adelin/CLionProjects/PriorityQueue/cmake-build-debug /home/adelin/CLionProjects/PriorityQueue/cmake-build-debug/CMakeFiles/PriorityQueue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PriorityQueue.dir/depend

