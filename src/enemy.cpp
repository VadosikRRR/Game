#include "enemy.h"
#include <algorithm>


Enemy::Enemy(int level_enemy, int x_coordinate, int y_coordinate) : position_(QPoint(x_coordinate, y_coordinate)) {
    if (level_enemy == 2) {
        attack_power_ = Constant::attack_power_2;
        health_ = Constant::max_health_2;
        max_health_ = Constant::max_health_2;
        energy_ = Constant::max_energy_2;
        max_energy_ = Constant::max_energy_2;
        attack_probability_ = Constant::attack_probability_2;
        name_ = QString(Constant::enemy_name_2);
        symbol_ = Constant::enemy_symbol_2;
        level_ = 2;
    }
    else if (level_enemy == 3) {
        attack_power_ = Constant::attack_power_3;
        health_ = Constant::max_health_3;
        max_health_ = Constant::max_health_3;
        energy_ = Constant::max_energy_3;
        max_energy_ = Constant::max_energy_3;
        attack_probability_ = Constant::attack_probability_3;
        name_ = QString(Constant::enemy_name_3);
        symbol_ = Constant::enemy_symbol_3;
        level_ = 3;
    }
    else {
        attack_power_ = Constant::attack_power_1;
        health_ = Constant::max_health_1;
        max_health_ = Constant::max_health_1;
        energy_ = Constant::max_energy_1;
        max_energy_ = Constant::max_energy_1;
        attack_probability_ = Constant::attack_probability_1;
        name_ = QString(Constant::enemy_name_1);
        symbol_ = Constant::enemy_symbol_1;
        level_ = 1;
    }
}

char Enemy::GetSymbol() const { return symbol_; }

int Enemy::GetLevel() const { return level_; }

int Enemy::GetX() const { return position_.x(); }

int Enemy::GetY() const { return position_.y(); }

int Enemy::GetHealth() const { return health_; }

int Enemy::GetMaxHealth() const { return max_health_; }

int Enemy::GetEnergy() const { return energy_; }

int Enemy::GetMaxEnergy() const { return max_energy_; }

int Enemy::GetAttackPower() const { return attack_power_; }

int Enemy::GetAttackProbability()  const { return attack_probability_; }

QString Enemy::GetName() const { return name_; }

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

void Enemy::SetHealth(int new_health) {
    if (new_health > max_health_) {
        health_ = max_health_;
        return;
    }
    else if (new_health < 0) {
        health_ = 0;
        return;
    }

    health_ = new_health;
}

void Enemy::SetPosition(int x, int y) {
    position_.setX(x);
    position_.setY(y);
}

int Enemy::StepsNumberToPlayer(int player_x, int player_y) {
    return std::max(std::abs(position_.x() - player_x), std::abs(position_.y() - player_y));
}

QPoint Enemy::NextStep(int player_x, int player_y) {
    if (player_x + 1 >= position_.x() && player_x <= position_.x() + 1 &&
    player_y + 1 >= position_.y() && player_y <= position_.y() + 1){
        return QPoint(position_.x(), position_.y());
    }
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
    SetEnergy(energy_ + Constant::energy_rest);
}

void Enemy::ReduceEnergyForStep() {
    SetEnergy(energy_ - Constant::energy_for_step);
}

void Enemy::ReduceEnergyForHit() {
    SetEnergy(energy_ - Constant::energy_for_hit);
}


void Enemy::ReduceHealth(int delta_health) {
    if (delta_health < 0) {
        return;
    }

    SetHealth(health_ - delta_health);
}

char Enemy::GetEatenTile() { return eaten_tile_; }

void Enemy::SetEatenTile(char tile) {
    eaten_tile_ = tile;
}
