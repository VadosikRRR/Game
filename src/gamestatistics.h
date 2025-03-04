#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

#include <QString>

class GameStatistics
{
public:
    GameStatistics();

    void SetPlayerName(const QString &name);
    QString GetPlayerName() const;

    void SetCurrentLevel(int level);
    int GetCurrentLevel() const;

    void IncrementEnemiesKilled();
    void SetEnemiesKilled(int count);
    int GetTotalEnemiesKilled() const;

    void IncrementStepsTaken();
    void SetStepsTaken(int count);
    int GetTotalStepsTaken() const;

    void Reset();

private:
    QString player_name_;
    int current_level_;
    int total_enemies_killed_;
    int total_steps_taken_;
};

#endif // GAMESTATISTICS_H