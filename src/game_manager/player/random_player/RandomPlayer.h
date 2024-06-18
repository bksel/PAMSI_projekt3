//
// Created by ksel on 19/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_RANDOM_PLAYER_RANDOMPLAYER_H_
#define MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_RANDOM_PLAYER_RANDOMPLAYER_H_

#include "../IPlayer.h"

namespace game {

class RandomPlayer : public IPlayer {
  checkers::Piece::Color color;
  bool printing;

 public:
  explicit RandomPlayer(bool print = false) : printing(print) {}
  checkers::Move make_move(const checkers::Board& board) override;
  void set_color(checkers::Piece::Color _color) override { this->color = _color; }
};

}  // namespace game

#endif  // MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_RANDOM_PLAYER_RANDOMPLAYER_H_
