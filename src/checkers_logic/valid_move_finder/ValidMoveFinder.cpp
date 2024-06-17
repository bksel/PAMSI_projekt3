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
std::vector<Move> ValidMoveFinder::valid_moves_for_white(const Board& board) {
  Pieces pieces = find_pieces(board);
  std::vector<Move> moves;

  for (int id : pieces.white_pieces) {
    std::vector<Move> moves_for_piece = valid_moves_for_normal_white(board, id);
    moves.insert(moves.end(), moves_for_piece.begin(), moves_for_piece.end());
  }

  return moves;
}
std::vector<Move> ValidMoveFinder::valid_moves_for_normal_white(const Board& board, int field_id) {
  std::vector<Move> moves;
  const Field& field = board.get_fields()[field_id];

  // case of single move
  if (field.upper_left != -1 && board.get_fields()[field.upper_left].empty) {
    Move m;
    m.steps.push_back(field.id);
    m.steps.push_back(field.upper_left);
    moves.push_back(m);
  }
  if (field.upper_right != -1 && board.get_fields()[field.upper_right].empty) {
    Move m;
    m.steps.push_back(field.id);
    m.steps.push_back(field.upper_right);
    moves.push_back(m);
  }

  return moves;
}
std::vector<Move> ValidMoveFinder::valid_moves_for_red(const Board& board) {
  Pieces pieces = find_pieces(board);
  std::vector<Move> moves;

  for (int id : pieces.red_pieces) {
    std::vector<Move> moves_for_piece = valid_moves_for_normal_red(board, id);
    moves.insert(moves.end(), moves_for_piece.begin(), moves_for_piece.end());
  }

  return moves;
}
std::vector<Move> ValidMoveFinder::valid_moves_for_normal_red(const Board& board, int field_id) {
  std::vector<Move> moves;
  const Field& field = board.get_fields()[field_id];

  // case of single move
  if (field.lower_left != -1 && board.get_fields()[field.lower_left].empty) {
    Move m;
    m.steps.push_back(field.id);
    m.steps.push_back(field.lower_left);
    moves.push_back(m);
  }

  if (field.lower_right != -1 && board.get_fields()[field.lower_right].empty) {
    Move m;
    m.steps.push_back(field.id);
    m.steps.push_back(field.lower_right);
    moves.push_back(m);
  }

  return moves;
}
}  // namespace checkers