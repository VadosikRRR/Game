#ifndef ENEMY_H
#define ENEMY_H
#include <QString>
#include <QPoint>
#include "constants.h"

class Enemy {
private:
    char symbol_;
    int level_;
    int attack_power_;
    int health_;
    int max_health_;
    int energy_;
    int max_energy_;
    int attack_probability_;
    QString name_;
    QPoint position_;

    char eaten_tile_ = '.';
public:
    explicit Enemy(int level_enemy, int x_coordinate, int y_coordinate);

    char GetSymbol() const;
    int GetLevel() const;
    int GetX() const;
    int GetY() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetEnergy() const;
    int GetMaxEnergy() const;
    int GetAttackPower() const;
    int GetAttackProbability() const;
    QString GetName() const;

    void SetPosition(int x, int y);
    void SetEnergy(int new_enegry);
    void SetHealth(int new_health);
    void RestEnemy();
    void ReduceEnergyForStep();
    void ReduceEnergyForHit();
    void ReduceHealth(int delta_health);

    int StepsNumberToPlayer(int player_x, int player_y);
    QPoint NextStep(int player_x, int player_y);

    char GetEatenTile();
    void SetEatenTile(char tile);
};

#endif // ENEMY_H
