#ifndef PLAYERNAMEDIALOG_H
#define PLAYERNAMEDIALOG_H

#include <QDialog>
#include <QLineEdit>

class PlayerNameDialog : public QDialog {
  Q_OBJECT

public:
  explicit PlayerNameDialog(QWidget *parent = nullptr);
  QString getPlayerName() const;

private:
  QLineEdit *nameInput;
};

#endif // PLAYERNAMEDIALOG_H
