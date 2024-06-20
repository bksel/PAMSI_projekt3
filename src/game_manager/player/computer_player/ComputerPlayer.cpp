//
// Created by ksel on 19/06/24.
//

#include "ComputerPlayer.h"

namespace game {
checkers::Move ComputerPlayer::make_move(const checkers::Board& board) {

  checkers::Move move = minmax.get_best_move(board,3, color);

  return move;

}
}  // namespace game