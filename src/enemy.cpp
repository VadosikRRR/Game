#include "enemy.h"
#include <algorithm>


Enemy::Enemy(int level_enemy, int x_coordinate, int y_coordinate) : position_(QPoint(x_coordinate, y_coordinate)) {
    if (level_enemy == 2) {
        attackPower_ = ATTACK_POWER_2;
        health_ = MAX_HEALTH_2;
        maxHealth_ = MAX_HEALTH_2;
        energy_ = MAX_ENERGY_2;
        max_energy_ = MAX_ENERGY_2;
        attackProbability_ = ATTACK_PROBABILITY_2;
        name_ = QString(NAME_2);
        symbol_ = SYMBOL_2;
    }
    else if (level_enemy == 3) {
        attackPower_ = ATTACK_POWER_3;
        health_ = MAX_HEALTH_3;
        maxHealth_ = MAX_HEALTH_3;
        energy_ = MAX_ENERGY_3;
        max_energy_ = MAX_ENERGY_3;
        attackProbability_ = ATTACK_PROBABILITY_3;
        name_ = QString(NAME_3);
        symbol_ = SYMBOL_3;
    }
    else {
        attackPower_ = ATTACK_POWER_1;
        health_ = MAX_HEALTH_1;
        maxHealth_ = MAX_HEALTH_1;
        energy_ = MAX_ENERGY_1;
        max_energy_ = MAX_ENERGY_1;
        attackProbability_ = ATTACK_PROBABILITY_1;
        name_ = QString(NAME_1);
        symbol_ = SYMBOL_1;
    }
}

char Enemy::GetSymbol() const { return symbol_; }

int Enemy::GetX() const { return position_.x(); }

int Enemy::GetY() const { return position_.y(); }

int Enemy::GetHealth() const { return health_; }

int Enemy::GetMaxHealth() const { return maxHealth_; }

int Enemy::GetEnergy() const { return energy_; }

int Enemy::GetMaxEnergy() const { return max_energy_; }

int Enemy::GetAttackPower() const { return attackPower_; }

int Enemy::GetAttackProbability()  const { return attackProbability_; }

void Enemy::SetEnergy(int new_energy) {
    if (new_energy > max_energy_) {
        energy_ = max_energy_;
        return;
    }
    else if (new_energy < 0) {
        energy_ = 0;
        return;
    }

    energy_ = new_energy;
}

void Enemy::SetPosition(int x, int y) {
    position_.setX(x);
    position_.setY(y);
}

int Enemy::StepsNumberToPlayer(int player_x, int player_y) {
    return std::max(std::abs(position_.x() - player_x), std::abs(position_.y() - player_y));
}

QPoint Enemy::NextStep(int player_x, int player_y) {
    int dx = 0;
    int dy = 0;
    if (player_x > position_.x()) {
        dx = 1;
    }
    else if (player_x < position_.x()) {
        dx = -1;
    }

    if (player_y > position_.y()) {
        dy = 1;
    }
    else if (player_y < position_.y()) {
        dy = -1;
    }

    return QPoint(position_.x() + dx, position_.y() + dy);
}

void Enemy::RestEnemy() {
    SetEnergy(energy_ + ENERGY_REST);
}

void Enemy::ReduceEnergyForStep() {
    SetEnergy(energy_ - ENERGY_FOR_STEP);
}
