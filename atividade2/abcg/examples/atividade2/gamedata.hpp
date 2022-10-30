#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>

enum class Input { Right, Left};
enum class State { Playing, Win };

struct GameData {
  State m_state{State::Playing};
  std::bitset<2> m_input;  // [left, right]
};

#endif