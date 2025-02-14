#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

const int kMapWidth = 80;
const int kMapHeight = 60;

class MainMenu : public QWidget {
  Q_OBJECT

public:
  MainMenu(QWidget *parent = nullptr);

private slots:
  void startNewGame();
  void loadGame();
};
