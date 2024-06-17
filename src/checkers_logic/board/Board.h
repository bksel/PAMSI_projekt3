//
// Created by ksel on 16/06/24.
//

#ifndef PROJEKT3_WARCABY_NOWY_SRC_CHECKERS_LOGIC_BOARD_BOARD_H_
#define PROJEKT3_WARCABY_NOWY_SRC_CHECKERS_LOGIC_BOARD_BOARD_H_

#include <vector>

#include "../field/Field.h"
#include "../move/Move.h"

namespace checkers {

class Board {
  std::vector<Field> fields;

  void init_fields();
  void set_connections();
  void promote_if_possible();

 public:
  Board();
  // copy constructor
  Board(const Board& b);

  void execute_move(const Move& m);
  struct Statistics {
    int white_pieces;
    int black_pieces;
    int white_kings;
    int black_kings;
  };
  [[nodiscard]] Statistics get_statistics() const;

  [[nodiscard]] const std::vector<Field>& get_fields() const { return fields; }
};

}  // namespace checkers

#endif  // PROJEKT3_WARCABY_NOWY_SRC_CHECKERS_LOGIC_BOARD_BOARD_H_
