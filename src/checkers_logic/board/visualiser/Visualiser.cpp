//
// Created by ksel on 17/06/24.
//

#include "Visualiser.h"

#include <fmt/core.h>

void checkers::Visualiser::print(const checkers::Board& board) {
  print_header();
  print_rows(board);
}
void checkers::Visualiser::print_header() {
  fmt::print("    {}", margin);
  for (int i = 0; i <= 3; i++) {
    fmt::print("{} {} ", i, i);
  }
  fmt::print("\n");
}
void checkers::Visualiser::print_rows(const checkers::Board& board) {
  int count = 1;

  constexpr std::array<int, 8> row = {1, 5, 9, 13, 17, 21, 25, 29};

  for (int i = 1; i <= 8; i++) {
    fmt::print("{}{}| ", margin, fmt::format("{:02d}", row[i - 1]));

    for (int j = 1; j <= 4; j++) {
      const checkers::Field& field = board.get_fields().at(count);

      char symbol = field_to_symbol(field);
      if (i % 2 == 0) {
        fmt::print("{} {} ", white_field, symbol);
      } else {
        fmt::print("{} {} ", symbol, white_field);
      }

      ++count;
    }

    fmt::print("\n");
  }
}
char checkers::Visualiser::field_to_symbol(checkers::Field f) {
  using namespace checkers;
  using p = checkers::Piece;
  if (f.empty) return blank_field;
  if (f.piece.color == p::WHITE) {
    if (f.piece.type == p::QUEEN) return 'W';
    return 'w';
  } else {
    if (f.piece.type == p::QUEEN) return 'R';
    return 'r';
  }
}
