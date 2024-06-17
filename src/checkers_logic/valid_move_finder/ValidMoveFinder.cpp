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


  std::vector<Move> moves;
  if (state.color == Piece::WHITE) {
    if (state.type == Piece::NORMAL) {
      int a;
    } else if (state.type == Piece::QUEEN) {
      int a;
    }
  } else if (state.color == Piece::RED) {
    if (state.type == Piece::NORMAL) {
      int a;
    } else if (state.type == Piece::QUEEN) {
      int a;
    }
  }

  moves = leave_only_longest_move_sequences(moves);

  return moves;
}
std::vector<Move> ValidMoveFinder::valid_moves_for_white(const Board& board) {
  Pieces pieces = find_pieces(board);
  std::vector<Move> moves;
  for (int id : pieces.white_pieces) {
    ParentState state{id, false, Piece::WHITE, Piece::NORMAL, board, Move{{}, {}}};
    std::vector<Move> piece_moves = find_moves(state);
    moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
  }

  return moves;
}
std::vector<Move> ValidMoveFinder::leave_only_longest_move_sequences(std::vector<Move> moves) {
  // find move with the longest beating chain
  int max_length = 0;
  for (Move& m : moves) {
    if (m.steps.size() > max_length) {
      max_length = static_cast<int>(m.steps.size());
    }
  }

  // remove all moves that are not the longest
  moves.erase(std::remove_if(moves.begin(), moves.end(),
                             [max_length](const Move& m) { return m.steps.size() < max_length; }),
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

}  // namespace checkers