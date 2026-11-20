cmake_minimum_required(VERSION 3.20)

project(EmeraldEngine
    VERSION 0.1.0
    DESCRIPTION "A modular 2D engine"
    LANGUAGES CXX
)

# C++ configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find dependencies
find_package(SDL2 CONFIG REQUIRED)

# Engine executable
add_executable(EmeraldEngine
    src/main.cpp

    src/Application.cpp
)

# Header directories
target_include_directories(EmeraldEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link SDL
target_link_libraries(EmeraldEngine PRIVATE
    SDL2::SDL2
)

target_compile_definitions(EmeraldEngine PRIVATE SDL_MAIN_HANDLED)

# Compiler warnings
if(MSVC)
    target_compile_options(EmeraldEngine PRIVATE /W4)
else()
    target_compile_options(EmeraldEngine PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Place executable in build/bin
set_target_properties(EmeraldEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/bin"
)

# copy SDL2.dll
add_custom_command(TARGET EmeraldEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/ucrt64/bin/SDL2.dll"
        "$<TARGET_FILE_DIR:EmeraldEngine>"
)