#ifndef ENEMY_H
#define ENEMY_H
#include <QString>
#include <QPoint>


#define ATTACK_POWER_1 5
#define ATTACK_POWER_2 15
#define ATTACK_POWER_3 25

#define MAX_HEALTH_1 30
#define MAX_HEALTH_2 60
#define MAX_HEALTH_3 90

#define MAX_ENERGY_1 50
#define MAX_ENERGY_2 100
#define MAX_ENERGY_3 150

#define ATTACK_PROBABILITY_1 25
#define ATTACK_PROBABILITY_2 50
#define ATTACK_PROBABILITY_3 75

#define NAME_1 "Level 1"
#define NAME_2 "Level 2"
#define NAME_3 "Level 3"

#define SYMBOL_1 'E'
#define SYMBOL_2 'N'
#define SYMBOL_3 'H'

#define ENERGY_FOR_STEP 10
#define ENERGY_REST 10
#define ENERGY_FOR_HIT 15

class Enemy {
private:
    char symbol_;
    int attackPower_;
    int health_;
    int maxHealth_;
    int energy_;
    int max_energy_;
    int attackProbability_;
    QString name_;
    QPoint position_;

    void SetEnergy(int new_enegry);
public:
    explicit Enemy(int level_enemy, int x_coordinate, int y_coordinate);

    char GetSymbol() const;
    int GetX() const;
    int GetY() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetEnergy() const;
    int GetMaxEnergy() const;
    int GetAttackPower() const;
    int GetAttackProbability() const;

    void SetPosition(int x, int y);
    void RestEnemy();
    void ReduceEnergyForStep();
    void ReduceEnergyForHit();

    int StepsNumberToPlayer(int player_x, int player_y);
    QPoint NextStep(int player_x, int player_y);
};

#endif // ENEMY_H
