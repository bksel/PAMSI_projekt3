//
// Created by ksel on 16/06/24.
//

#ifndef MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_LIB_H_
#define MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_LIB_H_

#include "board/Board.h"
#include "board/visualiser/Visualiser.h"
#include "field/Field.h"
#include "valid_move_finder/ValidMoveFinder.h"

namespace checkers {
void print(const Board& b) { Visualiser::print(b); }

template <typename T>
concept Iterable = requires(T t) {
  { t.begin() } -> std::same_as<typename T::iterator>;
  { t.end() } -> std::same_as<typename T::iterator>;
};

template <typename T>
concept MoveContainer = Iterable<T> && std::same_as<typename T::value_type, Move>;

template <MoveContainer Container>
void print(const Container& moves) {
  for (const Move& m : moves) {
    fmt::println("{}", m.to_string());
  }
}

void print(const Move& m) { fmt::println("{}", m.to_string()); }
}  // namespace checkers

#endif  // MINIPROJEKT3_WARCABY_SRC_CHECKERS_LOGIC_LIB_H_
