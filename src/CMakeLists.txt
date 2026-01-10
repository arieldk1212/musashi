list(APPEND sources
musashi.cpp

game/game.cpp
)

add_library(src STATIC ${sources})

add_executable(musashi ${sources})

target_link_libraries(musashi PRIVATE src ${project_libraries})