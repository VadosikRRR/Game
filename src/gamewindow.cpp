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

//TODO: Релизовать логику подбора предмета [добавлять в  Player::inventory_] [использовать метод Inventory::Add(Item *), получать предмет по координате 
// из Map::items_], когда стоишь на нём. Если предмет является наследником CollectiblesItem, то либо добавить его инвентарь, если объекта этого типа в инвентаре не было,
// либо увеличить у объекта этого типа поле count_ [с помощью метода Add()]
// сделать отрисовку инвентаря в окошке, или хотя бы вывод предмета, на который сейчас указывает Inventory::currItem [итератор по списку]
// сделать так чтобы стрелки двигали Inventory::currItem [использовать методы Inventory::Next(), Inventory::Previous()]
// реализовать логику выкидывания предмета, на который указывает Inventory::currItem [Inventory::Drop() удаляет как раз этот предмет из инвентаря]
// после подбора предмет должен пропасть из Map::items_, а при выкидывании наоборот [ну и соответственно надо поменять на карте тайлы].

const char kPLayerChar = '@';
GameWindow::GameWindow(const QString& playerName, int mapWidth, int mapHeight, QWidget* parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), gameLogic(new GameLogic(mapWidth, mapHeight, 10)), playerName(playerName) {
    setFixedSize(1280, 720);

    gameSaverLoader = new GameSaverLoader(playerName); // Инициализация GameSaverLoader

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
    if (gameSaverLoader->saveGame(*gameLogic)) {
        QMessageBox::information(this, "Game Saved", "Game saved successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save the game.");
    }
}

bool GameWindow::loadGameState() {
    if (gameSaverLoader->loadGame(*gameLogic)) {
        render();
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to load the game.");
        return false;
    }
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
    updateTile(playerX, playerY, kPLayerChar);
}

