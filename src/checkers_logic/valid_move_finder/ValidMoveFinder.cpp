//
// Created by ksel on 17/06/24.
//

#include "ValidMoveFinder.h"

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
}  // namespace checkers