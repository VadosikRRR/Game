#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QAction>
#include <QGraphicsScene>
#include <QListWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include "../gamelogic.h"
#include "../gamesaverloader.h"
#include "statusbarwidget.h"
#include <memory>

class GameWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void returnToMenu();
    void killCharacter();

public:
    explicit GameWindow(const QString &playerName,
                        int mapWidth,
                        int mapHeight,
                        QWidget *parent = nullptr);
    bool loadGameState();
    GameStatistics &getGameStatistics();

private:
    QGraphicsScene *scene_;
    std::unique_ptr<GameLogic> game_logic_;
    QString player_name_;
    GameSaverLoader *gameSaverLoader;
    QListWidget *inventoryWidget;

    QMenuBar *menuBar;
    StatusBarWidget *statusBarWidget;
    QListWidget *attackedEnemyWidget;
    QAction *saveAction;
    QAction *returnToMenuAction;

    bool is_space_pressed_;


    void render();
    void scaleScene();
    void updateTile(int x, int y, char tile);
    void updateChangedTiles();
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void updateInventoryDisplay();
    void updateAttackedEnemies();
    void updateStatusBar();
    void checkSurvivalStatus();

private slots:
    void onSaveClicked();
    void onReturnToMenuClicked();
};
#endif // GAMEWINDOW_H
