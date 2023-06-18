#pragma once
#include "../state/state.hpp"

/**
 * @brief Policy class for random policy,
 * your policy class should have get_move method
 */
class MinMax
{
public:
  static std::pair<Move, int> get_move(State *state, int depth, Move prev);
};

/*
class MinMax2
{
public:
  static Move get_move(State *root);
};
*/