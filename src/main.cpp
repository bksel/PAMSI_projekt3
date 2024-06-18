#include <fmt/core.h>

#include <iostream>

#include "checkers_logic/lib.h"

namespace chs = checkers;

int main() {
  std::cout << "Hello, World!" << std::endl;
  chs::Board b{};
  chs::print(b);
  chs::Move m{{9, 13}, {29}};
  fmt::println("{}", m.to_string());

  b.execute_move(m);
  chs::print(b);
  b.execute_move({{22, 17}, {}});
  b.execute_move({{10, 14}, {3}});
  b.execute_move({{13, 29}, {31, 24}});
  chs::print(b);
  std::vector<chs::Move> moves_red = chs::ValidMoveFinder::valid_moves_for_red(b);
  std::vector<chs::Move> moves_white = chs::ValidMoveFinder::valid_moves_for_white(b);



  chs::print(moves_white);


  fmt::print("White pieces: ");

  return 0;
}
