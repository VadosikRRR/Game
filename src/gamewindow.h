#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "gamelogic.h"
#include <QPushButton>

#include <QMenuBar>
#include <QAction>

#include "gamesaverloader.h"

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit GameWindow(const QString& playerName, int mapWidth, int mapHeight, QWidget* parent = nullptr);
    ~GameWindow();
    bool loadGameState();

private:
    QGraphicsScene* scene;
    GameLogic* gameLogic;
    QString playerName;
    GameSaverLoader* gameSaverLoader;

    QMenuBar* menuBar;
    QAction* saveAction;
    QAction* returnToMenuAction;

    void render();
    void updateTile(int x, int y, char tile);
    void updateChangedTiles();
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void onSaveClicked();
    void onReturnToMenuClicked();
};
#endif // GAMEWINDOW_H
