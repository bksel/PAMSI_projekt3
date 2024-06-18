#include <fmt/core.h>

#include <iostream>

#include "checkers_logic/lib.h"
#include "game_manager/lib.h"

namespace chs = checkers;

void test_board() {
  std::cout << "Hello, World!" << std::endl;
  chs::Board b{};
  chs::Visualiser::print(b);
  chs::Move m{{9, 13}, {29}};
  fmt::println("{}", m.to_string());

  b.execute_move(m);
  chs::Visualiser::print(b);
  b.execute_move({{22, 17}, {}});
  b.execute_move({{10, 14}, {3}});
  b.execute_move({{13, 29}, {31, 24}});
  b.execute_move({{28, 3}, {17}});
  b.execute_move({{21, 17}, {1, 2, 4, 5, 6, 7, 8, 11, 12, 17}});
  chs::Visualiser::print(b);
  std::vector<chs::Move> moves_red = chs::ValidMoveFinder::valid_moves_for_red(b);
  std::vector<chs::Move> moves_white = chs::ValidMoveFinder::valid_moves_for_white(b);
//  chs::print(moves_red);

    chs::print(moves_white);

  fmt::print("White pieces: ");
}

void test_game_manager() {
  //  game::HumanPlayer white{};
  //  game::HumanPlayer red{};

  game::RandomPlayer white{};
  game::RandomPlayer red{true};

  game::GameManager gm{white, red};

  gm.play_game();
}

int main() {
//    test_board();
  test_game_manager();
  return 0;
}
