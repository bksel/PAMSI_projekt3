//
// Created by ksel on 18/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_HUMAN_PLAYER_HUMANPLAYER_H_
#define MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_HUMAN_PLAYER_HUMANPLAYER_H_

#include "../IPlayer.h"

namespace game {

class HumanPlayer : public IPlayer {
 public:
  checkers::Piece::Color color;

  checkers::Move make_move(const checkers::Board& board) override;
  void set_color(checkers::Piece::Color _color) override { this->color = _color; }
};

}  // namespace game

#endif  // MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_HUMAN_PLAYER_HUMANPLAYER_H_
