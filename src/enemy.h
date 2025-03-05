#ifndef ENEMY_H
#define ENEMY_H
#include <QString>
#include <QPoint>


#define ATTACK_POWER_1 5
#define ATTACK_POWER_2 10
#define ATTACK_POWER_3 15

#define MAX_HEALTH_1 30
#define MAX_HEALTH_2 45
#define MAX_HEALTH_3 60

#define MAX_ENERGY_1 50
#define MAX_ENERGY_2 100
#define MAX_ENERGY_3 150

#define ATTACK_PROBABILITY_1 25
#define ATTACK_PROBABILITY_2 50
#define ATTACK_PROBABILITY_3 50

#define NAME_1 "Barbarian"
#define NAME_2 "Pekka"
#define NAME_3 "GODZILLA"

#define SYMBOL_1 'E'
#define SYMBOL_2 'N'
#define SYMBOL_3 'H'

#define ENERGY_FOR_STEP 10
#define ENERGY_REST 10
#define ENERGY_FOR_HIT 15

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
