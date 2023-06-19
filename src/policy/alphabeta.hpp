#pragma once
#include "../state/state.hpp"

/**
 * @brief Policy class for random policy,
 * your policy class should have get_move method
 */
class AlphaBeta
{
public:
  static std::pair<Move, std::pair<int, int>> get_move(State *state, int depth, Move prev, int prev_beta, int maxdepth);
  // return content: { Move, {boardVal, alpha} }
  static Move get_move(State *state, int depth);
};
