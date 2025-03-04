#include "gamewindow.h"
#include <QChar>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMessageBox>
#include "../gamelogic.h"
#include "../gamesaverloader.h"

const int PlayerVisibleDistance = 6;

const char kPLayerChar = '@';
GameWindow::GameWindow(const QString &playerName, int mapWidth, int mapHeight, QWidget *parent)
    : QMainWindow(parent)
    , scene_(new QGraphicsScene(this))
    , game_logic_(new GameLogic(mapWidth, mapHeight, 10))
    , player_name_(playerName)
    , gameSaverLoader(new GameSaverLoader(playerName))
    , inventoryWidget(new QListWidget(this))
    , menuBar(new QMenuBar(this))
    , attackedEnemyWidget(new QListWidget(this))
    , is_space_pressed_(false)
{
    setMenuBar(menuBar);
    QMenu *fileMenu = menuBar->addMenu("Файл");

    saveAction = new QAction("Сохранить игру", this);
    connect(saveAction, &QAction::triggered, this, &GameWindow::onSaveClicked);
    fileMenu->addAction(saveAction);

    returnToMenuAction = new QAction("Вернуться в меню", this);
    connect(returnToMenuAction, &QAction::triggered, this, &GameWindow::onReturnToMenuClicked);
    fileMenu->addAction(returnToMenuAction);

    inventoryWidget->setStyleSheet("QListWidget { background-color: #f0f0f0; }");
    inventoryWidget->setMinimumSize(200, 300);
    attackedEnemyWidget->setStyleSheet("QListWidget { background-color: #f0f0f0; }");
    attackedEnemyWidget->setMinimumSize(200, 300);

    auto *view = new QGraphicsView(scene_, this);

    int sceneWidth = mapWidth * 10;
    int sceneHeight = mapHeight * 10;

    view->setFixedSize(sceneWidth, sceneHeight);

    auto *rightPanel = new QWidget(this);
    auto *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->addWidget(inventoryWidget);
    rightLayout->addWidget(attackedEnemyWidget);

    auto *mainWidget = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->addWidget(view, 3);
    mainLayout->addWidget(rightPanel, 2);

    statusBarWidget = new StatusBarWidget(playerName,
                                          game_logic_->getPlayerHealth(),
                                          game_logic_->getPlayerAttackPower(),
                                          this);
    connect(game_logic_.get(), &GameLogic::statsUpdated, this, &GameWindow::updateStatusBar);

    auto *container = new QWidget(this);
    auto *containerLayout = new QVBoxLayout(container);
    containerLayout->addWidget(mainWidget);
    containerLayout->addWidget(statusBarWidget);

    setCentralWidget(container);

    render();
    updateAttackedEnemies();
    updateInventoryDisplay();
    updateStatusBar();
    scaleScene();
}

void GameWindow::scaleScene()
{
    auto *view = findChild<QGraphicsView *>();
    if (view) {
        view->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
    }
}
void GameWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    auto *view = findChild<QGraphicsView *>();
    if (view) {
        view->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
    }
    updateAttackedEnemies();
    updateInventoryDisplay();
    updateStatusBar();
}
void GameWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    scaleScene();
}
void GameWindow::onSaveClicked()
{
    if (gameSaverLoader->SaveGame(*game_logic_)) {
        QMessageBox::information(this, "Сохранение игры", "Игра сохранена успешно!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Ошибка при загрузке игры.");
    }
}

bool GameWindow::loadGameState()
{
    if (gameSaverLoader->LoadGame(*game_logic_)) {
        render();
        return true;
    }
    QMessageBox::warning(this, "Ошибка", "Ошибка при сохранении игры.");
    return false;
}
void GameWindow::onReturnToMenuClicked()
{
    emit returnToMenu();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int dx = 0;
    int dy = 0;

    if (is_space_pressed_) {
        if (event->key() == Qt::Key_W) {
            game_logic_->HitEnemy(dx, -1);
        } else if (event->key() == Qt::Key_S) {
            game_logic_->HitEnemy(dx, 1);
        } else if (event->key() == Qt::Key_A) {
            game_logic_->HitEnemy(-1, dy);
        } else if (event->key() == Qt::Key_D) {
            game_logic_->HitEnemy(1, dy);
        }
        updateAttackedEnemies();
    } else if (event->key() == Qt::Key_W) {
        game_logic_->MovePlayer(dx, -1);
    } else if (event->key() == Qt::Key_S) {
        game_logic_->MovePlayer(dx, 1);
    } else if (event->key() == Qt::Key_A) {
        game_logic_->MovePlayer(-1, dy);
    } else if (event->key() == Qt::Key_D) {
        game_logic_->MovePlayer(1, dy);
    } else if (event->key() == Qt::Key_Less || event->key() == Qt::Key_Greater) {
        game_logic_->interactWithStairs();
    } else if (event->key() == Qt::Key_E) {
        game_logic_->PickUpItem();
        updateInventoryDisplay();
    } else if (event->key() == Qt::Key_Q) {
        game_logic_->DropItem();
        updateInventoryDisplay();
    } else if (event->key() == Qt::Key_U) {
        game_logic_->UseItem();
        updateInventoryDisplay();
    } else if (event->key() == Qt::Key_2) {
        game_logic_->SelectNextItem();
        updateInventoryDisplay();
        return;
    } else if (event->key() == Qt::Key_1) {
        game_logic_->SelectPreviousItem();
        updateInventoryDisplay();
        return;
    } else if (event->key() == Qt::Key_Space) {
        is_space_pressed_ = true;
        return;
    }

    is_space_pressed_ = false;
    game_logic_->UpdateEnemies();
    updateStatusBar();
    checkSurvivalStatus();
    render();
}
void GameWindow::updateTile(int x, int y, char tile)
{
    auto *tileItem = new QGraphicsSimpleTextItem();
    tileItem->setText(QString(tile));
    tileItem->setBrush(Qt::darkGray);

    tileItem->setFont(QFont("Courier", 10));
    tileItem->setPos(x * 10, y * 10);

    scene_->addItem(tileItem);
}
void GameWindow::updateChangedTiles()
{
    for (const auto &tile : game_logic_->GetChangedTiles()) {
        int const x = tile.x();
        int const y = tile.y();
        char const updatedTile = game_logic_->GetCurrentMap().getTile(x, y);

        updateTile(x, y, updatedTile);
    }

    game_logic_->clearChangedTiles();
}

