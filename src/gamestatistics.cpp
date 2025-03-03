#include "gamestatistics.h"

GameStatistics::GameStatistics()
    : currentLevel_(0)
    , totalEnemiesKilled_(0)
    , totalStepsTaken_(0)
{}

void GameStatistics::setPlayerName(const QString &name)
{
    playerName_ = name;
}

QString GameStatistics::getPlayerName() const
{
    return playerName_;
}

void GameStatistics::setCurrentLevel(int level)
{
    currentLevel_ = level;
}

int GameStatistics::getCurrentLevel() const
{
    return currentLevel_;
}

void GameStatistics::incrementEnemiesKilled()
{
    totalEnemiesKilled_++;
}

int GameStatistics::getTotalEnemiesKilled() const
{
    return totalEnemiesKilled_;
}

void GameStatistics::incrementStepsTaken()
{
    totalStepsTaken_++;
}

int GameStatistics::getTotalStepsTaken() const
{
    return totalStepsTaken_;
}
void GameStatistics::setEnemiesKilled(int count)
{
    totalEnemiesKilled_ = count;
}
void GameStatistics::setStepsTaken(int count)
{
    totalStepsTaken_ = count;
}
void GameStatistics::reset()
{
    playerName_.clear();
    currentLevel_ = 0;
    totalEnemiesKilled_ = 0;
    totalStepsTaken_ = 0;
}
