#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "gamelogic.h"

class NameInputDialog;

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void saveGameState(const QString& filename);
    bool loadGameState(const QString& filename);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *scene;
    GameLogic *gameLogic;
    QString playerName;

    void render();
    void updateTile(int x, int y, char tile);
    void updateChangedTiles();
    void startNewGame();
};

#endif // GAMEWINDOW_H
