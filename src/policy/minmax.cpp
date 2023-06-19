#include <cstdlib>
#include <bits/stdc++.h>
#include <fstream>
#include <stack>

#include "../state/state.hpp"
#include "./minmax.hpp"
#include "./random.hpp"

std::ofstream mydebug("debugger.txt", std::ios::app);

/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */

std::pair<Move, int> MinMax::get_move(State *state, int depth, Move prev, int maxdepth)
{
  if (depth == maxdepth)
    return {prev, state->boardVal};

  auto actions = state->legal_actions;
  if (actions.empty())
    return {prev, state->boardVal};

  for (auto A : actions)
  {
    State *newstate = state->next_state(A);
    if (newstate->game_state != WIN)
      state->NextStates.push_back(newstate);
  }
  if (state->NextStates.empty())
    return {get_move(state, 0), state->boardVal};

  auto it = state->NextStates.begin();
  std::pair<Move, int> BestMove = get_move(*it, depth + 1, (*it)->prev, maxdepth);
  it++;
  while (it != state->NextStates.end())
  {
    auto temp = get_move(*it, depth + 1, (*it)->prev, maxdepth);
    if (depth % 2 == 0)
    {
      if (temp.second > BestMove.second)
        BestMove = temp;
    }
    else
    {
      if (temp.second < BestMove.second)
        BestMove = temp;
    }
    it++;
  }
  mydebug << "depth = " << depth << std::endl
          << "from (" << BestMove.first.first.first << "," << BestMove.first.first.second << ")"
          << "to ("
          << BestMove.first.second.first << "," << BestMove.first.second.second << ")" << std::endl;
  if (depth == 0)
    return BestMove;
  else
    return {prev, BestMove.second};
}

/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
Move MinMax::get_move(State *state, int depth)
{
  if (!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;
  return actions[(rand() + depth) % actions.size()];
}