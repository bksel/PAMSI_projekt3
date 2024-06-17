#include <iostream>
#include <fmt/core.h>

#include "checkers_logic/lib.h"

namespace chkrs = checkers;

int main() {
  std::cout << "Hello, World!" << std::endl;
  chkrs::Board b{};
  chkrs::print(b);
  chkrs::Move m{{9, 13, 11, 23}, {26}};
  fmt::println("{}", m.to_string());

  b.execute_move(m);
  chkrs::print(b);
  return 0;
}
