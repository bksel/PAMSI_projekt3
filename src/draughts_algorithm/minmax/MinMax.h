//
// Created by ksel on 19/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_DRAUGHTS_ALGORITHM_MINMAX_MINMAX_H_
#define MINIPROJEKT3_WARCABY_SRC_DRAUGHTS_ALGORITHM_MINMAX_MINMAX_H_

#include <atomic>

#include "../../checkers_logic/lib.h"

namespace draught_ai {

struct Node {
  checkers::Move initial_move;
  checkers::Board board;

  float value;
};

class MinMax {

  std::atomic<int> thread_count = 0;
  int max_thread_count = 20;
  const int initial_depth = 2;

  static float calculate_minmax (Node& node, int depth, checkers::Piece::Color color);

  float alpha_beta(Node& node, int depth, float alpha, float beta, checkers::Piece::Color color);
  float minmax(Node& node, int depth, checkers::Piece::Color color);

 public:
  checkers::Move get_best_move(const checkers::Board& board, int depth, checkers::Piece::Color color);
};




}  // namespace draught_ai

#endif  // MINIPROJEKT3_WARCABY_SRC_DRAUGHTS_ALGORITHM_MINMAX_MINMAX_H_
