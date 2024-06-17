//
// Created by ksel on 17/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_BOARD_VISUALISER_VISUALISER_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_BOARD_VISUALISER_VISUALISER_H_

#include "../Board.h"

namespace checkers {

struct Visualiser {
  static void print(const Board& board);

 private:
  static constexpr std::string margin = "    ";
  static constexpr char blank_field = '_';
  static constexpr char white_field = '.';

  static void print_header();
  static void print_rows(const Board& board);
  static char field_to_symbol(checkers::Field role);



};




}  // namespace checkers
#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_BOARD_VISUALISER_VISUALISER_H_
