#include "mainmenu.h"
#include "gamewindow.h"
#include "playernamedialog.h"
#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qdialog.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qlist.h>
#include <qinputdialog.h>

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Roguelike Game");
    setFixedSize(300, 200);

    auto* layout = new QVBoxLayout(this);

    auto* newGameButton = new QPushButton("New Game", this);
    auto* loadGameButton = new QPushButton("Load Game", this);
    auto* exitButton = new QPushButton("Exit", this);

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
        QString const playerName = dialog.getPlayerName();
        if (!playerName.isEmpty()) {
            auto* gameWindow = new GameWindow(playerName,kMapWidth,kMapHeight);
            gameWindow->show();
            close();
        }
    }
}
void MainMenu::loadGame() {
    QDir const savesDir("saves");
    if (!savesDir.exists()) {
        QMessageBox::information(this, "No Saves", "No saved games found.");
        return;
    }

    QStringList const saveFiles = savesDir.entryList(QStringList() << "*.txt", QDir::Files);

    if (saveFiles.isEmpty()) {
        QMessageBox::information(this, "No Saves", "No saved games found.");
        return;
    }

    bool ok = false;
    QString selectedSave = QInputDialog::getItem(this, "Load Game", "Select a saved game:", saveFiles, 0, false, &ok);

    if (ok && !selectedSave.isEmpty()) {
        QString const playerName = selectedSave.replace("_save.txt", "");

        auto* gameWindow = new GameWindow(playerName, kMapWidth, kMapHeight);

        if (gameWindow->loadGameState()) {
            gameWindow->show();
            close();
        } else {
            delete gameWindow;
            QMessageBox::warning(this, "Error", "Failed to load the selected game.");
        }
    }
}
