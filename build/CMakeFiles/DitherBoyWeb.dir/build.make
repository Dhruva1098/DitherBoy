# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dhruvasharma/Documents/projects-cpp/DitherBoy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build

# Include any dependencies generated for this target.
include CMakeFiles/DitherBoyWeb.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DitherBoyWeb.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DitherBoyWeb.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DitherBoyWeb.dir/flags.make

DitherBoyWeb_autogen/timestamp: /opt/homebrew/share/qt/libexec/moc
DitherBoyWeb_autogen/timestamp: /opt/homebrew/share/qt/libexec/uic
DitherBoyWeb_autogen/timestamp: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target DitherBoyWeb"
	/opt/homebrew/bin/cmake -E cmake_autogen /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles/DitherBoyWeb_autogen.dir/AutogenInfo.json ""
	/opt/homebrew/bin/cmake -E touch /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/DitherBoyWeb_autogen/timestamp

CMakeFiles/DitherBoyWeb.dir/codegen:
.PHONY : CMakeFiles/DitherBoyWeb.dir/codegen

CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o: DitherBoyWeb_autogen/mocs_compilation.cpp
CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/DitherBoyWeb_autogen/mocs_compilation.cpp

CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/DitherBoyWeb_autogen/mocs_compilation.cpp > CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.i

CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/DitherBoyWeb_autogen/mocs_compilation.cpp -o CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.s

CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/web_ui/main_web.cpp
CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/web_ui/main_web.cpp

CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/web_ui/main_web.cpp > CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.i

CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/web_ui/main_web.cpp -o CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.s

CMakeFiles/DitherBoyWeb.dir/Image.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/Image.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Image.cpp
CMakeFiles/DitherBoyWeb.dir/Image.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DitherBoyWeb.dir/Image.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/Image.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/Image.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/Image.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Image.cpp

CMakeFiles/DitherBoyWeb.dir/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/Image.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Image.cpp > CMakeFiles/DitherBoyWeb.dir/Image.cpp.i

CMakeFiles/DitherBoyWeb.dir/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/Image.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Image.cpp -o CMakeFiles/DitherBoyWeb.dir/Image.cpp.s

CMakeFiles/DitherBoyWeb.dir/Color.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/Color.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Color.cpp
CMakeFiles/DitherBoyWeb.dir/Color.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/DitherBoyWeb.dir/Color.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/Color.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/Color.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/Color.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Color.cpp

CMakeFiles/DitherBoyWeb.dir/Color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/Color.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Color.cpp > CMakeFiles/DitherBoyWeb.dir/Color.cpp.i

CMakeFiles/DitherBoyWeb.dir/Color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/Color.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/Color.cpp -o CMakeFiles/DitherBoyWeb.dir/Color.cpp.s

CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/pallete.cpp
CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/pallete.cpp

CMakeFiles/DitherBoyWeb.dir/pallete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/pallete.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/pallete.cpp > CMakeFiles/DitherBoyWeb.dir/pallete.cpp.i

CMakeFiles/DitherBoyWeb.dir/pallete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/pallete.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/pallete.cpp -o CMakeFiles/DitherBoyWeb.dir/pallete.cpp.s

CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/floyd_dithrer.cpp
CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/floyd_dithrer.cpp

CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/floyd_dithrer.cpp > CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.i

CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/floyd_dithrer.cpp -o CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.s

CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/atkinson_dithrer.cpp
CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/atkinson_dithrer.cpp

CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/atkinson_dithrer.cpp > CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.i

CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/atkinson_dithrer.cpp -o CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.s

CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ordered_dithrer.cpp
CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ordered_dithrer.cpp

CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ordered_dithrer.cpp > CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.i

CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ordered_dithrer.cpp -o CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.s

CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/threshold_dithrer.cpp
CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/threshold_dithrer.cpp

CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/threshold_dithrer.cpp > CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.i

CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/threshold_dithrer.cpp -o CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.s

CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/flags.make
CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o: /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ascii_dithrer.cpp
CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o: CMakeFiles/DitherBoyWeb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o -MF CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o.d -o CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o -c /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ascii_dithrer.cpp

CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ascii_dithrer.cpp > CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.i

CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/ascii_dithrer.cpp -o CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.s

# Object files for target DitherBoyWeb
DitherBoyWeb_OBJECTS = \
"CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/Image.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/Color.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o" \
"CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o"

# External object files for target DitherBoyWeb
DitherBoyWeb_EXTERNAL_OBJECTS =

DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/DitherBoyWeb_autogen/mocs_compilation.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/web_ui/main_web.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/Image.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/Color.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/pallete.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/floyd_dithrer.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/atkinson_dithrer.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/ordered_dithrer.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/threshold_dithrer.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/ascii_dithrer.cpp.o
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/build.make
DitherBoyWeb: CMakeFiles/DitherBoyWeb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable DitherBoyWeb"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DitherBoyWeb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DitherBoyWeb.dir/build: DitherBoyWeb
.PHONY : CMakeFiles/DitherBoyWeb.dir/build

CMakeFiles/DitherBoyWeb.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DitherBoyWeb.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DitherBoyWeb.dir/clean

CMakeFiles/DitherBoyWeb.dir/depend: DitherBoyWeb_autogen/timestamp
	cd /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dhruvasharma/Documents/projects-cpp/DitherBoy /Users/dhruvasharma/Documents/projects-cpp/DitherBoy /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build /Users/dhruvasharma/Documents/projects-cpp/DitherBoy/build/CMakeFiles/DitherBoyWeb.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/DitherBoyWeb.dir/depend

