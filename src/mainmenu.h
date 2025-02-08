#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MainMenu : public QWidget {
    Q_OBJECT

public:
    MainMenu(QWidget* parent = nullptr);

private slots:
    void startNewGame();

    void loadGame();
};
