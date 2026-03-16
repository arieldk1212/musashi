add_library(musashi_core STATIC
  game/game.cpp
)

target_include_directories(musashi_core
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(musashi_core
  PUBLIC
    glad::glad
    glfw
    imgui::imgui
    glm::glm
)

add_executable(musashi
  musashi.cpp
)

target_link_libraries(musashi
  PRIVATE
    musashi_core
)