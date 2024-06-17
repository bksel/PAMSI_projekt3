//
// Created by ksel on 16/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_LIB_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_LIB_H_

#include "board/Board.h"
#include "field/Field.h"
#include "board/visualiser/Visualiser.h"
#include "valid_move_finder/ValidMoveFinder.h"

namespace checkers {
  void print(const Board& b) {
    Visualiser::print(b);
  }
}  // namespace checkers



#endif//MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_LIB_H_
