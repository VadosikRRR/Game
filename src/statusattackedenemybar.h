#ifndef STATUSATTACKEDENEMYBAR_H
#define STATUSATTACKEDENEMYBAR_H

#include "enemy.h"
#include <QWidget>
#include <QLabel>
#include <QProgressBar>


class StatusAttackedEnemyBar : public QWidget {
    Q_OBJECT

private:
    QLabel *enemyNameLabel;
    QProgressBar *healthBar;
    QLabel *attackPowerLabel;

public:
    explicit StatusAttackedEnemyBar(const QString &enemy_name, int health, int maxHealth,
                             int attack_power, QWidget *parent = nullptr);
    void setEnemyName(const QString &name);
    void setHealth(int health, int max_health);
    void setAttackPower(int attack_power);
};

#endif // STATUSATTACKEDENEMYBAR_H
