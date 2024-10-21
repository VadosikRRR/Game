#pragma once

#include "Hero/Hero.hpp"
#include "map/map.h"
#include <iostream>

namespace game {
const int kCountLevels = 10;

class Game {
private:
  std::vector<Map> levels_;
  int current_level_;
  Hero player_;

  void HandleInput(int input);
  void CheckLevelTransition();

public:
  Game();
  void run();
};
} // namespace game