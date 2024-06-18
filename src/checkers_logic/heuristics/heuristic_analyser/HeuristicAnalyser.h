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

  static int calculate_row(int id);
  static int calculate_column(int id);

 public:
  struct Weights {
    int pawns_number = 1;
    int queens_number = 2;

    float piece_opponent_edge = 2./8;
    float piece_board_center = 2./20;

    int piece_under_attack = 1;
    int mobility = 1;


  } weights;


  static int piece_opponent_edge(const Board& board);
  static int piece_board_center(const Board& board);
};

}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_HEURISTICS_HEURISTICANALYSER_H_
