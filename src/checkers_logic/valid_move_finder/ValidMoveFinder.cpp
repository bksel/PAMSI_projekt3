//
// Created by ksel on 17/06/24.
//

#include "ValidMoveFinder.h"

#include <fmt/core.h>

namespace checkers {
ValidMoveFinder::Pieces ValidMoveFinder::find_pieces(const Board& board) {
  Pieces pieces;
  for (const Field& f : board.get_fields()) {
    if (f.empty) continue;
    if (f.piece.color == Piece::Color::WHITE) {
      if (f.piece.type == Piece::Type::QUEEN) {
        pieces.white_queens.emplace_back(f.id);
      } else {
        pieces.white_pieces.emplace_back(f.id);
      }
    } else {
      if (f.piece.type == Piece::Type::QUEEN) {
        pieces.red_queens.emplace_back(f.id);
      } else {
        pieces.red_pieces.emplace_back(f.id);
      }
    }
  }

  return std::move(pieces);
}

std::vector<Move> ValidMoveFinder::find_moves(const ValidMoveFinder::ParentState& state) {
  ValidMoveFinder::ParentState new_state = state;
  //  Board b = state.original_board;
  //  b.execute_move(state.move);
  //
  //  const Field& f = b.get_fields()[state.index];
  //  new_state.type = f.piece.type;
  promote_if_possible(new_state);
  if (new_state.index == 29) {
    fmt::print("AAAA DEBUG\n");
  }

  std::vector<Move> moves, m;
  if (state.color == Piece::WHITE) {
    if (state.type == Piece::NORMAL) {
      m = moves_for_normal_white(state);
    } else if (state.type == Piece::QUEEN) {
      m = moves_for_queen(state);
    }
  } else if (state.color == Piece::RED) {
    if (state.type == Piece::NORMAL) {
      m = moves_for_normal_red(state);
    } else if (state.type == Piece::QUEEN) {
      m = moves_for_queen(state);
    }
  }

  moves.insert(moves.end(), m.begin(), m.end());

  return moves;
}
std::vector<Move> ValidMoveFinder::valid_moves_for_white(const Board& board) {
  Pieces pieces = find_pieces(board);
  std::vector<Move> moves;
  for (int id : pieces.white_pieces) {
    ParentState state{id, false, Piece::WHITE, Piece::NORMAL, board, Move{{id}, {}}};
    std::vector<Move> piece_moves = find_moves(state);
    moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
  }
  moves = leave_only_longest_move_sequences(moves);
  return moves;
}
std::vector<Move> ValidMoveFinder::valid_moves_for_red(const Board& board) {
  Pieces pieces = find_pieces(board);
  std::vector<Move> moves;
  for (int id : pieces.red_pieces) {
    ParentState state{id, false, Piece::RED, Piece::NORMAL, board, Move{{id}, {}}};
    std::vector<Move> piece_moves = find_moves(state);
    moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
  }
  for (int id : pieces.red_queens) {
    ParentState state{id, false, Piece::RED, Piece::QUEEN, board, Move{{id}, {}}};
    std::vector<Move> piece_moves = find_moves(state);
    moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
  }
  moves = leave_only_longest_move_sequences(moves);

  return moves;
}
std::vector<Move> ValidMoveFinder::leave_only_longest_move_sequences(std::vector<Move> moves) {
  // find move with the longest beating chain
  int max_length = 0;
  for (Move& m : moves) {
    if (m.removed_pieces.size() > max_length) {
      max_length = static_cast<int>(m.removed_pieces.size());
    }
  }

  fmt::print("Max length: {}\n", max_length);

  // remove all moves that are not the longest
  moves.erase(
      std::remove_if(moves.begin(), moves.end(),
                     [max_length](const Move& m) { return m.removed_pieces.size() < max_length; }),
      moves.end());

  return moves;
}
void ValidMoveFinder::promote_if_possible(ValidMoveFinder::ParentState& state) {
  const int id = state.index;
  if (state.color == Piece::WHITE) {
    if (1 <= id and id <= 4) {
      state.type = Piece::QUEEN;
    }
  } else if (state.color == Piece::RED) {
    if (29 <= id and id <= 32) {
      state.type = Piece::QUEEN;
    }
  }
}
std::vector<Move> ValidMoveFinder::moves_for_normal_white(
    const ValidMoveFinder::ParentState& state) {
  const Board& b = state.original_board;
  const std::vector<Field>& fields = b.get_fields();
  const Field& f = fields[state.index];
  std::vector<Move> moves;

  if (state.move.steps.size() > 1) {
    moves.emplace_back(state.move);
  }
  std::vector<Move> jump_moves;
  Piece::Color enemy_color = Piece::RED;

  if (f.upper_left != -1) {
    const Field& ul = fields[f.upper_left];
    if (not ul.empty && ul.piece.color == enemy_color && ul.upper_left != -1 &&
        fields[ul.upper_left].empty) {
      ParentState new_state = state;
      new_state.index = ul.upper_left;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(ul.upper_left);
      new_state.move.removed_pieces.emplace_back(f.upper_left);
      std::vector<Move> m = find_moves(new_state);
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }
  if (f.upper_right != -1) {
    const Field& ur = fields[f.upper_right];
    if (not ur.empty && ur.piece.color == enemy_color && ur.upper_right != -1 &&
        fields[ur.upper_right].empty) {
      ParentState new_state = state;
      new_state.index = ur.upper_right;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(ur.upper_right);
      new_state.move.removed_pieces.emplace_back(f.upper_right);
      std::vector<Move> m = find_moves(new_state);
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }

  if (not jump_moves.empty()) {
    moves.insert(moves.end(), jump_moves.begin(), jump_moves.end());
    return moves;
  }

  // simple moves
  for (int id : {f.upper_left, f.upper_right}) {
    if (id == -1) continue;
    const Field& neighbour = fields[id];
    if (not neighbour.empty) {
      continue;
    }
    Move move = state.move;
    move.steps.emplace_back(id);
    moves.emplace_back(move);
  }
  return moves;
}
std::vector<Move> ValidMoveFinder::moves_for_normal_red(const ValidMoveFinder::ParentState& state) {
  const Board& b = state.original_board;
  const std::vector<Field>& fields = b.get_fields();
  const Field& f = fields[state.index];
  std::vector<Move> moves;

  if (state.move.steps.size() > 1) {
    moves.emplace_back(state.move);
  }
  std::vector<Move> jump_moves;
  Piece::Color enemy_color = Piece::WHITE;

  if (f.lower_left != -1) {
    const Field& ul = fields[f.lower_left];
    if (not ul.empty && ul.piece.color == enemy_color && ul.lower_left != -1 &&
        fields[ul.lower_left].empty) {
      ParentState new_state = state;
      new_state.index = ul.lower_left;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(ul.lower_left);
      new_state.move.removed_pieces.emplace_back(f.lower_left);
      std::vector<Move> m = find_moves(new_state);
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }
  if (f.lower_right != -1) {
    const Field& ur = fields[f.lower_right];
    if (not ur.empty && ur.piece.color == enemy_color && ur.lower_right != -1 &&
        fields[ur.lower_right].empty) {
      ParentState new_state = state;
      new_state.index = ur.lower_right;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(ur.lower_right);
      new_state.move.removed_pieces.emplace_back(f.lower_right);
      std::vector<Move> m = find_moves(new_state);
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }

  if (not jump_moves.empty()) {
    moves.insert(moves.end(), jump_moves.begin(), jump_moves.end());
    return moves;
  }

  // simple moves
  for (int id : {f.lower_left, f.lower_right}) {
    if (id == -1) continue;
    const Field& neighbour = fields[id];
    if (not neighbour.empty) {
      continue;
    }
    Move move = state.move;
    move.steps.emplace_back(id);
    moves.emplace_back(move);
  }
  return moves;
}
std::vector<Move> ValidMoveFinder::moves_for_queen(const ValidMoveFinder::ParentState& state) {
  const Board& b = state.original_board;
  const std::vector<Field>& fields = b.get_fields();
  const Field& f = fields[state.index];
  std::vector<Move> moves;

  if (state.move.steps.size() > 1) {
    moves.emplace_back(state.move);
  }
  std::vector<Move> jump_moves;

  if (jump_moves.empty()) {
    moves.insert(moves.end(), jump_moves.begin(), jump_moves.end());
    return moves;
  }

  // simple moves
  for (int id : {f.upper_left, f.upper_right, f.lower_left, f.lower_right}) {
    if (id == -1) continue;
    const Field& neighbour = fields[id];
    if (not neighbour.empty) {
      continue;
    }
    ParentState new_state = state;
    new_state.index = id;
    new_state.move.steps.emplace_back(id);
  }

  return moves;
}
std::vector<Move> ValidMoveFinder::leave_empty_moves(std::vector<Move> moves) {
  // erase entries where there is one step or less
}

}  // namespace checkers