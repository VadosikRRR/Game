#include "playernamedialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
PlayerNameDialog::PlayerNameDialog(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Enter Player Name");
    setFixedSize(300, 150);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Enter your character's name:", this);
    layout->addWidget(label);

    nameInput = new QLineEdit(this);
    layout->addWidget(nameInput);

    QPushButton* confirmButton = new QPushButton("Confirm", this);
    connect(confirmButton, &QPushButton::clicked, this, &PlayerNameDialog::accept);
    layout->addWidget(confirmButton);
}

QString PlayerNameDialog::getPlayerName() const {
    return nameInput->text();
}
