//
// Created by ksel on 18/06/24.
//

#include "GameManager.h"

namespace game {
void GameManager::switch_colors() {
  std::swap(first_player_color, second_player_color);
  player1.set_color(first_player_color);
  player2.set_color(second_player_color);
}
}  // namespace game