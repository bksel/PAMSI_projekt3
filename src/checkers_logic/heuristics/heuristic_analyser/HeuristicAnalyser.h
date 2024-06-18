//
// Created by ksel on 19/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_HEURISTICS_HEURISTICANALYSER_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_HEURISTICS_HEURISTICANALYSER_H_

#include "../../board/Board.h"
namespace checkers {

/*
 * Positive values indicate that white is winning, negative values indicate that black is winning.
 */
class HeuristicAnalyser {
 public:
  struct Weights {
    int pawns_number = 1;
    int queens_number = 2;

    int piece_opponent_edge = 1;
    int piece_board_center = 1;

    int piece_under_attack = 1;
    int mobility = 1;


  } weights;

  static int pawns_number(const Board& board);
  static int queens_number(const Board& board);
};

}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_HEURISTICS_HEURISTICANALYSER_H_
