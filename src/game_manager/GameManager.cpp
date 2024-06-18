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
void GameManager::play_game() {
  bool is_game_over = false;
  winner = GameWinner::NOT_FINISHED;
  while (!is_game_over) {
    play_turn();
    is_game_over = check_if_draw() || check_if_win();
  }
}
bool GameManager::check_if_draw() {
  checkers::Board::Statistics stats = board.get_statistics();
  int whites = stats.white_pieces + stats.white_kings;
  int reds = stats.black_pieces + stats.black_kings;

  if (whites == 0 || reds == 0) {
    return true;
  }
  if (whites == 1 && reds == 1) {
    return true;
  }

  return false;
}
bool GameManager::check_if_win() {
  if (winner == GameWinner::NOT_FINISHED or winner == GameWinner::DRAW) return false;
  return true;
}

void GameManager::play_turn() {
  checkers::Move move;
  IPlayer& p1 = first_player_color == checkers::Piece::Color::WHITE ? player1 : player2;
  IPlayer& p2 = first_player_color == checkers::Piece::Color::WHITE ? player2 : player1;

  move = p1.make_move(board);
  board.execute_move(move);
  move = p2.make_move(board);
  board.execute_move(move);
}

}  // namespace game