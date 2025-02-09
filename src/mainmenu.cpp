#include "mainmenu.h"
#include "gamewindow.h"
#include "playernamedialog.h"
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) {
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

void MainMenu::startNewGame() {
    PlayerNameDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString playerName = dialog.getPlayerName();
        if (!playerName.isEmpty()) {
            GameWindow* gameWindow = new GameWindow(playerName,kMapWidth,kMapHeight);
            gameWindow->show();
            close();
        }
    }
}
void MainMenu::loadGame() {
    QDir savesDir("saves");
    if (!savesDir.exists()) {
        QMessageBox::information(this, "No Saves", "No saved games found.");
        return;
    }

    QStringList saveFiles = savesDir.entryList(QStringList() << "*.txt", QDir::Files);

    if (saveFiles.isEmpty()) {
        QMessageBox::information(this, "No Saves", "No saved games found.");
        return;
    }

    bool ok;
    QString selectedSave = QInputDialog::getItem(this, "Load Game", "Select a saved game:", saveFiles, 0, false, &ok);

    if (ok && !selectedSave.isEmpty()) {
        QString playerName = selectedSave.replace("_save.txt", "");

        GameWindow* gameWindow = new GameWindow(playerName, kMapWidth, kMapHeight);

        if (gameWindow->loadGameState()) {
            gameWindow->show();
            close();
        } else {
            delete gameWindow;
            QMessageBox::warning(this, "Error", "Failed to load the selected game.");
        }
    }
}
