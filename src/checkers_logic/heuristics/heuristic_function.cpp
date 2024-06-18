//
// Created by ksel on 19/06/24.
//
#include "heuristic_function.h"

float checkers::heuristic_function(const Board& board) {
  Board::Statistics stats = board.get_statistics();

  int result = 0;

  HeuristicAnalyser::Weights weights;

  int pawns = stats.white_pieces - stats.black_pieces;
  int queens = stats.white_kings - stats.black_kings;

  result += weights.pawns_number * pawns;
  result += weights.queens_number * queens;

  return result;
}
