//
// Created by ksel on 19/06/24.
//

#include "HeuristicAnalyser.h"

namespace checkers {

int HeuristicAnalyser::piece_opponent_edge(const Board& board) {
  const std::vector<checkers::Field>& fields = board.get_fields();

  int result = 0;

  for (const Field& f : fields) {
    if (f.empty) continue;
    if (f.piece.color == Piece::WHITE) {
      int distance = 7 - calculate_row(f.id);
      result += distance;
    } else {
      int distance = calculate_row(f.id);
      result -= distance;
    }
  }

  return result;
}
int HeuristicAnalyser::calculate_row(int id) {
  if (id < 5) {
    return 0;
  } else if (id < 9) {
    return 1;
  } else if (id < 13) {
    return 2;
  } else if (id < 17) {
    return 3;
  } else if (id < 21) {
    return 4;
  } else if (id < 25) {
    return 5;
  } else if (id < 29) {
    return 6;
  } else {
    return 7;
  }
}
int HeuristicAnalyser::piece_board_center(const Board& board) {
  int result = 0;

  float middle_column = 1.5;

  for (const Field& f : board.get_fields()) {
    if (f.empty) continue;

    if (f.piece.color == Piece::WHITE) {
      int distance = std::abs(middle_column - calculate_column(f.id));
      result -= distance; // minus because we want to be closer to the center
    } else {
      int distance = std::abs(middle_column - calculate_column(f.id));
      result += distance;
    }

  }

  return result;
}
int HeuristicAnalyser::calculate_column(int id) {
  if (id % 4 == 0) {
    return 0;
  } else if (id % 4 == 1) {
    return 1;
  } else if (id % 4 == 2) {
    return 2;
  } else {
    return 3;
  }

  return 0;
}
}  // namespace checkers