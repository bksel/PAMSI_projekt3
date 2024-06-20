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
  static int calculate_attacks(const Board& board, int id);


 public:
  struct Weights {
    float pawns_number = 1.;
    float queens_number = 1.5;

    float piece_opponent_edge = 0.05;
    float piece_board_center = 0.03;

    float piece_under_attack = -0.1;
    float mobility = 0.01 ;
    float chain_attack = 1.2;


  } weights;


  static int piece_opponent_edge(const Board& board);
  static int piece_board_center(const Board& board);
  static int under_attack(const Board& board);
  static int mobility(const Board& board);
  static int chain_attack(const Board& board);
};

}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_HEURISTICS_HEURISTICANALYSER_H_
