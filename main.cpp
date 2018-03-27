#include <QApplication>

#include <board.h>
#include <dialog.h>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Dialog* dialog = new Dialog();  // TODO memory optimization
  dialog->show();
  return app.exec();
}
