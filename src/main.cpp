#include "ui/mainmenu.h"
#include <qapplication.h>

auto main(int argc, char *argv[]) -> int {
  QApplication const app(argc, argv);

  MainMenu mainMenu;
  mainMenu.show();

  return QApplication::exec();
}
