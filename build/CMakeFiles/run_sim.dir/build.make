# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aobrien/dev/cpp/market_maker_sim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aobrien/dev/cpp/market_maker_sim/build

# Include any dependencies generated for this target.
include CMakeFiles/run_sim.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/run_sim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run_sim.dir/flags.make

CMakeFiles/run_sim.dir/main.cc.o: CMakeFiles/run_sim.dir/flags.make
CMakeFiles/run_sim.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aobrien/dev/cpp/market_maker_sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run_sim.dir/main.cc.o"
	/usr/bin/clang++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run_sim.dir/main.cc.o -c /home/aobrien/dev/cpp/market_maker_sim/main.cc

CMakeFiles/run_sim.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_sim.dir/main.cc.i"
	/usr/bin/clang++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aobrien/dev/cpp/market_maker_sim/main.cc > CMakeFiles/run_sim.dir/main.cc.i

CMakeFiles/run_sim.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_sim.dir/main.cc.s"
	/usr/bin/clang++-13 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aobrien/dev/cpp/market_maker_sim/main.cc -o CMakeFiles/run_sim.dir/main.cc.s

# Object files for target run_sim
run_sim_OBJECTS = \
"CMakeFiles/run_sim.dir/main.cc.o"

# External object files for target run_sim
run_sim_EXTERNAL_OBJECTS =

run_sim: CMakeFiles/run_sim.dir/main.cc.o
run_sim: CMakeFiles/run_sim.dir/build.make
run_sim: CMakeFiles/run_sim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aobrien/dev/cpp/market_maker_sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable run_sim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run_sim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run_sim.dir/build: run_sim

.PHONY : CMakeFiles/run_sim.dir/build

CMakeFiles/run_sim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run_sim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run_sim.dir/clean

CMakeFiles/run_sim.dir/depend:
	cd /home/aobrien/dev/cpp/market_maker_sim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aobrien/dev/cpp/market_maker_sim /home/aobrien/dev/cpp/market_maker_sim /home/aobrien/dev/cpp/market_maker_sim/build /home/aobrien/dev/cpp/market_maker_sim/build /home/aobrien/dev/cpp/market_maker_sim/build/CMakeFiles/run_sim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/run_sim.dir/depend
