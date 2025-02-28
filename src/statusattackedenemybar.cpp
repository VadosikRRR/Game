#include "statusattackedenemybar.h"
#include <QHBoxLayout>


StatusAttackedEnemyBar::StatusAttackedEnemyBar(const QString &enemyName, int health, int maxHealth,
                                 int attackPower, QWidget *parent)
    : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);

    enemyNameLabel = new QLabel(this);
    enemyNameLabel->setStyleSheet(
        "QLabel { font-weight: bold; font-size: 12px; }");
    enemyNameLabel->setText("Имя: " + enemyName);
    layout->addWidget(enemyNameLabel);

    healthBar = new QProgressBar(this);
    healthBar->setRange(0, maxHealth);
    healthBar->setValue(health);
    healthBar->setTextVisible(true);
    healthBar->setFormat(QString("Здоровье: %1").arg(health));
    healthBar->setFixedWidth(150);
    healthBar->setFixedHeight(20);
    layout->addWidget(healthBar);

    attackPowerLabel = new QLabel(this);
    attackPowerLabel->setStyleSheet("QLabel { color: red; font-size: 12px; }");
    attackPowerLabel->setText("Урон: " + QString::number(attackPower));
    layout->addWidget(attackPowerLabel);

    setFixedHeight(50);
    setLayout(layout);
}

void StatusAttackedEnemyBar::setEnemyName(const QString &name) {
    enemyNameLabel->setText("Имя: " + name);
}

void StatusAttackedEnemyBar::setHealth(int health, int maxHealth) {
    healthBar->setRange(0, maxHealth);
    healthBar->setValue(health);
    healthBar->setFormat(QString("Здоровье: %1").arg(health));
}

void StatusAttackedEnemyBar::setAttackPower(int attackPower) {
    attackPowerLabel->setText("Урон: " + QString::number(attackPower));
}
