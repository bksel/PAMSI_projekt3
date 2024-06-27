//
// Created by ksel on 19/06/24.
//
#include "heuristic_function.h"


float checkers::heuristic_function(const Board& board) {
  Board::Statistics stats = board.get_statistics();

  float result = 0;

  HeuristicAnalyser::Weights weights;

  int pawns = stats.white_pieces - stats.black_pieces;
  int queens = stats.white_kings - stats.black_kings;

  result += weights.pawns_number * pawns;
  result += weights.queens_number * queens;

  int distance_to_opponents_edge = HeuristicAnalyser::piece_opponent_edge(board);
  result += weights.piece_opponent_edge * distance_to_opponents_edge;

  int distance_to_board_center = HeuristicAnalyser::piece_board_center(board);
  result += weights.piece_board_center * distance_to_board_center;

  int attack = HeuristicAnalyser::under_attack(board);
  result += weights.piece_under_attack * attack;

  int mobility = HeuristicAnalyser::mobility(board);
  result += weights.mobility * mobility;

  result += weights.chain_attack * HeuristicAnalyser::chain_attack(board);

  return result;
}
