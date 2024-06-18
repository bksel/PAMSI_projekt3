cmake_minimum_required(VERSION 3.28)
project(miniprojekt3_warcaby)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES TRUE)

# add debug variable
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")



add_library(checkers_logic STATIC
        src/checkers_logic/board/Board.cpp
        src/checkers_logic/board/Board.h
        src/checkers_logic/lib.h
        src/checkers_logic/field/Field.cpp
        src/checkers_logic/field/Field.h
        src/checkers_logic/piece/Piece.cpp
        src/checkers_logic/piece/Piece.h
        src/checkers_logic/move/Move.cpp
        src/checkers_logic/move/Move.h
        src/checkers_logic/heuristics/heuristic_function.h
        src/checkers_logic/board/visualiser/Visualiser.cpp
        src/checkers_logic/board/visualiser/Visualiser.h
        src/checkers_logic/valid_move_finder/ValidMoveFinder.cpp
        src/checkers_logic/valid_move_finder/ValidMoveFinder.h
        src/game_manager/player/IPlayer.h
        src/game_manager/player/human_player/HumanPlayer.cpp
        src/game_manager/player/human_player/HumanPlayer.h


)

add_executable(miniprojekt3_warcaby src/main.cpp
        src/game_manager/GameManager.cpp
        src/game_manager/GameManager.h
        src/game_manager/lib.h
        src/game_manager/player/random_player/RandomPlayer.cpp
        src/game_manager/player/random_player/RandomPlayer.h

)

find_package(fmt REQUIRED)
target_link_libraries(miniprojekt3_warcaby PRIVATE fmt::fmt checkers_logic)