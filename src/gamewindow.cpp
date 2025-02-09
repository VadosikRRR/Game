#include "gamewindow.h"
#include "mainmenu.h"
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>


GameWindow::GameWindow(const QString& playerName,int mapWidth, int mapHeight, QWidget* parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), gameLogic(new GameLogic(mapWidth, mapWidth, 10)), playerName(playerName) {
    setFixedSize(1280, 720);

    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu* fileMenu = menuBar->addMenu("Файл");

    saveAction = new QAction("Сохранить игру", this);
    connect(saveAction, &QAction::triggered, this, &GameWindow::onSaveClicked);
    fileMenu->addAction(saveAction);

    returnToMenuAction = new QAction("Вернуться в меню", this);
    connect(returnToMenuAction, &QAction::triggered, this, &GameWindow::onReturnToMenuClicked);
    fileMenu->addAction(returnToMenuAction);

    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setGeometry(0, menuBar->height(), 1280, 720 - menuBar->height());
    render();
}

void GameWindow::onSaveClicked() {
    saveGameState();
}

void GameWindow::onReturnToMenuClicked() {
    this->close();
    MainMenu* mainMenu = new MainMenu();
    mainMenu->show();
}
GameWindow::~GameWindow() {
    delete scene;
    delete gameLogic;
}
void GameWindow::saveGameState() {
    QDir().mkdir("saves");

    QString filename = QString("saves/%1_save.txt").arg(playerName);

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);

        out << playerName << "\n";
        out << gameLogic->getCurrentLevel() << "\n";
        out << gameLogic->getPlayerX() << " " << gameLogic->getPlayerY() << "\n";

        for (const auto& map : gameLogic->getAllMaps()) {
            const auto& mapData = map.getData();
            for (const auto& row : mapData) {
                out << QString::fromStdString(std::string(row.begin(), row.end())) << "\n";
            }
            out << "---\n";
        }

        file.close();
        QMessageBox::information(this, "Game Saved", "Game saved successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save the game.");
    }
}
bool GameWindow::loadGameState() {
    QString filename = QString("saves/%1_save.txt").arg(playerName);

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);

        playerName = in.readLine();

        int currentLevel;
        in >> currentLevel;
        gameLogic->setCurrentLevel(currentLevel);

        int playerX, playerY;
        in >> playerX >> playerY;
        gameLogic->setPlayerPosition(playerX, playerY);

        in.readLine();

        std::vector<Map> maps;
        std::vector<std::vector<char>> mapData;
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line == "---") {
                Map map(mapData[0].size(), mapData.size());
                map.setData(mapData);
                maps.push_back(map);
                mapData.clear();
            } else {
                std::vector<char> row;
                for (QChar qchar : line) {
                    row.push_back(qchar.toLatin1());
                }
                mapData.push_back(row);
            }
        }
        gameLogic->setAllMaps(maps);

        render();

        file.close();
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to load the game.");
        return false;
    }
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
    } else if (event->key() == Qt::Key_Less || event->key() == Qt::Key_Greater){
        gameLogic->interactWithStairs();
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

    int playerX = gameLogic->getPlayerX();
    int playerY = gameLogic->getPlayerY();
    updateTile(playerX, playerY, '@');
}

