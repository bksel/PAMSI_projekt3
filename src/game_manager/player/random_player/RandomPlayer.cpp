//
// Created by ksel on 19/06/24.
//

#include "RandomPlayer.h"

#include <fmt/core.h>

#include <random>

namespace game {
checkers::Move RandomPlayer::make_move(const checkers::Board& board) {
  std::vector<checkers::Move> moves;
  if (this->color == checkers::Piece::Color::RED) {
    moves = checkers::ValidMoveFinder::valid_moves_for_red(board);
  } else {
    moves = checkers::ValidMoveFinder::valid_moves_for_white(board);
  }

  // random device chooses random move
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, moves.size() - 1);

  int random_move = dis(gen);
  checkers::Move move = moves[random_move];

  if (printing) {
    fmt::print("RANDOM PLAYER IS PLAYING AS {}:\n",
               this->color == checkers::Piece::Color::RED ? "RED" : "WHITE");
    checkers::Visualiser::print(board);
    fmt::print("Chosen move: {}\n", move.to_string());
  }

  return move;
}
}  // namespace game