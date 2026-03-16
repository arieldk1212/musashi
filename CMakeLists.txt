<<<<<<< HEAD
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
=======
cmake_minimum_required(VERSION 3.15)
project(musashi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (APPLE)
  set(CMAKE_TOOLCHAIN_FILE
      "/Users/$ENV{USER}/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
  set(CMAKE_PREFIX_PATH "/Users/$ENV{USER}/vcpkg/installed/arm64-osx/share")
endif()

find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
>>>>>>> 0c5c218fcdf3c0486441f398e6a373ebdfd946d2
