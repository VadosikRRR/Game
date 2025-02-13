#include "gamewindow.h"
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include "gamelogic.h"
#include "gamesaverloader.h"
#include "item.h"
#include "mainmenu.h"

const char kPLayerChar = '@';
GameWindow::GameWindow(const QString& playerName, int mapWidth, int mapHeight, QWidget* parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), gameLogic(new GameLogic(mapWidth, mapHeight, 10)), playerName(playerName), gameSaverLoader(new GameSaverLoader(playerName)), menuBar(new QMenuBar(this)), inventoryWidget(new QListWidget(this)) {
    setFixedSize(1280, 720);

    setMenuBar(menuBar);

    QMenu* fileMenu = menuBar->addMenu("Файл");

    saveAction = new QAction("Сохранить игру", this);
    connect(saveAction, &QAction::triggered, this, &GameWindow::onSaveClicked);
    fileMenu->addAction(saveAction);

    returnToMenuAction = new QAction("Вернуться в меню", this);
    connect(returnToMenuAction, &QAction::triggered, this, &GameWindow::onReturnToMenuClicked);
    fileMenu->addAction(returnToMenuAction);

    
    inventoryWidget->setFixedWidth(200);
    inventoryWidget->setStyleSheet("QListWidget { background-color: #f0f0f0; }");

    auto* mainWidget = new QWidget(this);
    auto* layout = new QHBoxLayout(mainWidget);

    auto* view = new QGraphicsView(scene, this);
    view->setFixedSize(1080 - 50, 720 - menuBar->height());

    layout->addWidget(view);
    layout->addWidget(inventoryWidget);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    statusBarWidget = new StatusBarWidget(playerName,
                                          gameLogic->getPlayerHealth(),
                                          gameLogic->getPlayerAttackPower(),
                                          this);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainWidget);
    mainLayout->addWidget(statusBarWidget);

    QWidget* container = new QWidget(this);
    container->setLayout(mainLayout);
    setCentralWidget(container);

    render();
    updateInventoryDisplay();
    updateStatusBar();
}
void GameWindow::onSaveClicked() {
    if (gameSaverLoader->saveGame(*gameLogic)) {
        QMessageBox::information(this, "Game Saved", "Game saved successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save the game.");
    }
}

bool GameWindow::loadGameState()
{
    if (gameSaverLoader->loadGame(*gameLogic)) {
        render();
        return true;
    }         QMessageBox::warning(this, "Error", "Failed to load the game.");
        return false;
}

void GameWindow::onReturnToMenuClicked() {
    this->close();
    auto* mainMenu = new MainMenu();
    mainMenu->show();
}
GameWindow::~GameWindow() {
    delete scene;
    delete gameLogic;
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    int dx = 0;
    int dy = 0;

    if (event->key() == Qt::Key_W) {
        gameLogic->MovePlayer(dx, -1);
        render();
    } else if (event->key() == Qt::Key_S) {
        gameLogic->MovePlayer(dx, 1);
        render();
    } else if (event->key() == Qt::Key_A) {
        gameLogic->MovePlayer(-1, dy);
        render();
    } else if (event->key() == Qt::Key_D) {
        gameLogic->MovePlayer(1, dy);
        render();
    } else if (event->key() == Qt::Key_Less || event->key() == Qt::Key_Greater){
        gameLogic->interactWithStairs();
        render();
    } else if (event->key() == Qt::Key_E) {
        gameLogic->PickUpItem();
        updateInventoryDisplay();
        render();
    } else if (event->key() == Qt::Key_Q) {
        gameLogic->DropItem();
        updateInventoryDisplay();
        render();
    } else if (event->key() == Qt::Key_U) {
        gameLogic->UseItem();
        updateInventoryDisplay();
        render();
    }   else if (event->key() == Qt::Key_2) {
        gameLogic->SelectNextItem();
        updateInventoryDisplay();
    } else if (event->key() == Qt::Key_1) {
        gameLogic->SelectPreviousItem();
        updateInventoryDisplay();
    }
    updateStatusBar();
}
void GameWindow::updateTile(int x, int y, char tile) {
    auto* tileItem = new QGraphicsSimpleTextItem();
    tileItem->setText(QString(tile));
    tileItem->setBrush(Qt::darkGray);

    tileItem->setFont(QFont("Courier", 10));
    tileItem->setPos(x * 10, y * 10);

    scene->addItem(tileItem);
}
void GameWindow::updateChangedTiles() {
    for (const auto& tile : gameLogic->GetChangedTiles()) {
        int const x = tile.x();
        int const y = tile.y();
        char const updatedTile = gameLogic->GetCurrentMap().getTile(x, y);

        updateTile(x, y, updatedTile);
    }

    gameLogic->clearChangedTiles();
}

void GameWindow::render() {
    scene->clear();

    const auto& mapData = gameLogic->GetCurrentMap().getData();

    for (int y = 0; y < mapData.size(); ++y) {
        for (int x = 0; x < mapData[y].size(); ++x) {
            updateTile(x, y, mapData[y][x]);
        }
    }

    int const playerX = gameLogic->GetPlayerX();
    int const playerY = gameLogic->GetPlayerY();
    updateTile(playerX, playerY, kPLayerChar);
}

void GameWindow::updateInventoryDisplay() {
    inventoryWidget->clear();

    const auto& inventory = gameLogic->GetPlayerItems();
    int const currentIndex = gameLogic->GetCurrentItemIndex();

    for (size_t i = 0; i < inventory.size(); ++i) {
        QString itemInfo = inventory[i]->GetName();

        if (auto collectible = std::dynamic_pointer_cast<CollectiblesItem>(inventory[i])) {
            itemInfo += QString(" (x%1)").arg(collectible->GetCount());
        }

        if (i == currentIndex) {
            itemInfo = "> " + itemInfo;         }

        inventoryWidget->addItem(itemInfo);
    }
}
void GameWindow::updateStatusBar()
{
    if (statusBarWidget) {
        statusBarWidget->setHealth(gameLogic->getPlayerHealth());
        statusBarWidget->setAttackPower(gameLogic->getPlayerAttackPower());
    }
}
