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
  for (int id : pieces.white_queens) {
    ParentState state{id, false, Piece::WHITE, Piece::QUEEN, board, Move{{id}, {}}};
    std::vector<Move> piece_moves = find_moves(state);
    moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
  }

  if (moves.empty()) {
    throw NoMovesFound();
  }

  moves = leave_only_longest_move_sequences(moves);
  moves = remove_duplicates(moves);

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

  if (moves.empty()) {
    throw NoMovesFound();
  }

  moves = leave_only_longest_move_sequences(moves);
  moves = remove_duplicates(moves);

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

  //  fmt::print("Max length: {}\n", max_length);

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

  if (state.was_beating) {
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

  if (state.was_beating) {
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
  Piece::Color enemy_color = state.color == Piece::WHITE ? Piece::RED : Piece::WHITE;

  if (f.upper_right != -1 and state.move.is_id_in_removed_pieces(f.upper_right) == false) {
    //    fmt::print("UR: {}\n", f.upper_right);
    const Field& ur = fields[f.upper_right];
    if (not ur.empty && ur.piece.color == enemy_color && ur.upper_right != -1 &&
        fields[ur.upper_right].empty) {
      ParentState new_state = state;
      new_state.index = ur.upper_right;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(ur.upper_right);
      new_state.move.removed_pieces.emplace_back(f.upper_right);
      std::vector<Move> m = find_moves(new_state);
      if (m.size() == 1 and m[0].steps.size() == state.move.steps.size()) {
      }
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }

  if (f.lower_right != -1 and state.move.is_id_in_removed_pieces(f.lower_right) == false) {
    //    fmt::print("LR: {}\n", f.lower_right);
    const Field& lr = fields[f.lower_right];
    if (not lr.empty && lr.piece.color == enemy_color && lr.lower_right != -1 &&
        fields[lr.lower_right].empty) {
      ParentState new_state = state;
      new_state.index = lr.lower_right;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(lr.lower_right);
      new_state.move.removed_pieces.emplace_back(f.lower_right);
      std::vector<Move> m = find_moves(new_state);
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }

  if (f.lower_left != -1 and state.move.is_id_in_removed_pieces(f.lower_left) == false) {
    //    fmt::print("LR: {}\n", f.lower_left);
    const Field& lr = fields[f.lower_left];
    if (not lr.empty && lr.piece.color == enemy_color && lr.lower_left != -1 &&
        fields[lr.lower_left].empty) {
      ParentState new_state = state;
      new_state.index = lr.lower_left;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(lr.lower_left);
      new_state.move.removed_pieces.emplace_back(f.lower_left);
      std::vector<Move> m = find_moves(new_state);
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }

  if (f.upper_left != -1 and state.move.is_id_in_removed_pieces(f.upper_left) == false) {
    //    fmt::print("UL: {}\n", f.upper_left);
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

  if (f.lower_left != -1 and state.move.is_id_in_removed_pieces(f.lower_left) == false) {
    //    fmt::print("LL: {}\n", f.lower_left);
    const Field& ll = fields[f.lower_left];
    if (not ll.empty && ll.piece.color == enemy_color && ll.lower_left != -1 &&
        fields[ll.lower_left].empty) {
      ParentState new_state = state;
      new_state.index = ll.lower_left;
      new_state.was_beating = true;
      new_state.move.steps.emplace_back(ll.lower_left);
      new_state.move.removed_pieces.emplace_back(f.lower_left);
      std::vector<Move> m = find_moves(new_state);
      jump_moves.insert(jump_moves.end(), m.begin(), m.end());
    }
  }

  moves.insert(moves.end(), jump_moves.begin(), jump_moves.end());
  if (not jump_moves.empty()) {
    return jump_moves;
  }

  // simple moves
  fmt::print("SIMPLE MOVES\n");
  for (int id : {f.upper_left, f.upper_right, f.lower_left, f.lower_right}) {
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
std::vector<Move> ValidMoveFinder::remove_duplicates(std::vector<Move> moves) {
  // assume that only the longest moves are left
  Move first = moves[0];
  // remove all moves that end in the same field
  moves.erase(
      std::remove_if(moves.begin() + 1, moves.end(),
                     [first](const Move& m) { return m.steps.back() == first.steps.back(); }),
      moves.end());
  return moves;
}
bool ValidMoveFinder::is_move_in_moves(Move& move, const std::vector<Move>& moves) {
  for (const Move& m : moves)
    if (m == move) {
      move = m;
      return true;
    }

  return false;
}

std::vector<Move> ValidMoveFinder::valid_moves_for_piece(const Board& board, int index) {
  ParentState state{index,
                    false,
                    board.get_fields()[index].piece.color,
                    board.get_fields()[index].piece.type,
                    board,
                    Move{{index}, {}}};
  std::vector<Move> moves = find_moves(state);
  return moves;

  return {};
}

}  // namespace checkers