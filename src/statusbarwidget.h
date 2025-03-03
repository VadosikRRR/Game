#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

class StatusBarWidget : public QWidget {
  Q_OBJECT

public:
  explicit StatusBarWidget(const QString &playerName, int health,
                           int attackPower, QWidget *parent = nullptr);
  void setPlayerName(const QString &name);
  void setHealth(int health, int maxHealth);
  void setAttackPower(int attackPower);

private:
  QLabel *playerNameLabel;
  QProgressBar *healthBar;
  QLabel *attackPowerLabel;
};

#endif // STATUSBARWIDGET_H
