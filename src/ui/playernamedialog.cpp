#include "playernamedialog.h"
#include <qboxlayout.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>
PlayerNameDialog::PlayerNameDialog(QWidget *parent)
    : QDialog(parent), nameInput(new QLineEdit(this)) {
  setWindowTitle("Enter Player Name");
  setFixedSize(300, 150);

  auto *layout = new QVBoxLayout(this);

  auto *label = new QLabel("Enter your character's name:", this);
  layout->addWidget(label);

  layout->addWidget(nameInput);

  auto *confirm_button = new QPushButton("Confirm", this);
  connect(confirm_button, &QPushButton::clicked, this,
          &PlayerNameDialog::accept);
  layout->addWidget(confirm_button);
}

QString PlayerNameDialog::getPlayerName() const { return nameInput->text(); }
