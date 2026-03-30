add_library(musashi_core STATIC
  app/app.cc
  renderer/shader.cc
  renderer/texture.cc
  renderer/camera.cc

  ../vendor/stb_image.cc
)

target_include_directories(musashi_core
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(musashi_core
  PUBLIC
  glad::glad
  glfw
  imgui::imgui
  glm::glm
  assimp::assimp
)

add_executable(musashi
  musashi.cc
)

target_link_libraries(musashi
  PRIVATE
  musashi_core
)