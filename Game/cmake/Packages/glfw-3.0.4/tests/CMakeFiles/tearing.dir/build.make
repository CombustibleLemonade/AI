# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jan/GitRepository/AI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jan/GitRepository/AI/Game

# Include any dependencies generated for this target.
include cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/depend.make

# Include the progress variables for this target.
include cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/progress.make

# Include the compile flags for this target's objects.
include cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/flags.make

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o: cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/flags.make
cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o: ../cmake/Packages/glfw-3.0.4/tests/tearing.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jan/GitRepository/AI/Game/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o"
	cd /home/jan/GitRepository/AI/Game/cmake/Packages/glfw-3.0.4/tests && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tearing.dir/tearing.c.o   -c /home/jan/GitRepository/AI/cmake/Packages/glfw-3.0.4/tests/tearing.c

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tearing.dir/tearing.c.i"
	cd /home/jan/GitRepository/AI/Game/cmake/Packages/glfw-3.0.4/tests && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/jan/GitRepository/AI/cmake/Packages/glfw-3.0.4/tests/tearing.c > CMakeFiles/tearing.dir/tearing.c.i

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tearing.dir/tearing.c.s"
	cd /home/jan/GitRepository/AI/Game/cmake/Packages/glfw-3.0.4/tests && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/jan/GitRepository/AI/cmake/Packages/glfw-3.0.4/tests/tearing.c -o CMakeFiles/tearing.dir/tearing.c.s

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.requires:
.PHONY : cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.requires

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.provides: cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.requires
	$(MAKE) -f cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/build.make cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.provides.build
.PHONY : cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.provides

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.provides.build: cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o

# Object files for target tearing
tearing_OBJECTS = \
"CMakeFiles/tearing.dir/tearing.c.o"

# External object files for target tearing
tearing_EXTERNAL_OBJECTS =

cmake/Packages/glfw-3.0.4/tests/tearing: cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o
cmake/Packages/glfw-3.0.4/tests/tearing: cmake/Packages/glfw-3.0.4/src/libglfw3.a
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libGLU.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libX11.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/librt.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libXrandr.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libXi.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/librt.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libm.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libGL.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libXrandr.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libXi.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libm.so
cmake/Packages/glfw-3.0.4/tests/tearing: /usr/lib/x86_64-linux-gnu/libGL.so
cmake/Packages/glfw-3.0.4/tests/tearing: cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/build.make
cmake/Packages/glfw-3.0.4/tests/tearing: cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable tearing"
	cd /home/jan/GitRepository/AI/Game/cmake/Packages/glfw-3.0.4/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tearing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/build: cmake/Packages/glfw-3.0.4/tests/tearing
.PHONY : cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/build

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/requires: cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/tearing.c.o.requires
.PHONY : cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/requires

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/clean:
	cd /home/jan/GitRepository/AI/Game/cmake/Packages/glfw-3.0.4/tests && $(CMAKE_COMMAND) -P CMakeFiles/tearing.dir/cmake_clean.cmake
.PHONY : cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/clean

cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/depend:
	cd /home/jan/GitRepository/AI/Game && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jan/GitRepository/AI /home/jan/GitRepository/AI/cmake/Packages/glfw-3.0.4/tests /home/jan/GitRepository/AI/Game /home/jan/GitRepository/AI/Game/cmake/Packages/glfw-3.0.4/tests /home/jan/GitRepository/AI/Game/cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cmake/Packages/glfw-3.0.4/tests/CMakeFiles/tearing.dir/depend

