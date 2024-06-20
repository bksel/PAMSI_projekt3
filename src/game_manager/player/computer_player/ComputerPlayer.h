//
// Created by ksel on 19/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_COMPUTER_PLAYER_COMPUTERPLAYER_H_
#define MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_COMPUTER_PLAYER_COMPUTERPLAYER_H_

#include "../IPlayer.h"
#include "../../../draughts_algorithm/lib.h"

namespace game {

class ComputerPlayer : public IPlayer {
  checkers::Piece::Color color;
  bool printing;
  bool alpha_beta;
  draught_ai::MinMax minmax;


 public:
  explicit ComputerPlayer(bool print = false, bool alphabeta = false) : printing(print), alpha_beta(alphabeta) {}
  checkers::Move make_move(const checkers::Board& board) override;
  void set_color(checkers::Piece::Color _color) override { this->color = _color; }
};



}  // namespace game

#endif  // MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_COMPUTER_PLAYER_COMPUTERPLAYER_H_
