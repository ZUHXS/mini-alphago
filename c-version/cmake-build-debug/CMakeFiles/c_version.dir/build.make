# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/zuhxs/Downloads/clion-2019.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/zuhxs/Downloads/clion-2019.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/psf/Home/Documents/GitHub/mini-alphago/c-version

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/c_version.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/c_version.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/c_version.dir/flags.make

CMakeFiles/c_version.dir/main.cpp.o: CMakeFiles/c_version.dir/flags.make
CMakeFiles/c_version.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/c_version.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/c_version.dir/main.cpp.o -c /media/psf/Home/Documents/GitHub/mini-alphago/c-version/main.cpp

CMakeFiles/c_version.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/c_version.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/psf/Home/Documents/GitHub/mini-alphago/c-version/main.cpp > CMakeFiles/c_version.dir/main.cpp.i

CMakeFiles/c_version.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/c_version.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/psf/Home/Documents/GitHub/mini-alphago/c-version/main.cpp -o CMakeFiles/c_version.dir/main.cpp.s

CMakeFiles/c_version.dir/chessboard.cpp.o: CMakeFiles/c_version.dir/flags.make
CMakeFiles/c_version.dir/chessboard.cpp.o: ../chessboard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/c_version.dir/chessboard.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/c_version.dir/chessboard.cpp.o -c /media/psf/Home/Documents/GitHub/mini-alphago/c-version/chessboard.cpp

CMakeFiles/c_version.dir/chessboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/c_version.dir/chessboard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/psf/Home/Documents/GitHub/mini-alphago/c-version/chessboard.cpp > CMakeFiles/c_version.dir/chessboard.cpp.i

CMakeFiles/c_version.dir/chessboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/c_version.dir/chessboard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/psf/Home/Documents/GitHub/mini-alphago/c-version/chessboard.cpp -o CMakeFiles/c_version.dir/chessboard.cpp.s

CMakeFiles/c_version.dir/MCTS.cpp.o: CMakeFiles/c_version.dir/flags.make
CMakeFiles/c_version.dir/MCTS.cpp.o: ../MCTS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/c_version.dir/MCTS.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/c_version.dir/MCTS.cpp.o -c /media/psf/Home/Documents/GitHub/mini-alphago/c-version/MCTS.cpp

CMakeFiles/c_version.dir/MCTS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/c_version.dir/MCTS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/psf/Home/Documents/GitHub/mini-alphago/c-version/MCTS.cpp > CMakeFiles/c_version.dir/MCTS.cpp.i

CMakeFiles/c_version.dir/MCTS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/c_version.dir/MCTS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/psf/Home/Documents/GitHub/mini-alphago/c-version/MCTS.cpp -o CMakeFiles/c_version.dir/MCTS.cpp.s

# Object files for target c_version
c_version_OBJECTS = \
"CMakeFiles/c_version.dir/main.cpp.o" \
"CMakeFiles/c_version.dir/chessboard.cpp.o" \
"CMakeFiles/c_version.dir/MCTS.cpp.o"

# External object files for target c_version
c_version_EXTERNAL_OBJECTS =

c_version: CMakeFiles/c_version.dir/main.cpp.o
c_version: CMakeFiles/c_version.dir/chessboard.cpp.o
c_version: CMakeFiles/c_version.dir/MCTS.cpp.o
c_version: CMakeFiles/c_version.dir/build.make
c_version: CMakeFiles/c_version.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable c_version"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c_version.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/c_version.dir/build: c_version

.PHONY : CMakeFiles/c_version.dir/build

CMakeFiles/c_version.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/c_version.dir/cmake_clean.cmake
.PHONY : CMakeFiles/c_version.dir/clean

CMakeFiles/c_version.dir/depend:
	cd /media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/psf/Home/Documents/GitHub/mini-alphago/c-version /media/psf/Home/Documents/GitHub/mini-alphago/c-version /media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug /media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug /media/psf/Home/Documents/GitHub/mini-alphago/c-version/cmake-build-debug/CMakeFiles/c_version.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/c_version.dir/depend

