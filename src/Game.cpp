#include "Game.h"

namespace game
{
    void Game::HandleInput(int input)
    {
        switch (input)
        {
        case 'w':
            player_.move(-1, 0, levels_[current_level_]);
            break;
        case 'a':
            player_.move(0, -1, levels_[current_level_]);
            break;
        case 'd':
            player_.move(0, 1, levels_[current_level_]);
            break;
        case 's':
            player_.move(1, 0, levels_[current_level_]);
            break;
        case 'q':
            exit(0);
            break;
        case '>':
            CheckLevelTransition();
            break;

        case '<':
            CheckLevelTransition();
            break;
        }
    }
    Game::Game() : current_level_(0), player_("IAM", fighter::warrior)
    {
        levels_.push_back(Map());
        auto stair_up = levels_[current_level_].GetStairUp();
        player_.SetPositions(Point(stair_up.second, stair_up.first));
    }
    void Game::run()
    {
        initscr();
        noecho();
        curs_set(0);
        while (true)
        {
            clear();
            levels_[current_level_].Draw(player_.get_position().get_x(), player_.get_position().get_y());
            refresh();
            int input = getchar();
            HandleInput(input);
        }
        endwin();
    }
    void Game::CheckLevelTransition()
    {
        int player_x = player_.get_position().get_x();
        int player_y = player_.get_position().get_y();
        if (levels_[current_level_].IsStairsDown(player_x, player_y))
        {
            if (current_level_ >= kCountLevels)
                {return;}
            if(current_level_ >= levels_.size() - 1){
                levels_.push_back(Map());
            }
            current_level_++;

            auto stair_up = levels_[current_level_].GetStairUp();
            player_.SetPositions(Point(stair_up.second, stair_up.first));
        }
        else if (levels_[current_level_].IsStairsUp(player_x, player_y))
        {
            if (current_level_ <= 0)
                {return;}
            current_level_--;
            auto stair_up = levels_[current_level_].GetStairDown();
            player_.SetPositions(Point(stair_up.second, stair_up.first));
        }
    }

}
