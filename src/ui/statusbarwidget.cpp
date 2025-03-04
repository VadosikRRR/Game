#include "statusbarwidget.h"

StatusBarWidget::StatusBarWidget(const QString &playerName,
                                 int health,
                                 int attackPower,
                                 QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    playerNameLabel = new QLabel(this);
    playerNameLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 15px; }");
    playerNameLabel->setText("Имя: " + playerName);
    layout->addWidget(playerNameLabel);

    levelLabel = new QLabel(this);
    levelLabel->setStyleSheet("QLabel { color: green; font-size: 15px; }");
    levelLabel->setText("Текущий уровень: " + QString::number(attackPower));
    layout->addWidget(levelLabel);

    healthBar = new QProgressBar(this);
    healthBar->setRange(0, health);
    healthBar->setValue(health);
    healthBar->setTextVisible(true);
    healthBar->setFormat(QString("Здоровье: %1").arg(health));
    healthBar->setFixedWidth(150);
    healthBar->setFixedHeight(20);
    layout->addWidget(healthBar);

    attackPowerLabel = new QLabel(this);
    attackPowerLabel->setStyleSheet("QLabel { color: red; font-size: 15px; }");
    attackPowerLabel->setText("Урон: " + QString::number(attackPower));
    layout->addWidget(attackPowerLabel);

    stepsLabel = new QLabel(this);
    stepsLabel->setStyleSheet("QLabel { color: blue; font-size: 15px; }");
    stepsLabel->setText("Шаги: 0");
    layout->addWidget(stepsLabel);

    enemiesKilledLabel = new QLabel(this);
    enemiesKilledLabel->setStyleSheet("QLabel { color: green; font-size: 15px; }");
    enemiesKilledLabel->setText("Враги: 0");
    layout->addWidget(enemiesKilledLabel);

    setFixedHeight(50);
    setLayout(layout);
}

void StatusBarWidget::setPlayerName(const QString &name)
{
    playerNameLabel->setText("Имя: " + name);
}

void StatusBarWidget::setHealth(int health, int maxHealth)
{
    healthBar->setRange(0, maxHealth);
    healthBar->setValue(health);
    healthBar->setFormat(QString("Здоровье: %1").arg(health));
}

void StatusBarWidget::setAttackPower(int attackPower)
{
    attackPowerLabel->setText("Урон: " + QString::number(attackPower));
}

void StatusBarWidget::setStepsTaken(int steps)
{
    stepsLabel->setText("Шаги: " + QString::number(steps));
}

void StatusBarWidget::setEnemiesKilled(int enemiesKilled)
{
    enemiesKilledLabel->setText("Враги: " + QString::number(enemiesKilled));
}
void StatusBarWidget::setLevel(int level)
{
    levelLabel->setText("Текущий уровень: " + QString::number(level));
}
