#include <cstdlib>
#include <bits/stdc++.h>
#include <fstream>
#include <stack>

#include "../state/state.hpp"
#include "./minmax.hpp"

std::ofstream mydebug("debugger.txt", std::ios::app);

/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */

std::map<std::pair<Move, int>, bool> explored_moves;

std::pair<Move, int> MinMax::get_move(State *state, int depth, Move prev)
{
  mydebug << depth << std::endl;
  // explored_moves[{prev, depth}] = true;
  // std::pair<Move, int> BestMove = {prev, state->boardVal};
  if (depth == 3)
    return {prev, state->boardVal};

  State *root = state;
  if (root->legal_actions.empty())
    root->get_legal_actions();

  auto actions = root->legal_actions;
  mydebug << "num. of next actions = " << actions.size() << std::endl;
  if (actions.empty())
    return {prev, state->boardVal};

  for (auto A : actions)
  {
    // if (!explored_moves[{A, depth}])
    {
      State *newstate = root->next_state(A);
      root->NextStates.push_back(newstate);
      mydebug << "(" << A.first.first << "," << A.first.second << ")";
      mydebug << " -> "
              << "(" << A.second.first << "," << A.second.second << ")" << std::endl;
    }
  }

  auto it = root->NextStates.begin();
  std::pair<Move, int> BestMove = get_move(*it, depth + 1, (*it)->prev);
  it++;
  while (it != root->NextStates.end())
  {
    auto temp = get_move(*it, depth + 1, (*it)->prev);
    if (depth % 2 == 1)
      temp.second = -temp.second;
    if (temp.second <= BestMove.second)
      BestMove = temp;
    it++;
  }
  mydebug << "from (" << BestMove.first.first.first << "," << BestMove.first.first.second << ")"
          << "to ("
          << BestMove.first.second.first << "," << BestMove.first.second.second << ")" << std::endl;
  if (depth == 0)
    return BestMove;
  else
    return {prev, BestMove.second};
}

/*
Move MinMax2::get_move(State *root)
{
  State *initial_state = root;
  std::stack<std::pair<State *, int>> Stack;
  Stack.push({initial_state, 0});

  while (!Stack.empty())
  {
    State *cur_state = Stack.top().first;
    int cur_val = Stack.top().second;
    Stack.pop();

    if (root->legal_actions.empty())
      root->get_legal_actions();

    auto actions = root->legal_actions;
  }
}
*/