cmake_minimum_required(VERSION 3.10)
project(DitherBoy VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(DitherBoy
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/Image.cpp
    ${CMAKE_SOURCE_DIR}/Color.cpp
    ${CMAKE_SOURCE_DIR}/pallete.cpp
    ${CMAKE_SOURCE_DIR}/ordered_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/floyd_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/atkinson_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/threshold_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/ascii_dithrer.cpp
)

# Include directories
target_include_directories(DitherBoy PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Compiler flags
if(MSVC)
    target_compile_options(DitherBoy PRIVATE /W4)
else()
    target_compile_options(DitherBoy PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set output directory
set_target_properties(DitherBoy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Qt GUI target
find_package(Qt6 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
endif()

add_executable(DitherBoyQt
    ${CMAKE_SOURCE_DIR}/gui/main.cpp
    ${CMAKE_SOURCE_DIR}/gui/main_window.cpp
    ${CMAKE_SOURCE_DIR}/gui/main_window.h
)
target_include_directories(DitherBoyQt PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
)
target_link_libraries(DitherBoyQt PRIVATE Qt6::Widgets)

# ImGui + GLFW + OpenGL3 GUI target
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(DitherBoyImGui
    ${CMAKE_SOURCE_DIR}/main_imgui.cpp # To be created
    # DitherBoy core
    ${CMAKE_SOURCE_DIR}/Image.cpp
    ${CMAKE_SOURCE_DIR}/Color.cpp
    ${CMAKE_SOURCE_DIR}/pallete.cpp
    ${CMAKE_SOURCE_DIR}/floyd_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/atkinson_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/ordered_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/threshold_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/ascii_dithrer.cpp
    # ImGui core
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_demo.cpp
    # ImGui backends
    ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(DitherBoyImGui PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/imgui/backends
    ${GLFW_INCLUDE_DIRS}
)
if(APPLE)
    target_include_directories(DitherBoyImGui PRIVATE /opt/homebrew/include)
    target_link_libraries(DitherBoyImGui PRIVATE
        "-framework Cocoa" "-framework IOKit" "-framework CoreVideo"
        /opt/homebrew/lib/libglfw.3.dylib
    )
else()
    target_link_libraries(DitherBoyImGui PRIVATE
        ${GLFW_LIBRARIES}
    )
endif()
target_link_libraries(DitherBoyImGui PRIVATE
    ${OPENGL_LIBRARIES}
)

add_executable(DitherBoyWeb
    ${CMAKE_SOURCE_DIR}/web_ui/main_web.cpp
    ${CMAKE_SOURCE_DIR}/Image.cpp
    ${CMAKE_SOURCE_DIR}/Color.cpp
    ${CMAKE_SOURCE_DIR}/pallete.cpp
    ${CMAKE_SOURCE_DIR}/floyd_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/atkinson_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/ordered_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/threshold_dithrer.cpp
    ${CMAKE_SOURCE_DIR}/ascii_dithrer.cpp
)
target_include_directories(DitherBoyWeb PRIVATE
    external
    web_ui
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}
) 