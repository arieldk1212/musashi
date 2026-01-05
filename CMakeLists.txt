cmake_minimum_required(VERSION 3.20)

project(musashi LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Example executable
add_executable(my_app
    src/main.cpp
)

# Include directories (example)
target_include_directories(my_app
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
