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
    QString const player_name = dialog.getPlayerName();
    if (player_name.isEmpty()) {
        return;
    }

    if (current_game_window_) {
        current_game_window_->close();
    }
    current_game_window_ = std::make_unique<GameWindow>(player_name,
                                                        config::kMapWidth,
                                                        config::kMapHeight);

    connect(current_game_window_.get(), &GameWindow::returnToMenu, this, [this]() {
        current_game_window_->hide();
        continue_button_->setVisible(true);
        this->show();
    });

    connect(current_game_window_.get(),
            &GameWindow::killCharacter,
            this,
            &MainMenu::HandleKillCharacter);

    current_game_window_->show();
    continue_button_->setVisible(true);
    this->hide();
}

void MainMenu::LoadGame()
{
    QDir const saves_dir("saves");
    if (!saves_dir.exists()) {
        QMessageBox::information(this, "Нет сохранений", "Сохраненные игры не найдены.");
        return;
    }

    QStringList const save_files = saves_dir.entryList(QStringList() << "*.json", QDir::Files);

    if (save_files.isEmpty()) {
        QMessageBox::information(this, "Нет сохранений", "Сохраненные игры не найдены.");
        return;
    }

    bool ok = false;
    QString selected_save = QInputDialog::getItem(this,
                                                 "Загрузить игру",
                                                 "Выберите сохранение:",
                                                 save_files,
                                                 0,
                                                 false,
                                                 &ok);

    if (!ok || selected_save.isEmpty()) {
        return;
    }
    QString const player_name = selected_save.replace("_save.json", "");

    if (current_game_window_) {
        current_game_window_->close();
    }
    current_game_window_ = std::make_unique<GameWindow>(player_name,
                                                        config::kMapWidth,
                                                        config::kMapHeight);
    connect(current_game_window_.get(), &GameWindow::returnToMenu, this, [this]() {
        current_game_window_->hide();
        continue_button_->setVisible(true);
        this->show();
    });
    connect(current_game_window_.get(),
            &GameWindow::killCharacter,
            this,
            &MainMenu::HandleKillCharacter);

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


void MainMenu::HandleKillCharacter()
{
    current_game_window_->hide();

    const GameStatistics &stats = current_game_window_->getGameStatistics();

    QString message = QString("Игрок %1 погиб!\n\n"
                              "Статистика игры:\n"
                              "Уровень: %2\n"
                              "Убито врагов: %3\n"
                              "Шагов сделано: %4\n")
                          .arg(stats.getPlayerName())
                          .arg(stats.getCurrentLevel())
                          .arg(stats.getTotalEnemiesKilled())
                          .arg(stats.getTotalStepsTaken());

    QMessageBox::information(this, "Смерть", message);

    continue_button_->setVisible(false);
    this->show();
}
