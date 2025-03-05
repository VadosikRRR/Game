#include "statusbarwidget.h"

StatusBarWidget::StatusBarWidget(const QString &player_name,
                                 int health,
                                 int attack_power,
                                 QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    player_name_label_ = new QLabel(this);
    player_name_label_->setStyleSheet("QLabel { font-weight: bold; font-size: 15px; }");
    player_name_label_->setText("Имя: " + player_name);
    layout->addWidget(player_name_label_);

    level_label_ = new QLabel(this);
    level_label_->setStyleSheet("QLabel { color: green; font-size: 15px; }");
    level_label_->setText("Текущий уровень: 0");
    layout->addWidget(level_label_);

    health_bar_ = new QProgressBar(this);
    health_bar_->setRange(0, health);
    health_bar_->setValue(health);
    health_bar_->setTextVisible(true);
    health_bar_->setFormat(QString("Здоровье: %1").arg(health));
    health_bar_->setFixedWidth(150);
    health_bar_->setFixedHeight(20);
    layout->addWidget(health_bar_);

    attack_power_label_ = new QLabel(this);
    attack_power_label_->setStyleSheet("QLabel { color: red; font-size: 15px; }");
    attack_power_label_->setText("Урон: " + QString::number(attack_power));
    layout->addWidget(attack_power_label_);

    steps_label_ = new QLabel(this);
    steps_label_->setStyleSheet("QLabel { color: blue; font-size: 15px; }");
    steps_label_->setText("Шаги: 0");
    layout->addWidget(steps_label_);

    enemies_killed_label_ = new QLabel(this);
    enemies_killed_label_->setStyleSheet("QLabel { color: green; font-size: 15px; }");
    enemies_killed_label_->setText("Враги: 0");
    layout->addWidget(enemies_killed_label_);

    setFixedHeight(50);
    setLayout(layout);
}

void StatusBarWidget::SetPlayerName(const QString &name)
{
    player_name_label_->setText("Имя: " + name);
}

void StatusBarWidget::SetHealth(int health, int max_health)
{
    health_bar_->setRange(0, max_health);
    health_bar_->setValue(health);
    health_bar_->setFormat(QString("Здоровье: %1").arg(health));
}

void StatusBarWidget::SetAttackPower(int attack_power)
{
    attack_power_label_->setText("Урон: " + QString::number(attack_power));
}

void StatusBarWidget::SetStepsTaken(int steps)
{
    steps_label_->setText("Шаги: " + QString::number(steps));
}

void StatusBarWidget::SetEnemiesKilled(int enemies_killed)
{
    enemies_killed_label_->setText("Враги: " + QString::number(enemies_killed));
}
void StatusBarWidget::SetLevel(int level)
{
    level_label_->setText("Текущий уровень: " + QString::number(level));
}