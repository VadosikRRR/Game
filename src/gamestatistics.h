#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

#include <QString>

class GameStatistics
{
public:
    GameStatistics();

    void setPlayerName(const QString &name);
    QString getPlayerName() const;

    void setCurrentLevel(int level);
    int getCurrentLevel() const;

    void incrementEnemiesKilled();
    void setEnemiesKilled(int count);
    int getTotalEnemiesKilled() const;

    void incrementStepsTaken();
    void setStepsTaken(int count);
    int getTotalStepsTaken() const;

    void reset();

private:
    QString playerName_;
    int currentLevel_;
    int totalEnemiesKilled_;
    int totalStepsTaken_;
};

#endif // GAMESTATISTICS_H
