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
#include "../constants.h"
#include <memory>

class GameWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void ReturnToMenu();
    void KillCharacter();

public:
    explicit GameWindow(const QString &player_name,
                        int map_width,
                        int map_height,
                        QWidget *parent = nullptr);
    bool LoadGameState();
    GameStatistics &GetGameStatistics();

private:
    QGraphicsScene *scene_;
    std::unique_ptr<GameLogic> game_logic_;
    QString player_name_;
    GameSaverLoader *game_saver_loader_;
    QListWidget *inventory_widget_;

    QMenuBar *menu_bar_;
    StatusBarWidget *status_bar_widget_;
    QListWidget *attacked_enemy_widget_;
    QAction *save_action_;
    QAction *return_to_menu_action_;

    bool is_space_pressed_;


    void Render();
    void ScaleScene();
    void UpdateTile(int x, int y, char tile);
    void UpdateChangedTiles();
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void UpdateInventoryDisplay();
    void UpdateAttackedEnemies();
    void UpdateStatusBar();
    void CheckSurvivalStatus();

private slots:
    void OnSaveClicked();
    void OnReturnToMenuClicked();
    void DrawVisibleTile(int x, int y, const std::vector<std::vector<char>> &map_data);
};
#endif // GAMEWINDOW_H