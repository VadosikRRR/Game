#ifndef MAINMENU_H
#define MAINMENU_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "gamewindow.h"
#include "../constants.h"

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);

private slots:
    void StartNewGame();
    void LoadGame();
    void ContinueGame();
    void HandleKillCharacter();

private:
    QPushButton *new_game_button_;
    QPushButton *load_game_button_;
    QPushButton *continue_button_;
    QPushButton *exit_button_;

    std::unique_ptr<GameWindow> current_game_window_;
};

#endif // MAINMENU_H