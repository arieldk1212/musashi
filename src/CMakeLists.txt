# glad
add_library(glad STATIC ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/vendor/glad/include)

# imgui
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

# musashi - engine
file(GLOB_RECURSE ENGINE_SOURCES "engine/*.cc")
add_library(engine STATIC ${ENGINE_SOURCES} ${PROJECT_SOURCE_DIR}/vendor/stb_image.cc)
target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/src/engine ${PROJECT_SOURCE_DIR})
target_link_libraries(engine PUBLIC glfw imgui assimp glad glm::glm spdlog)

# dead verse - game
file(GLOB_RECURSE GAME_SOURCES "game/*.cc")
add_library(game STATIC ${GAME_SOURCES})
target_include_directories(game PUBLIC ${PROJECT_SOURCE_DIR}/src/game ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/engine)
target_link_libraries(game PUBLIC glfw imgui assimp glad glm::glm spdlog)

# main
add_executable(main game)
target_link_libraries(main PUBLIC engine game)