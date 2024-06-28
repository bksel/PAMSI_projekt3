//
// Created by ksel on 19/06/24.
//

#include "ComputerPlayer.h"

namespace game {
checkers::Move ComputerPlayer::make_move(const checkers::Board& board) {
  checkers::Move move;
  if (alpha_beta) {
    fmt::print("Calling alpha-beta\n");
    move = minmax.get_best_move_alphabeta(board, 7, color);
  }
  else {
    fmt::print("Calling minmax\n");
    move = minmax.get_best_move(board, 3, color);
  }

  return move;
}
}  // namespace game