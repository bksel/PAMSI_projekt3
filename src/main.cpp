#include <iostream>
#include <fmt/core.h>

#include "checkers_logic/lib.h"

namespace chkrs = checkers;

int main() {
  std::cout << "Hello, World!" << std::endl;
  chkrs::Board b{};
  chkrs::print(b);
  chkrs::Move m{{9, 13}, {29}};
  fmt::println("{}", m.to_string());

  b.execute_move(m);
  chkrs::print(b);
  b.execute_move({{22,17}, {}});
  b.execute_move({{10,14}, {3}});
  chkrs::print(b);
  std::vector<chkrs::Move> moves_red = chkrs::ValidMoveFinder::valid_moves_for_red(b);
  std::vector<chkrs::Move> moves_white = chkrs::ValidMoveFinder::valid_moves_for_white(b);

  auto pieces = chkrs::ValidMoveFinder::find_pieces(b);

  fmt::print("White pieces: ");

  return 0;
}
