#include <cstdlib>
#include <bits/stdc++.h>
#include <fstream>
#include <stack>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

std::ofstream debug("debugger.txt", std::ios::app);

/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */

std::pair<Move, std::pair<int, int>> AlphaBeta::get_move(State *state, int depth, Move prev, int prev_beta, int maxdepth)
{
  if (depth == maxdepth)
    return {prev, {state->boardVal, state->boardVal}};

  if (depth % 2 == 0 && prev_beta < state->beta)
    state->beta = prev_beta;
  if (depth % 2 == 0 && depth > 0 && state->alpha >= state->beta)
    return {prev, {state->boardVal, state->alpha}};

  auto actions = state->legal_actions;
  debug << "num. of next actions = " << actions.size() << std::endl;
  if (actions.empty())
    return {prev, {state->boardVal, state->alpha}};

  for (auto A : actions)
  {
    State *newstate = state->next_state(A);
    if (newstate->game_state != WIN)
      state->NextStates.push_back(newstate);
  }
  if (state->NextStates.empty() && depth == 0)
    return {get_move(state, 0), {state->boardVal, state->alpha}};
  if (state->NextStates.empty() && depth != 0)
    return {prev, {state->boardVal, state->alpha}};

  auto it = state->NextStates.begin();
  auto BestMove = get_move(*it, depth + 1, (*it)->prev, state->beta, maxdepth);
  if (depth % 2 == 0 && depth > 0 && BestMove.second.first > state->alpha)
    state->alpha = BestMove.second.first;
  else if (depth % 2 == 1 && BestMove.second.first < state->beta)
    state->beta = BestMove.second.first;
  it++;

  while (it != state->NextStates.end())
  {
    if (depth % 2 == 0 && depth > 0 && state->alpha >= state->beta)
      return {prev, {BestMove.second.first, state->alpha}};

    auto temp = get_move(*it, depth + 1, (*it)->prev, state->beta, maxdepth);

    if (depth % 2 == 0)
    {
      if (temp.second.first > state->alpha)
        state->alpha = temp.second.first;
      if (temp.second.first > BestMove.second.first)
        BestMove = temp;
    }
    else
    {
      if (temp.second.first < state->beta)
        state->beta = temp.second.first;
      if (temp.second.first < BestMove.second.first)
        BestMove = temp;
    }
    debug << "alpha = " << state->alpha << "; beta = " << state->beta << std::endl;
    it++;
  }
  debug << "depth = " << depth << std::endl
        << "from (" << BestMove.first.first.first << "," << BestMove.first.first.second << ") "
        << "to ("
        << BestMove.first.second.first << "," << BestMove.first.second.second << ")" << std::endl;
  if (depth == 0)
    return BestMove;
  else
    return {prev, {BestMove.second.first, state->alpha}};
}

/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
Move AlphaBeta::get_move(State *state, int depth)
{
  if (!state->legal_actions.size())
    state->get_legal_actions();

  auto actions = state->legal_actions;
  return actions[(rand() + depth) % actions.size()];
}