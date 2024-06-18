//
// Created by ksel on 17/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_VALID_MOVE_FINDER_VALIDMOVEFINDER_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_VALID_MOVE_FINDER_VALIDMOVEFINDER_H_

#include <vector>

#include "../board/Board.h"

namespace checkers {

class ValidMoveFinder {
  struct ParentState {
    int index;
    bool was_beating;
    Piece::Color color;
    Piece::Type type;
    const Board& original_board;
    Move move;
  };

  static std::vector<Move> find_moves(const ValidMoveFinder::ParentState& state);
  static void promote_if_possible(ParentState& state);
  static std::vector<Move> leave_only_longest_move_sequences(std::vector<Move> moves);
  static std::vector<Move> leave_empty_moves(std::vector<Move> moves);

  static std::vector<Move> moves_for_normal_white(const ParentState& state);
  static std::vector<Move> moves_for_normal_red(const ParentState& state);

  static std::vector<Move> moves_for_queen(const ValidMoveFinder::ParentState& state);

 public:
  struct Pieces {
    std::vector<int> white_pieces;
    std::vector<int> red_pieces;
    std::vector<int> white_queens;
    std::vector<int> red_queens;
  };

  static Pieces find_pieces(const Board& board);

  static std::vector<Move> valid_moves_for_white(const Board& board);
  static std::vector<Move> valid_moves_for_red(const Board& board);
};

}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_VALID_MOVE_FINDER_VALIDMOVEFINDER_H_
