#include "statusbarwidget.h"

StatusBarWidget::StatusBarWidget(const QString &playerName, int health,
                                 int attackPower, QWidget *parent)
    : QWidget(parent) {
  QHBoxLayout *layout = new QHBoxLayout(this);

  playerNameLabel = new QLabel(this);
  playerNameLabel->setStyleSheet(
      "QLabel { font-weight: bold; font-size: 12px; }");
  playerNameLabel->setText("Имя: " + playerName);
  layout->addWidget(playerNameLabel);

  healthBar = new QProgressBar(this);
  healthBar->setRange(0, health);
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

void StatusBarWidget::setPlayerName(const QString &name) {
  playerNameLabel->setText("Имя: " + name);
}

void StatusBarWidget::setHealth(int health, int maxHealth) {
  healthBar->setRange(0, maxHealth);
  healthBar->setValue(health);
  healthBar->setFormat(QString("Здоровье: %1").arg(health));
}

void StatusBarWidget::setAttackPower(int attackPower) {
  attackPowerLabel->setText("Урон: " + QString::number(attackPower));
}
