#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

class StatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBarWidget(const QString &player_name,
                             int health,
                             int attack_power,
                             QWidget *parent = nullptr);
    void SetPlayerName(const QString &name);
    void SetHealth(int health, int max_health);
    void SetAttackPower(int attack_power);
    void SetStepsTaken(int steps);
    void SetEnemiesKilled(int enemies_killed);
    void SetLevel(int level);

private:
    QLabel *player_name_label_;
    QLabel *level_label_;
    QProgressBar *health_bar_;
    QLabel *attack_power_label_;
    QLabel *steps_label_;
    QLabel *enemies_killed_label_;
};

#endif // STATUSBARWIDGET_H