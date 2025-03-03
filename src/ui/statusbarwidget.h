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
    explicit StatusBarWidget(const QString &playerName,
                             int health,
                             int attackPower,
                             QWidget *parent = nullptr);
    void setPlayerName(const QString &name);
    void setHealth(int health, int maxHealth);
    void setAttackPower(int attackPower);
    void setStepsTaken(int steps);
    void setEnemiesKilled(int enemiesKilled);
    void setLevel(int level);

private:
    QLabel *playerNameLabel;
    QLabel *levelLabel;
    QProgressBar *healthBar;
    QLabel *attackPowerLabel;
    QLabel *stepsLabel;
    QLabel *enemiesKilledLabel;
};

#endif // STATUSBARWIDGET_H
