#include "playernamedialog.h"
#include <qwidget.h>
#include <qdialog.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
PlayerNameDialog::PlayerNameDialog(QWidget* parent)
    : QDialog(parent), nameInput(new QLineEdit(this)) {
    setWindowTitle("Enter Player Name");
    setFixedSize(300, 150);

    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel("Enter your character's name:", this);
    layout->addWidget(label);

    
    layout->addWidget(nameInput);

    auto* confirmButton = new QPushButton("Confirm", this);
    connect(confirmButton, &QPushButton::clicked, this, &PlayerNameDialog::accept);
    layout->addWidget(confirmButton);
}

QString PlayerNameDialog::getPlayerName() const
{
    return nameInput->text();
}
