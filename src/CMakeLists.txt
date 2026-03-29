add_library(musashi_core STATIC
  App/App.cpp
  Renderer/Shader.cpp
  Renderer/Texture.cpp
  Renderer/Camera.cpp

  ../vendor/stb_image.cpp
)

target_include_directories(musashi_core
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/vendor
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
  Musashi.cpp
)

target_link_libraries(musashi
  PRIVATE
    musashi_core
)