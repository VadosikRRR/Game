#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

const int kMapWidth = 60;
const int kMapHeight = 80;

class MainMenu : public QWidget {
    Q_OBJECT

public:
    MainMenu(QWidget* parent = nullptr);

private slots:
    void startNewGame();
    void loadGame();
};
