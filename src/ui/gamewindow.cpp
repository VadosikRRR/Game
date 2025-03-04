#include "gamewindow.h"
#include <QChar>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMessageBox>
#include "../gamelogic.h"
#include "../gamesaverloader.h"

const int kPlayerVisibleDistance = 6;

const char kPLayerChar = '@';
GameWindow::GameWindow(const QString &player_name, int map_width, int map_height, QWidget *parent)
    : QMainWindow(parent)
    , scene_(new QGraphicsScene(this))
    , game_logic_(new GameLogic(map_width, map_height, 10))
    , player_name_(player_name)
    , game_saver_loader_(new GameSaverLoader(player_name))
    , inventory_widget_(new QListWidget(this))
    , menu_bar_(new QMenuBar(this))
    , attacked_enemy_widget_(new QListWidget(this))
    , is_space_pressed_(false)
{
    setMenuBar(menu_bar_);
    QMenu *file_menu = menu_bar_->addMenu("Файл");

    save_action_ = new QAction("Сохранить игру", this);
    connect(save_action_, &QAction::triggered, this, &GameWindow::OnSaveClicked);
    file_menu->addAction(save_action_);

    return_to_menu_action_ = new QAction("Вернуться в меню", this);
    connect(return_to_menu_action_, &QAction::triggered, this, &GameWindow::OnReturnToMenuClicked);
    file_menu->addAction(return_to_menu_action_);

    inventory_widget_->setStyleSheet("QListWidget { background-color: #f0f0f0; }");
    inventory_widget_->setMinimumSize(200, 300);
    attacked_enemy_widget_->setStyleSheet("QListWidget { background-color: #f0f0f0; }");
    attacked_enemy_widget_->setMinimumSize(200, 300);

    auto *view = new QGraphicsView(scene_, this);

    int scene_width = map_width * 10;
    int scene_height = map_height * 10;

    view->setFixedSize(scene_width, scene_height);

    auto *right_panel = new QWidget(this);
    auto *right_layout = new QVBoxLayout(right_panel);
    right_layout->addWidget(inventory_widget_);
    right_layout->addWidget(attacked_enemy_widget_);

    auto *main_widget = new QWidget(this);
    auto *main_layout = new QHBoxLayout(main_widget);
    main_layout->addWidget(view, 3);
    main_layout->addWidget(right_panel, 2);

    status_bar_widget_ = new StatusBarWidget(player_name,
                                          game_logic_->GetPlayerHealth(),
                                          game_logic_->GetPlayerAttackPower(),
                                          this);
    connect(game_logic_.get(), &GameLogic::StatsUpdated, this, &GameWindow::UpdateStatusBar);

    auto *container = new QWidget(this);
    auto *container_layout = new QVBoxLayout(container);
    container_layout->addWidget(main_widget);
    container_layout->addWidget(status_bar_widget_);

    setCentralWidget(container);

    Render();
    UpdateAttackedEnemies();
    UpdateInventoryDisplay();
    UpdateStatusBar();
    ScaleScene();
}

void GameWindow::ScaleScene()
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
    UpdateAttackedEnemies();
    UpdateInventoryDisplay();
    UpdateStatusBar();
}
void GameWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ScaleScene();
}
void GameWindow::OnSaveClicked()
{
    if (game_saver_loader_->SaveGame(*game_logic_)) {
        QMessageBox::information(this, "Сохранение игры", "Игра сохранена успешно!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Ошибка при загрузке игры.");
    }
}

