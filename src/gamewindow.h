#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gamelogic.h"
#include "gamesaverloader.h"
#include "statusbarwidget.h"
#include "statusattackedenemybar.h"
#include <QAction>
#include <QGraphicsScene>
#include <QListWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <memory>

class GameWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit GameWindow(const QString &playerName, int mapWidth, int mapHeight,
                      QWidget *parent = nullptr);
  ~GameWindow();
  bool loadGameState();

private:
  QGraphicsScene *scene;
  GameLogic *gameLogic;
  QString playerName;
  GameSaverLoader *gameSaverLoader;
  QListWidget *inventoryWidget;

  QMenuBar *menuBar;
  StatusBarWidget *statusBarWidget;
  std::shared_ptr<StatusAttackedEnemyBar> statusAttackedEnemyBar;
  QAction *saveAction;
  QAction *returnToMenuAction;

  bool is_space_pressed_;

  void render();
  void updateTile(int x, int y, char tile);
  void updateChangedTiles();
  void keyPressEvent(QKeyEvent *event) override;
  void updateInventoryDisplay();
  void updateStatusBar();

private slots:
  void onSaveClicked();
  void onReturnToMenuClicked();
};
#endif // GAMEWINDOW_H
