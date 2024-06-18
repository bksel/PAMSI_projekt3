//
// Created by ksel on 18/06/24.
//

#include "HumanPlayer.h"

#include <fmt/core.h>

#include <iostream>

namespace game {
checkers::Move HumanPlayer::make_move(const checkers::Board& board) {
  fmt::print("YOUR MOVE, YOU ARE PLAYING AS {}:\n", this->color == checkers::Piece::Color::RED ? "RED" : "WHITE");

  checkers::Visualiser::print(board);

  std::vector<checkers::Move> moves;
  if (this->color == checkers::Piece::Color::RED) {
    moves = checkers::ValidMoveFinder::valid_moves_for_red(board);
  } else {
    moves = checkers::ValidMoveFinder::valid_moves_for_white(board);
  }

  int counter = 1;
  fmt::print("Available moves:\n");
  for (const auto& move : moves) {
    fmt::print("{}: {}\n", counter, move.to_string());
    counter++;
  }

  int move_number;
  bool is_valid = false;
  while (not is_valid) {
    fmt::print("Choose move number: ");
    std::cin >> move_number;
    if (move_number > 0 and move_number <= moves.size()) {
      is_valid = true;
    } else {
      fmt::print("Invalid move number\n");
    }
  }

  return moves[move_number - 1];

}
}  // namespace game