bool GameWindow::LoadGameState()
{
    if (game_saver_loader_->LoadGame(*game_logic_)) {
        Render();
        return true;
    }
    QMessageBox::warning(this, "Ошибка", "Ошибка при сохранении игры.");
    return false;
}
void GameWindow::OnReturnToMenuClicked()
{
    emit ReturnToMenu();
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
        UpdateAttackedEnemies();
    } else if (event->key() == Qt::Key_W) {
        game_logic_->MovePlayer(dx, -1);
    } else if (event->key() == Qt::Key_S) {
        game_logic_->MovePlayer(dx, 1);
    } else if (event->key() == Qt::Key_A) {
        game_logic_->MovePlayer(-1, dy);
    } else if (event->key() == Qt::Key_D) {
        game_logic_->MovePlayer(1, dy);
    } else if (event->key() == Qt::Key_Less || event->key() == Qt::Key_Greater) {
        game_logic_->InteractWithStairs();
    } else if (event->key() == Qt::Key_E) {
        game_logic_->PickUpItem();
        UpdateInventoryDisplay();
    } else if (event->key() == Qt::Key_Q) {
        game_logic_->DropItem();
        UpdateInventoryDisplay();
    } else if (event->key() == Qt::Key_U) {
        game_logic_->UseItem();
        UpdateInventoryDisplay();
    } else if (event->key() == Qt::Key_2) {
        game_logic_->SelectNextItem();
        UpdateInventoryDisplay();
        return;
    } else if (event->key() == Qt::Key_1) {
        game_logic_->SelectPreviousItem();
        UpdateInventoryDisplay();
        return;
    } else if (event->key() == Qt::Key_Space) {
        is_space_pressed_ = true;
        return;
    }

    is_space_pressed_ = false;
    game_logic_->UpdateEnemies();
    UpdateStatusBar();
    CheckSurvivalStatus();
    Render();
}
void GameWindow::UpdateTile(int x, int y, char tile)
{
    auto *tile_item = new QGraphicsSimpleTextItem();
    tile_item->setText(QString(tile));
    tile_item->setBrush(Qt::darkGray);

    tile_item->setFont(QFont("Courier", 10));
    tile_item->setPos(x * 10, y * 10);

    scene_->addItem(tile_item);
}
void GameWindow::UpdateChangedTiles()
{
    for (const auto &tile : game_logic_->GetChangedTiles()) {
        int const x = tile.x();
        int const y = tile.y();
        char const updated_tile = game_logic_->GetCurrentMap().GetTile(x, y);

        UpdateTile(x, y, updated_tile);
    }

    game_logic_->ClearChangedTiles();
}

void GameWindow::Render()
{
    scene_->clear();
    const Map & now_map = game_logic_->GetCurrentMap();
    const auto &map_data = game_logic_->GetCurrentMap().GetData();

    int const player_x = game_logic_->GetPlayerX();
    int const player_y = game_logic_->GetPlayerY();



    for (int y = 0; y < static_cast<int>(map_data.size()); ++y) {
        for (int x = 0; x < static_cast<int>(map_data[y].size()); ++x) {
            if (now_map.IsExplored(x, y)) {
                UpdateTile(x, y, map_data[y][x]);
            } else {
                UpdateTile(x, y, ' ');
            }
        }
    }

    UpdateTile(player_x, player_y, kPLayerChar);
}

void GameWindow::DrawVisibleTile(int x, int y, const std::vector<std::vector<char>> &map_data) {
    if (x >= 0 && x < static_cast<int>(map_data[0].size()) &&
        y >= 0 && y < static_cast<int>(map_data.size())) {
        UpdateTile(x, y, map_data[y][x]);
    }
}

void GameWindow::UpdateInventoryDisplay()
{
    inventory_widget_->clear();

    const auto &inventory = game_logic_->GetPlayerItems();
    int const current_index = game_logic_->GetCurrentItemIndex();

    for (int i = 0; i < static_cast<int>(inventory.size()); ++i) {
        QString item_info = inventory[i]->GetName();

        if (i == current_index) {
            item_info = "> " + item_info;
        }

        inventory_widget_->addItem(item_info);
    }
}

void GameWindow::UpdateStatusBar()
{
    if (status_bar_widget_) {
        const GameStatistics &stats = game_logic_->GetGameStatistics();
        status_bar_widget_->SetHealth(game_logic_->GetPlayerHealth(),
                                   game_logic_->GetPlayerMaxHealth());
        status_bar_widget_->SetLevel(game_logic_->GetCurrentLevel());
        status_bar_widget_->SetAttackPower(game_logic_->GetPlayerAttackPower());
        status_bar_widget_->SetStepsTaken(stats.GetTotalStepsTaken());
        status_bar_widget_->SetEnemiesKilled(stats.GetTotalEnemiesKilled());
    }
}

void GameWindow::UpdateAttackedEnemies()
{
    attacked_enemy_widget_->clear();
    std::shared_ptr<Enemy> p_enemy = game_logic_->GetAttackedEnemy();

    if (!p_enemy || p_enemy->GetHealth() <= 0) {
        return;
    }

    QString enemy_info = QString("%1 (%2): %3/%4")
                            .arg(p_enemy->GetName())
                            .arg(QString(QChar(p_enemy->GetSymbol())))
                            .arg(p_enemy->GetHealth())
                            .arg(p_enemy->GetMaxHealth());

    attacked_enemy_widget_->addItem(enemy_info);
}


void GameWindow::CheckSurvivalStatus()
{
    if (game_logic_->GetPlayerHealth() == 0) {
        emit KillCharacter();
    }
}
GameStatistics &GameWindow::GetGameStatistics()
{
    return game_logic_->GetGameStatistics();
}
