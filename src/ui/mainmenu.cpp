#include "mainmenu.h"
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include "../config.h"
#include "playernamedialog.h"

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Roguelike Game");
    setFixedSize(300, 250);

    auto *layout = new QVBoxLayout(this);

    new_game_button_ = new QPushButton("Новая игра", this);
    load_game_button_ = new QPushButton("Загрузить игру", this);
    continue_button_ = new QPushButton("Продолжить", this);
    exit_button_ = new QPushButton("Выход", this);

    layout->addWidget(continue_button_);
    layout->addWidget(new_game_button_);
    layout->addWidget(load_game_button_);
    layout->addWidget(exit_button_);

    continue_button_->setVisible(false);

    connect(new_game_button_, &QPushButton::clicked, this, &MainMenu::StartNewGame);
    connect(load_game_button_, &QPushButton::clicked, this, &MainMenu::LoadGame);
    connect(continue_button_, &QPushButton::clicked, this, &MainMenu::ContinueGame);
    connect(exit_button_, &QPushButton::clicked, this, &MainMenu::close);
}

void MainMenu::StartNewGame()
{
    PlayerNameDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }
    QString const playerName = dialog.getPlayerName();
    if (playerName.isEmpty()) {
        return;
    }

    if (current_game_window_) {
        current_game_window_->close();
    }
    current_game_window_ = std::make_unique<GameWindow>(playerName,
                                                        config::kMapWidth,
                                                        config::kMapHeight);
    current_game_window_->setAttribute(Qt::WA_DeleteOnClose);
    connect(current_game_window_.get(), &GameWindow::returnToMenu, this, [this]() {
        current_game_window_->hide();
        continue_button_->setVisible(true);
        this->show();
    });
    current_game_window_->show();
    continue_button_->setVisible(true);
    this->hide();
}

void MainMenu::LoadGame()
{
    QDir const savesDir("saves");
    if (!savesDir.exists()) {
        QMessageBox::information(this, "Нет сохранений", "Сохраненные игры не найдены.");
        return;
    }

    QStringList const saveFiles = savesDir.entryList(QStringList() << "*.txt", QDir::Files);

    if (saveFiles.isEmpty()) {
        QMessageBox::information(this, "Нет сохранений", "Сохраненные игры не найдены.");
        return;
    }

    bool ok = false;
    QString selectedSave = QInputDialog::getItem(this,
                                                 "Загрузить игру",
                                                 "Выберите сохранение:",
                                                 saveFiles,
                                                 0,
                                                 false,
                                                 &ok);

    if (!ok || selectedSave.isEmpty()) {
        return;
    }
    QString const playerName = selectedSave.replace("_save.txt", "");

    if (current_game_window_) {
        current_game_window_->close();
    }
    current_game_window_ = std::make_unique<GameWindow>(playerName,
                                                        config::kMapWidth,
                                                        config::kMapHeight);
    current_game_window_->setAttribute(Qt::WA_DeleteOnClose);
    connect(current_game_window_.get(), &GameWindow::returnToMenu, this, [this]() {
        current_game_window_->hide();
        continue_button_->setVisible(true);
    });

    if (current_game_window_->loadGameState()) {
        current_game_window_->show();
        continue_button_->setVisible(true);
        this->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить игру.");
    }
}

void MainMenu::ContinueGame()
{
    if (current_game_window_) {
        current_game_window_->show();
        this->hide();
    }
}
