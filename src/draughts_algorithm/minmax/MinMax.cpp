//
// Created by ksel on 19/06/24.
//

#include "MinMax.h"

#include <future>
#include <thread>

namespace draught_ai {


[[maybe_unused]] checkers::Move MinMax::get_best_move(const checkers::Board& board, int depth,
                                                      checkers::Piece::Color color) {
  std::vector<checkers::Move> moves;
  if (color == checkers::Piece::Color::RED) {
    moves = checkers::ValidMoveFinder::valid_moves_for_red(board);
  } else {
    moves = checkers::ValidMoveFinder::valid_moves_for_white(board);
  }

  std::vector<Node> nodes;
  for (const auto& move : moves) {
    checkers::Board new_board = board;
    new_board.execute_move(move);
    nodes.push_back(Node{move, new_board, 0});
  }

  for (Node& node : nodes) {
    node.value = minmax(node, depth, color);
  }

  Node best;
  if (color == checkers::Piece::Color::RED) {
    best = *std::max_element(nodes.begin(), nodes.end(),
                             [](const Node& a, const Node& b) { return a.value < b.value; });
  } else {
    best = *std::min_element(nodes.begin(), nodes.end(),
                             [](const Node& a, const Node& b) { return a.value < b.value; });
  }

  checkers::Move best_move = best.initial_move;

  return best_move;
}
float MinMax::alpha_beta(Node& node, int depth, float alpha, float beta,
                         checkers::Piece::Color color) {
  if (depth == 0) {
    return checkers::heuristic_function(node.board);
  }

  std::vector<checkers::Move> moves;
  try {
    if (color == checkers::Piece::WHITE) {
      float value = -1000;

      moves = checkers::ValidMoveFinder::valid_moves_for_white(node.board);
      std::vector<Node> nodes;
      for (const auto& move : moves) {
        checkers::Board new_board = node.board;
        new_board.execute_move(move);
        nodes.push_back(Node{move, new_board, 0});
      }

      for (Node& n : nodes) {
        n.value = alpha_beta(n, depth - 1, alpha, beta, checkers::Piece::RED);
        value = std::max(value, n.value);
        alpha = std::max(alpha, value);
        if (value >= beta) {
          break;
        }
      }

      return value;

    } else {
      float value = 1000;
      moves = checkers::ValidMoveFinder::valid_moves_for_red(node.board);

      std::vector<Node> nodes;
      for (const auto& move : moves) {
        checkers::Board new_board = node.board;
        new_board.execute_move(move);
        nodes.push_back(Node{move, new_board, 0});
      }

      for (Node& n : nodes) {
        n.value = alpha_beta(n, depth - 1, alpha, beta, checkers::Piece::WHITE);
        value = std::min(value, n.value);
        beta = std::min(beta, value);
        if (value <= alpha) {
          break;
        }
      }

      return value;
    }

  } catch (checkers::ValidMoveFinder::NoMovesFound& e) {
    // node is terminal
    return checkers::heuristic_function(node.board);
  }

  return 0;
}
float MinMax::minmax(Node& node, int depth, checkers::Piece::Color color) {
  if (depth == 0) {
    return checkers::heuristic_function(node.board);
  }

  std::vector<checkers::Move> moves;
  try {
    if (color == checkers::Piece::WHITE) {
      float value = -1000;

      moves = checkers::ValidMoveFinder::valid_moves_for_white(node.board);
      std::vector<Node> nodes;
      for (const auto& move : moves) {
        checkers::Board new_board = node.board;
        new_board.execute_move(move);
        nodes.push_back(Node{move, new_board, 0});
      }

      for (Node& n : nodes) {
        n.value = minmax(n, depth - 1, checkers::Piece::RED);
        value = std::max(value, n.value);
      }

      return value;

    } else {
      float value = 1000;
      moves = checkers::ValidMoveFinder::valid_moves_for_red(node.board);

      std::vector<Node> nodes;
      for (const auto& move : moves) {
        checkers::Board new_board = node.board;
        new_board.execute_move(move);
        nodes.push_back(Node{move, new_board, 0});
      }

      for (Node& n : nodes) {
        n.value = minmax(n, depth - 1, checkers::Piece::WHITE);
        value = std::min(value, n.value);
      }

      return value;
    }
  } catch (checkers::ValidMoveFinder::NoMovesFound& e) {
    // node is terminal
    return checkers::heuristic_function(node.board);
  }
}
float MinMax::calculate_minmax(Node& node, int depth, checkers::Piece::Color color) {

}
checkers::Move MinMax::get_best_move_alphabeta(const checkers::Board& board, int depth,
                                               checkers::Piece::Color color) {
  std::vector<checkers::Move> moves;
  if (color == checkers::Piece::Color::RED) {
    moves = checkers::ValidMoveFinder::valid_moves_for_red(board);
  } else {
    moves = checkers::ValidMoveFinder::valid_moves_for_white(board);
  }

  std::vector<Node> nodes;
  for (const auto& move : moves) {
    checkers::Board new_board = board;
    new_board.execute_move(move);
    nodes.push_back(Node{move, new_board, 0});
  }

  for (Node& node : nodes) {
    node.value = alpha_beta(node, depth, -1000, 1000, color);
  }

  Node best;
  if (color == checkers::Piece::Color::RED) {
    best = *std::max_element(nodes.begin(), nodes.end(),
                             [](const Node& a, const Node& b) { return a.value < b.value; });
  } else {
    best = *std::min_element(nodes.begin(), nodes.end(),
                             [](const Node& a, const Node& b) { return a.value < b.value; });
  }

  checkers::Move best_move = best.initial_move;

  return best_move;
}
}  // namespace draught_ai