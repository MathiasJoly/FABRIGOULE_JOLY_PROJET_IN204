# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mathias/TestProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mathias/TestProject/build

# Include any dependencies generated for this target.
include CMakeFiles/TestProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestProject.dir/flags.make

CMakeFiles/TestProject.dir/test_wx.o: CMakeFiles/TestProject.dir/flags.make
CMakeFiles/TestProject.dir/test_wx.o: ../test_wx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mathias/TestProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestProject.dir/test_wx.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestProject.dir/test_wx.o -c /home/mathias/TestProject/test_wx.cpp

CMakeFiles/TestProject.dir/test_wx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestProject.dir/test_wx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mathias/TestProject/test_wx.cpp > CMakeFiles/TestProject.dir/test_wx.i

CMakeFiles/TestProject.dir/test_wx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestProject.dir/test_wx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mathias/TestProject/test_wx.cpp -o CMakeFiles/TestProject.dir/test_wx.s

CMakeFiles/TestProject.dir/test_wx.o.requires:

.PHONY : CMakeFiles/TestProject.dir/test_wx.o.requires

CMakeFiles/TestProject.dir/test_wx.o.provides: CMakeFiles/TestProject.dir/test_wx.o.requires
	$(MAKE) -f CMakeFiles/TestProject.dir/build.make CMakeFiles/TestProject.dir/test_wx.o.provides.build
.PHONY : CMakeFiles/TestProject.dir/test_wx.o.provides

CMakeFiles/TestProject.dir/test_wx.o.provides.build: CMakeFiles/TestProject.dir/test_wx.o


# Object files for target TestProject
TestProject_OBJECTS = \
"CMakeFiles/TestProject.dir/test_wx.o"

# External object files for target TestProject
TestProject_EXTERNAL_OBJECTS =

TestProject: CMakeFiles/TestProject.dir/test_wx.o
TestProject: CMakeFiles/TestProject.dir/build.make
TestProject: CMakeFiles/TestProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mathias/TestProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestProject.dir/build: TestProject

.PHONY : CMakeFiles/TestProject.dir/build

CMakeFiles/TestProject.dir/requires: CMakeFiles/TestProject.dir/test_wx.o.requires

.PHONY : CMakeFiles/TestProject.dir/requires

CMakeFiles/TestProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestProject.dir/clean

CMakeFiles/TestProject.dir/depend:
	cd /home/mathias/TestProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mathias/TestProject /home/mathias/TestProject /home/mathias/TestProject/build /home/mathias/TestProject/build /home/mathias/TestProject/build/CMakeFiles/TestProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestProject.dir/depend

