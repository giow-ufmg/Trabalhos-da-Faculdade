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
CMAKE_COMMAND = /home/giow/Apps/clion-2018.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/giow/Apps/clion-2018.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/giow/Dropbox/GioGio/TP1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/giow/Dropbox/GioGio/TP1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TP1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TP1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP1.dir/flags.make

CMakeFiles/TP1.dir/main.c.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/giow/Dropbox/GioGio/TP1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TP1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TP1.dir/main.c.o   -c /home/giow/Dropbox/GioGio/TP1/main.c

CMakeFiles/TP1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/giow/Dropbox/GioGio/TP1/main.c > CMakeFiles/TP1.dir/main.c.i

CMakeFiles/TP1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/giow/Dropbox/GioGio/TP1/main.c -o CMakeFiles/TP1.dir/main.c.s

CMakeFiles/TP1.dir/main.c.o.requires:

.PHONY : CMakeFiles/TP1.dir/main.c.o.requires

CMakeFiles/TP1.dir/main.c.o.provides: CMakeFiles/TP1.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/TP1.dir/build.make CMakeFiles/TP1.dir/main.c.o.provides.build
.PHONY : CMakeFiles/TP1.dir/main.c.o.provides

CMakeFiles/TP1.dir/main.c.o.provides.build: CMakeFiles/TP1.dir/main.c.o


CMakeFiles/TP1.dir/mem.c.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/mem.c.o: ../mem.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/giow/Dropbox/GioGio/TP1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TP1.dir/mem.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TP1.dir/mem.c.o   -c /home/giow/Dropbox/GioGio/TP1/mem.c

CMakeFiles/TP1.dir/mem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP1.dir/mem.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/giow/Dropbox/GioGio/TP1/mem.c > CMakeFiles/TP1.dir/mem.c.i

CMakeFiles/TP1.dir/mem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP1.dir/mem.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/giow/Dropbox/GioGio/TP1/mem.c -o CMakeFiles/TP1.dir/mem.c.s

CMakeFiles/TP1.dir/mem.c.o.requires:

.PHONY : CMakeFiles/TP1.dir/mem.c.o.requires

CMakeFiles/TP1.dir/mem.c.o.provides: CMakeFiles/TP1.dir/mem.c.o.requires
	$(MAKE) -f CMakeFiles/TP1.dir/build.make CMakeFiles/TP1.dir/mem.c.o.provides.build
.PHONY : CMakeFiles/TP1.dir/mem.c.o.provides

CMakeFiles/TP1.dir/mem.c.o.provides.build: CMakeFiles/TP1.dir/mem.c.o


CMakeFiles/TP1.dir/sort.c.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/sort.c.o: ../sort.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/giow/Dropbox/GioGio/TP1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TP1.dir/sort.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TP1.dir/sort.c.o   -c /home/giow/Dropbox/GioGio/TP1/sort.c

CMakeFiles/TP1.dir/sort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP1.dir/sort.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/giow/Dropbox/GioGio/TP1/sort.c > CMakeFiles/TP1.dir/sort.c.i

CMakeFiles/TP1.dir/sort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP1.dir/sort.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/giow/Dropbox/GioGio/TP1/sort.c -o CMakeFiles/TP1.dir/sort.c.s

CMakeFiles/TP1.dir/sort.c.o.requires:

.PHONY : CMakeFiles/TP1.dir/sort.c.o.requires

CMakeFiles/TP1.dir/sort.c.o.provides: CMakeFiles/TP1.dir/sort.c.o.requires
	$(MAKE) -f CMakeFiles/TP1.dir/build.make CMakeFiles/TP1.dir/sort.c.o.provides.build
.PHONY : CMakeFiles/TP1.dir/sort.c.o.provides

CMakeFiles/TP1.dir/sort.c.o.provides.build: CMakeFiles/TP1.dir/sort.c.o


CMakeFiles/TP1.dir/heap.c.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/heap.c.o: ../heap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/giow/Dropbox/GioGio/TP1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/TP1.dir/heap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TP1.dir/heap.c.o   -c /home/giow/Dropbox/GioGio/TP1/heap.c

CMakeFiles/TP1.dir/heap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP1.dir/heap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/giow/Dropbox/GioGio/TP1/heap.c > CMakeFiles/TP1.dir/heap.c.i

CMakeFiles/TP1.dir/heap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP1.dir/heap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/giow/Dropbox/GioGio/TP1/heap.c -o CMakeFiles/TP1.dir/heap.c.s

CMakeFiles/TP1.dir/heap.c.o.requires:

.PHONY : CMakeFiles/TP1.dir/heap.c.o.requires

CMakeFiles/TP1.dir/heap.c.o.provides: CMakeFiles/TP1.dir/heap.c.o.requires
	$(MAKE) -f CMakeFiles/TP1.dir/build.make CMakeFiles/TP1.dir/heap.c.o.provides.build
.PHONY : CMakeFiles/TP1.dir/heap.c.o.provides

CMakeFiles/TP1.dir/heap.c.o.provides.build: CMakeFiles/TP1.dir/heap.c.o


# Object files for target TP1
TP1_OBJECTS = \
"CMakeFiles/TP1.dir/main.c.o" \
"CMakeFiles/TP1.dir/mem.c.o" \
"CMakeFiles/TP1.dir/sort.c.o" \
"CMakeFiles/TP1.dir/heap.c.o"

# External object files for target TP1
TP1_EXTERNAL_OBJECTS =

TP1: CMakeFiles/TP1.dir/main.c.o
TP1: CMakeFiles/TP1.dir/mem.c.o
TP1: CMakeFiles/TP1.dir/sort.c.o
TP1: CMakeFiles/TP1.dir/heap.c.o
TP1: CMakeFiles/TP1.dir/build.make
TP1: CMakeFiles/TP1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/giow/Dropbox/GioGio/TP1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable TP1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP1.dir/build: TP1

.PHONY : CMakeFiles/TP1.dir/build

CMakeFiles/TP1.dir/requires: CMakeFiles/TP1.dir/main.c.o.requires
CMakeFiles/TP1.dir/requires: CMakeFiles/TP1.dir/mem.c.o.requires
CMakeFiles/TP1.dir/requires: CMakeFiles/TP1.dir/sort.c.o.requires
CMakeFiles/TP1.dir/requires: CMakeFiles/TP1.dir/heap.c.o.requires

.PHONY : CMakeFiles/TP1.dir/requires

CMakeFiles/TP1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP1.dir/clean

CMakeFiles/TP1.dir/depend:
	cd /home/giow/Dropbox/GioGio/TP1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/giow/Dropbox/GioGio/TP1 /home/giow/Dropbox/GioGio/TP1 /home/giow/Dropbox/GioGio/TP1/cmake-build-debug /home/giow/Dropbox/GioGio/TP1/cmake-build-debug /home/giow/Dropbox/GioGio/TP1/cmake-build-debug/CMakeFiles/TP1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TP1.dir/depend

