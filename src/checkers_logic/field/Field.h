//
// Created by ksel on 16/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_FIELD_FIELD_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_FIELD_FIELD_H_

#include <memory>

#include "../piece/Piece.h"

namespace checkers {

struct Field {
  bool empty;
  Piece piece;
  int id;

  int upper_left = -1;
  int upper_right = -1;
  int lower_left = -1;
  int lower_right = -1;


  explicit Field(int index) : id(index), empty(true), piece({Piece::NONE, Piece::EMPTY}){};
  void set_neighbours(int ul, int ur, int ll, int lr);

};

}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_FIELD_FIELD_H_
