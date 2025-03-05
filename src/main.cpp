#include "ui/mainmenu.h"
#include <qapplication.h>

auto main(int argc, char *argv[]) -> int {
  QApplication const app(argc, argv);

  MainMenu main_menu;
  main_menu.show();

  return QApplication::exec();
}
