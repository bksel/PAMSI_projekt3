//
// Created by ksel on 19/06/24.
//

#include "HeuristicAnalyser.h"

#include <fmt/args.h>

#include "../../valid_move_finder/ValidMoveFinder.h"

namespace checkers {

int HeuristicAnalyser::piece_opponent_edge(const Board& board) {
  const std::vector<checkers::Field>& fields = board.get_fields();

  int result = 0;

  for (const Field& f : fields) {
    if (f.empty) continue;
    if (f.piece.type == Piece::QUEEN) continue;
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
      result -= distance;  // minus because we want to be closer to the center
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
int HeuristicAnalyser::under_attack(const Board& board) {
  int result = 0;

  for (const checkers::Field& f : board.get_fields()) {
    if (f.empty) continue;
    if (f.piece.color == Piece::WHITE) {
      int attacks = calculate_attacks(board, f.id);
      result -= attacks;
    } else {
      int attacks = calculate_attacks(board, f.id);
      result += attacks;
    }
  }

  return result;
}
int HeuristicAnalyser::calculate_attacks(const Board& board, int id) {
  const Field& f = board.get_fields().at(id);
  checkers::Piece::Color opponent = f.piece.color == Piece::WHITE ? Piece::RED : Piece::WHITE;
  int attacks = 0;
  if (f.upper_left != -1 && f.lower_right == -1) {
    const Field& ul = board.get_fields().at(f.upper_left);
    const Field& lr = board.get_fields().at(ul.lower_right);

    if (ul.empty && not lr.empty && lr.piece.color == opponent) {
      attacks++;
    } else if (not ul.empty && ul.piece.color == opponent && lr.empty) {
      attacks++;
    }
  }

  if (f.upper_right != -1 && f.lower_left == -1) {
    const Field& ur = board.get_fields().at(f.upper_right);
    const Field& ll = board.get_fields().at(ur.lower_left);

    if (ur.empty && not ll.empty && ll.piece.color == opponent) {
      attacks++;
    } else if (not ur.empty && ur.piece.color == opponent && ll.empty) {
      attacks++;
    }
  }

  return attacks;
}
int HeuristicAnalyser::mobility(const Board& board) {
  int result = 0;

  for (const Field& f : board.get_fields()) {
    if (f.empty) continue;
    if (f.piece.color == Piece::WHITE) {
      std::vector<Move> moves = ValidMoveFinder::valid_moves_for_white(board);
      int attacks = calculate_attacks(board, f.id);
      if (attacks > 0) {
        result -= moves.size();
      } else {
        result += moves.size();
      }
    } else {
      std::vector<Move> moves = ValidMoveFinder::valid_moves_for_red(board);
      int attacks = calculate_attacks(board, f.id);
      if (attacks >  0) {
        result += moves.size();
      } else {
        result -= moves.size();
      }
    }
  }

  return result;
}
}  // namespace checkers