void GameWindow::render()
{
    scene_->clear();

    const auto &mapData = game_logic_->GetCurrentMap().getData();

    int const playerX = game_logic_->GetPlayerX();
    int const playerY = game_logic_->GetPlayerY();

    for (int y = 0; y < static_cast<int>(mapData.size()); ++y) {
        for (int x = 0; x < static_cast<int>(mapData[y].size()); ++x) {
            updateTile(x, y, ' ');
        }
    }

    for (int var = 1; var <= PlayerVisibleDistance; ++var) {
        for (int var2 = 0; var2 <= var; ++var2) {
            int x = playerX + var - var2;
            int y = playerY + var2;
            drowVisibleTile(x, y, mapData);

            x = playerX - (var - var2);
            y = playerY - var2;
            drowVisibleTile(x, y, mapData);

            x = playerX + var - var2;
            y = playerY - var2;
            drowVisibleTile(x, y, mapData);

            x = playerX - (var - var2);
            y = playerY + var2;
            drowVisibleTile(x, y, mapData);
        }
    }

    updateTile(playerX, playerY, kPLayerChar);
}

void GameWindow::drowVisibleTile(int x, int y, const std::vector<std::vector<char>> &mapData) {
    if (x >= 0 && x < static_cast<int>(mapData[0].size()) &&
        y >= 0 && y < static_cast<int>(mapData.size())) {
        updateTile(x, y, mapData[y][x]);
    }
}

void GameWindow::updateInventoryDisplay()
{
    inventoryWidget->clear();

    const auto &inventory = game_logic_->GetPlayerItems();
    int const currentIndex = game_logic_->GetCurrentItemIndex();

    for (int i = 0; i < static_cast<int>(inventory.size()); ++i) {
        QString itemInfo = inventory[i]->GetName();

        // if (auto collectible =
        // std::dynamic_pointer_cast<CollectiblesItem>(inventory[i])) {
        //     itemInfo += QString(" (x%1)").arg(collectible->GetCount());
        // }

        if (i == currentIndex) {
            itemInfo = "> " + itemInfo;
        }

        inventoryWidget->addItem(itemInfo);
    }
}

void GameWindow::updateStatusBar()
{
    if (statusBarWidget) {
        const GameStatistics &stats = game_logic_->getGameStatistics();
        statusBarWidget->setHealth(game_logic_->getPlayerHealth(),
                                   game_logic_->GetPlayerMaxHealth());
        statusBarWidget->setLevel(game_logic_->GetCurrentLevel());
        statusBarWidget->setAttackPower(game_logic_->getPlayerAttackPower());
        statusBarWidget->setStepsTaken(stats.getTotalStepsTaken());
        statusBarWidget->setEnemiesKilled(stats.getTotalEnemiesKilled());
    }
}

void GameWindow::updateAttackedEnemies()
{
    attackedEnemyWidget->clear();
    std::shared_ptr<Enemy> p_enemy = game_logic_->GetAttackedEnemy();

    if (!p_enemy || p_enemy->GetHealth() <= 0) {
        return;
    }

    QString enemyInfo = QString("%1 (%2): %3/%4")
                            .arg(p_enemy->GetName())
                            .arg(QString(QChar(p_enemy->GetSymbol())))
                            .arg(p_enemy->GetHealth())
                            .arg(p_enemy->GetMaxHealth());

    attackedEnemyWidget->addItem(enemyInfo);
}


void GameWindow::checkSurvivalStatus()
{
    if (game_logic_->getPlayerHealth() == 0) {
        emit killCharacter();
    }
}
GameStatistics &GameWindow::getGameStatistics()
{
    return game_logic_->getGameStatistics();
}

