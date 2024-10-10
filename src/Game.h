#pragma once

#include <iostream>
#include "map/map.h"
#include "Hero/Hero.hpp"

namespace game
{
    const int kCountLevels = 10;

    class Game
    {
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
}