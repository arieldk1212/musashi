cmake_minimum_required(VERSION 3.15)
project(musashi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR)

if (APPLE)
  set(CMAKE_TOOLCHAIN_FILE "/Users/$ENV{USER}/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(CMAKE_PREFIX_PATH "/Users/$ENV{USER}/vcpkg/installed/arm64-osx/share")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(imgui CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

list(APPEND project_libraries
raylib
imgui::imgui
)

add_subdirectory(src)

target_link_libraries(src PRIVATE ${project_libraries})