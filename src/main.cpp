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
  b.execute_move({{13,29}, {}});
  chkrs::print(b);
  auto pieces = chkrs::ValidMoveFinder::find_pieces(b);

  fmt::print("White pieces: ");

  return 0;
}
