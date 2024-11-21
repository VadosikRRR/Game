#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "gamelogic.h"

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
    void updateTile(int x, int y, char tile);
    void updateChangedTiles();
    void render();
};

#endif // GAMEWINDOW_H
