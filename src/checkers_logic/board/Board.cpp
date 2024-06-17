//
// Created by ksel on 16/06/24.
//

#include "Board.h"

#include <fmt/format.h>

namespace checkers {
Board::Board() {
  fields.emplace_back(-1);
  for (int i = 1; i <= 32; ++i) {
    fields.emplace_back(i);
  }
  init_fields();
  set_connections();
}
void Board::init_fields() {
  for (int i = 1; i <= 12; ++i) {
    fields[i].empty = false;
    fields[i].piece = {Piece::RED, Piece::NORMAL};
  }

  for (int i = 21; i <= 32; ++i) {
    fields[i].empty = false;
    fields[i].piece = {Piece::WHITE, Piece::NORMAL};
  }
}
void Board::set_connections() {
  for (int id : {1, 2, 3, 4}) {
    fields[id].lower_left = id + 4;
    if (id == 4) continue;
    fields[id].lower_right = id + 5;
  }

  for (int id : {5, 6, 7, 8, 13, 14, 15, 16, 21, 22, 23, 24}) {
    fields[id].upper_right = id - 4;
    fields[id].lower_right = id + 4;
    if (id == 5 or id == 13 or id == 21) continue;
    fields[id].upper_left = id - 5;
    fields[id].lower_left = id + 3;
  }

  for (int id : {9, 10, 11, 12, 17, 18, 19, 20, 25, 26, 27, 28}) {
    fields[id].upper_left = id - 4;
    fields[id].lower_left = id + 4;
    if (id == 12 or id == 20 or id == 28) continue;
    fields[id].upper_right = id - 3;
    fields[id].lower_right = id + 5;
  }

  for (int id : {29, 30, 31, 32}) {
    fields[id].upper_right = id - 4;
    if (id == 29) continue;
    fields[id].upper_left = id - 5;
  }
}
Board::Board(const Board& b) { fields = b.fields; }
void Board::execute_move(const Move& m) {
  int from = *m.steps.begin();
  int to = *m.steps.rbegin();

  for (auto it = m.steps.begin() + 1; it != m.steps.end(); ++it) {
    if (not fields[*it].empty) {
      std::string message = fmt::format(
          "Move to non-empty field! Move: {}, First invalid field: {}", m.to_string(), *it);
      throw std::runtime_error(message);
    }
  }

  fields[to].empty = false;
  fields[to].piece = fields[from].piece;
  fields[from].empty = true;
  fields[from].piece = {Piece::NONE, Piece::EMPTY};

  for (int to_be_removed : m.removed_pieces) {
    fields[to_be_removed].empty = true;
    fields[to_be_removed].piece = {Piece::NONE, Piece::EMPTY};
  }
}
Board::Statistics Board::get_statistics() const {
  int white_pieces = 0;
  int black_pieces = 0;
  int white_kings = 0;
  int black_kings = 0;

  for (const Field& field : fields) {
    if (field.empty) continue;
    if (field.piece.color == Piece::RED) {
      black_pieces++;
      if (field.piece.type == Piece::QUEEN) black_kings++;
    } else {
      white_pieces++;
      if (field.piece.type == Piece::QUEEN) white_kings++;
    }
  }

  return {white_pieces, black_pieces, white_kings, black_kings};
}
}  // namespace checkers