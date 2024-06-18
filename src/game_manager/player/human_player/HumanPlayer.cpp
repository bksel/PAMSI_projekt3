//
// Created by ksel on 18/06/24.
//

#include "HumanPlayer.h"

#include <fmt/core.h>

namespace game {
checkers::Move HumanPlayer::make_move(const checkers::Board& board) {

  fmt::print("YOUR MOVE:\n");

  checkers::Visualiser::print(board);

  checkers::Move move;


  return checkers::Move{{1, 2}, {}}; }
}  // namespace game