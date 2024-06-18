//
// Created by ksel on 18/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_IPLAYER_H_
#define MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_IPLAYER_H_

#include "../../checkers_logic/lib.h"

namespace game {

class IPlayer {
 public:
  virtual checkers::Move make_move(const checkers::Board& board) = 0;
  virtual void set_color(checkers::Piece::Color color) = 0;
  virtual ~IPlayer() = default;
};

}  // namespace game

#endif  // MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_PLAYER_IPLAYER_H_
