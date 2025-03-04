#include "gamestatistics.h"

GameStatistics::GameStatistics()
    : current_level_(0)
    , total_enemies_killed_(0)
    , total_steps_taken_(0)
{}

void GameStatistics::SetPlayerName(const QString &name)
{
    player_name_ = name;
}

QString GameStatistics::GetPlayerName() const
{
    return player_name_;
}

void GameStatistics::SetCurrentLevel(int level)
{
    current_level_ = level;
}

int GameStatistics::GetCurrentLevel() const
{
    return current_level_;
}

void GameStatistics::IncrementEnemiesKilled()
{
    total_enemies_killed_++;
}

int GameStatistics::GetTotalEnemiesKilled() const
{
    return total_enemies_killed_;
}

void GameStatistics::IncrementStepsTaken()
{
    total_steps_taken_++;
}

int GameStatistics::GetTotalStepsTaken() const
{
    return total_steps_taken_;
}

void GameStatistics::SetEnemiesKilled(int count)
{
    total_enemies_killed_ = count;
}

void GameStatistics::SetStepsTaken(int count)
{
    total_steps_taken_ = count;
}

void GameStatistics::Reset()
{
    player_name_.clear();
    current_level_ = 0;
    total_enemies_killed_ = 0;
    total_steps_taken_ = 0;
}