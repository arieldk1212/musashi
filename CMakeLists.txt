cmake_minimum_required(VERSION 3.15)

if (APPLE)
set(CMAKE_TOOLCHAIN_FILE
"/Users/$ENV{USER}/vcpkg/scripts/buildsystems/vcpkg.cmake"
CACHE STRING "")
set(CMAKE_PREFIX_PATH "/Users/$ENV{USER}/vcpkg/installed/arm64-osx/share")
endif()

project(musashi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/vendor)

add_subdirectory(src)
