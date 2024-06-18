//
// Created by ksel on 18/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_GAMEMANAGER_H_
#define MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_GAMEMANAGER_H_

#include "player/IPlayer.h"

namespace game {

enum class GameWinner { PLAYER1, PLAYER2, DRAW, NOT_FINISHED };

class GameManager {
  IPlayer& player1;
  IPlayer& player2;

  checkers::Board board;

  GameWinner winner = GameWinner::NOT_FINISHED;
  checkers::Piece::Color first_player_color = checkers::Piece::Color::WHITE;
  checkers::Piece::Color second_player_color = checkers::Piece::Color::RED;

  void switch_colors();
  bool check_if_draw();
  bool check_if_win();
  void play_turn();

 public:
  GameManager(IPlayer& player1, IPlayer& player2) : player1(player1), player2(player2) {
    player1.set_color(first_player_color);
    player2.set_color(second_player_color);
    board = {};
  }
  void set_first_player_color(checkers::Piece::Color color) { first_player_color = color; }

  void play_game();
};

}  // namespace game

#endif  // MINIPROJEKT3_WARCABY_SRC_GAME_MANAGER_GAMEMANAGER_H_
