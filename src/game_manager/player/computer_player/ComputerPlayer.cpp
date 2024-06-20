//
// Created by ksel on 19/06/24.
//

#include "ComputerPlayer.h"

namespace game {
checkers::Move ComputerPlayer::make_move(const checkers::Board& board) {
  checkers::Move move;
  if (alpha_beta) {
    move = minmax.get_best_move_alphabeta(board, 5, color);
  }
  else {
    move = minmax.get_best_move(board, 3, color);
  }

  return move;
}
}  // namespace game