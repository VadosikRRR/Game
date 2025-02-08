#include "gamewindow.h"
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>


GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), gameLogic(new GameLogic(80, 60, 10)) {
    setFixedSize(1280, 720);

    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setGeometry(0, 0, 1280, 720);

    render();
}

GameWindow::~GameWindow() {
    delete scene;
    delete gameLogic;
}
void GameWindow::saveGameState(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);

        out << gameLogic->getCurrentLevel() << "\n";
        out << gameLogic->getPlayerX() << " " << gameLogic->getPlayerX() << "\n";

        const auto& mapData = gameLogic->getCurrentMap().getData();
        for (const auto& row : mapData) {
            out << QString::fromStdString(std::string(row.begin(), row.end())) << "\n";
        }

        file.close();
    }
}
bool GameWindow::loadGameState(const QString& filename) {
    return true;
}
void GameWindow::keyPressEvent(QKeyEvent *event) {
    int dx = 0, dy = 0;

    if (event->key() == Qt::Key_W) {
        gameLogic->movePlayer(dx, -1);
        render();
    } else if (event->key() == Qt::Key_S) {
        gameLogic->movePlayer(dx, 1);
        render();
    } else if (event->key() == Qt::Key_A) {
        gameLogic->movePlayer(-1, dy);
        render();
    } else if (event->key() == Qt::Key_D) {
        gameLogic->movePlayer(1, dy);
        render();
    }
}
void GameWindow::updateTile(int x, int y, char tile) {
    QGraphicsSimpleTextItem* tileItem = new QGraphicsSimpleTextItem();
    tileItem->setText(QString(tile));
    tileItem->setBrush(Qt::darkGray);

    tileItem->setFont(QFont("Courier", 10));
    tileItem->setPos(x * 10, y * 10);


    scene->addItem(tileItem);
}
void GameWindow::updateChangedTiles() {
    for (const auto& tile : gameLogic->getChangedTiles()) {
        int x = tile.x();
        int y = tile.y();
        char updatedTile = gameLogic->getCurrentMap().getTile(x, y);

        updateTile(x, y, updatedTile);
    }

    gameLogic->clearChangedTiles();
}

void GameWindow::render() {
    scene->clear();

    const auto& mapData = gameLogic->getCurrentMap().getData();

    for (int y = 0; y < mapData.size(); ++y) {
        for (int x = 0; x < mapData[y].size(); ++x) {
            updateTile(x, y, mapData[y][x]);
        }
    }
}

