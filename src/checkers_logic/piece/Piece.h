//
// Created by ksel on 16/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_PIECE_PIECE_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_PIECE_PIECE_H_

namespace checkers {

struct Piece {
  enum Color { WHITE, RED, NONE };
  enum Type { NORMAL, QUEEN, EMPTY };

  Color color;
  Type type;

  Piece(Color c, Type t) : color(c), type(t){};
};

}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_PIECE_PIECE_H_
