# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /home/daddabarba/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/daddabarba/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daddabarba/CLionProjects/shell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daddabarba/CLionProjects/shell

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/daddabarba/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/daddabarba/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/daddabarba/CLionProjects/shell/CMakeFiles /home/daddabarba/CLionProjects/shell/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/daddabarba/CLionProjects/shell/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named shell

# Build rule for target.
shell: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 shell
.PHONY : shell

# fast build rule for target.
shell/fast:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/build
.PHONY : shell/fast

CommandList.o: CommandList.c.o

.PHONY : CommandList.o

# target to build an object file
CommandList.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/CommandList.c.o
.PHONY : CommandList.c.o

CommandList.i: CommandList.c.i

.PHONY : CommandList.i

# target to preprocess a source file
CommandList.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/CommandList.c.i
.PHONY : CommandList.c.i

CommandList.s: CommandList.c.s

.PHONY : CommandList.s

# target to generate assembly for a file
CommandList.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/CommandList.c.s
.PHONY : CommandList.c.s

Program.o: Program.c.o

.PHONY : Program.o

# target to build an object file
Program.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/Program.c.o
.PHONY : Program.c.o

Program.i: Program.c.i

.PHONY : Program.i

# target to preprocess a source file
Program.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/Program.c.i
.PHONY : Program.c.i

Program.s: Program.c.s

.PHONY : Program.s

# target to generate assembly for a file
Program.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/Program.c.s
.PHONY : Program.c.s

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/main.c.s
.PHONY : main.c.s

prompt.o: prompt.c.o

.PHONY : prompt.o

# target to build an object file
prompt.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/prompt.c.o
.PHONY : prompt.c.o

prompt.i: prompt.c.i

.PHONY : prompt.i

# target to preprocess a source file
prompt.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/prompt.c.i
.PHONY : prompt.c.i

prompt.s: prompt.c.s

.PHONY : prompt.s

# target to generate assembly for a file
prompt.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/prompt.c.s
.PHONY : prompt.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... shell"
	@echo "... edit_cache"
	@echo "... CommandList.o"
	@echo "... CommandList.i"
	@echo "... CommandList.s"
	@echo "... Program.o"
	@echo "... Program.i"
	@echo "... Program.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... prompt.o"
	@echo "... prompt.i"
	@echo "... prompt.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

