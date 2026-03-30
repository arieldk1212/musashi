add_library(glad STATIC ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/vendor/glad/include)

set(IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
  ${PROJECT_SOURCE_DIR}/vendor/imgui
  ${PROJECT_SOURCE_DIR}/vendor/imgui/backends
)
target_link_libraries(imgui PUBLIC glfw)

add_library(musashi_core STATIC
  app/app.cc
  renderer/shader.cc
  renderer/texture.cc
  renderer/camera.cc
  renderer/mesh.cc
  renderer/model.cc

  ${PROJECT_SOURCE_DIR}/vendor/stb_image.cc
)

target_include_directories(musashi_core
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(musashi_core
  PUBLIC
  glfw
  imgui
  assimp
  glad
  glm::glm
)

add_executable(musashi
  musashi.cc
)

target_link_libraries(musashi
  PRIVATE
  musashi_core
)