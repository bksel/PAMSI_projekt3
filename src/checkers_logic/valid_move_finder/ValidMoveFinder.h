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
    bool was_beating;
    int index;
    Piece::Color color;
    Piece::Type type;
    Board board;
    Move move;
  };


  static std::vector<Move> valid_moves_for_normal_white(const Board& board, int field_id);
  static std::vector<Move> valid_moves_for_queen_white(const Board& board, int field_id);

  static std::vector<Move> valid_moves_for_normal_red(const Board& board, int field_id);
  static std::vector<Move> valid_moves_for_queen_red(const Board& board, int field_id);

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
