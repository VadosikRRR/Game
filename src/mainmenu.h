#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "gamewindow.h"

class MainMenu : public QWidget {
    Q_OBJECT

public:
    MainMenu(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("Roguelike Game");
        setFixedSize(300, 200);

        QVBoxLayout* layout = new QVBoxLayout(this);

        QPushButton* newGameButton = new QPushButton("New Game", this);
        QPushButton* loadGameButton = new QPushButton("Load Game", this);
        QPushButton* exitButton = new QPushButton("Exit", this);

        layout->addWidget(newGameButton);
        layout->addWidget(loadGameButton);
        layout->addWidget(exitButton);

        connect(newGameButton, &QPushButton::clicked, this, &MainMenu::startNewGame);
        connect(loadGameButton, &QPushButton::clicked, this, &MainMenu::loadGame);
        connect(exitButton, &QPushButton::clicked, this, &MainMenu::close);
    }

private slots:
    void startNewGame() {
        GameWindow* gameWindow = new GameWindow();
        gameWindow->show();
        close();
    }

    void loadGame() {
        GameWindow* gameWindow = new GameWindow();
        if (gameWindow->loadGameState("savegame.txt")) {
            gameWindow->show();
            close();
        } else {
            delete gameWindow;
        }
    }
};
