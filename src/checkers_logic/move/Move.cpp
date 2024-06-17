//
// Created by ksel on 16/06/24.
//

#include "Move.h"

namespace checkers {
std::string Move::to_string() const {
  std::string result;
  for (int i = 0; i < steps.size(); i++) {
    result += std::to_string(steps[i]);
    if (i != steps.size() - 1) {
      result += " -> ";
    }
  }
  result += " | x: ";
  for (int i = 0; i < removed_pieces.size(); i++) {
    result += std::to_string(removed_pieces[i]);
    if (i != removed_pieces.size() - 1) {
      result += ", ";
    }
  }
  return result;
}
}  // namespace checkers