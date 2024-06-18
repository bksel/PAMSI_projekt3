//
// Created by ksel on 16/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_MOVE_MOVE_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_MOVE_MOVE_H_

#include <vector>
#include <string>

namespace checkers {

struct Move {
  std::vector<int> steps;
  std::vector<int> removed_pieces;
  [[nodiscard]] std::string to_string() const;

  bool is_id_in_removed_pieces(int id) const;


};

}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_MOVE_MOVE_H_
